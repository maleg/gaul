/**********************************************************************
  table.c
 **********************************************************************

  table - Table data structure.
  Copyright �2000-2002, Stewart Adcock <stewart@bellatrix.pcl.ox.ac.uk>

  The latest version of this program should be available at:
  http://www.stewart-adcock.co.uk/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.  Alternatively, if your project
  is incompatible with the GPL, I will probably agree to requests
  for permission to use the terms of any other license.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY WHATSOEVER.

  A full copy of the GNU General Public License should be in the file
  "COPYING" provided with this distribution; if not, see:
  http://www.gnu.org/

 **********************************************************************

  Synopsis:	Table data structure. (basically a growable table)

  Thread-safe.
 
  Updated:	29 Jan 2002 SAA	Modifications to avoid some splint (http://www.splint.org/) warnings.
		28 Jan 2002 SAA	Removed some pointless comparisons of unsigned integers with zeros.
		18 Dec 2001 SAA	Added table_get_data_all() and table_get_index_all().
		07/08/01 SAA	Added table_remove_data_all().
		27/02/01 SAA	gpointer replaced with vpointer and G_LOCK etc. replaced with THREAD_LOCK etc.
 		21/02/01 SAA	Added table_count_items().
 		22/01/01 SAA	Added table_lookup_index().
 		18/01/01 SAA	Frist tidy version.
 
  To do:	Add table_compress().
		Need to add more safety checks and create 'fast' versions.
		Document and comment!
 
  Compile test program with something like:
  gcc table.c -DTABLE_COMPILE_MAIN `glib-config --cflags` -I..
              -DVERSION_STRING=NULL -lmethods -lglib -L.

 **********************************************************************/

#include "table.h"

THREAD_LOCK_DEFINE_STATIC(table_mem_chunk_thread);
static MemChunk *table_mem_chunk = NULL;

static unsigned int next_pow2(unsigned int num)
  {
  unsigned int	n = 1;

  num++;

  while(n < num) n <<= 1;

  return n;
  }


static boolean table_ensure_size(TableStruct *table, unsigned int size)
  {
  unsigned int		i;

  if(table->size < size)
    {
    size = next_pow2(size);
    table->data = s_realloc(table->data, sizeof(vpointer)*size);
    table->unused = s_realloc(table->unused, sizeof(unsigned int)*size);

    for (i=table->size; i<size; i++)
      table->data[i]=NULL;

    table->size = size;

/*
    printf("DEBUG: Table size is now %d\n", size);
*/
    }

  return TRUE;
  }


TableStruct *table_new(void)
  {
  TableStruct *table;

  THREAD_LOCK(table_mem_chunk_thread);
  if(!table_mem_chunk)
    table_mem_chunk = mem_chunk_new(sizeof(TableStruct), 64);

  table = mem_chunk_alloc(table_mem_chunk);
  THREAD_UNLOCK(table_mem_chunk_thread);

  table->data = NULL;
  table->unused = NULL;
/*
  table->deallocate = NULL;
*/
  table->size = 0;
  table->numfree = 0;
  table->next = 0;

  return (TableStruct*) table;
  }


void table_destroy(TableStruct *table)
  {
/*
  if(table->deallocate)
    s_free(table->data);
*/
  if (table->data) s_free(table->data);
  if (table->unused) s_free(table->unused);

  THREAD_LOCK(table_mem_chunk_thread);
  mem_chunk_free(table_mem_chunk, table);
  THREAD_UNLOCK(table_mem_chunk_thread);

  return;
  }


boolean table_set_size(TableStruct *table, unsigned int size)
  {

  if(table->size < size)
    {
    return table_ensure_size(table, size);
    }
  else
    {
    printf("FIXME: Maybe need to shrink table if possible.");
    }

  return TRUE;
  }


/* Returns data removed, NULL otherwise. */
vpointer table_remove_index(TableStruct *table, unsigned int index)
  {
  vpointer data;

  if (!table) die("NULL pointer to TableStruct passed.");

/* if (index < 0 || index >= table->next) die("Invalid index passed."); */
  if (index >= table->next) die("Invalid index passed.");

  data = table->data[index];

/* Is this index used?  Do nothing if not. */
  if (data)
    {
    /* Add index to unused list. */
    table->unused[table->numfree]=index;
    table->numfree++;
    table->data[index] = NULL;
    }
  else
    {
    printf("WARNING: Trying to remove unused item.\n");
    }

  return data;
  }


/* Returns index of data removed, TABLE_ERROR_INDEX otherwise. */
unsigned int table_remove_data(TableStruct *table, vpointer data)
  {
  unsigned int	index=0;

  if (!table) die("NULL pointer to TableStruct passed.");
  if (!data) die("NULL pointer to user data passed.");

  while ( index < table->next)
    {
    if ( table->data[index] == data )
      { /* Data found in table */
      /* Add index to unused list. */
      table->unused[table->numfree]=index;
      table->numfree++;
      table->data[index] = NULL;
      return index;
      }
    index++;
    }

  printf("WARNING: Trying to remove unused item.\n");

  return TABLE_ERROR_INDEX;
  }


/* Count of items removed, TABLE_ERROR_INDEX otherwise. */
unsigned int table_remove_data_all(TableStruct *table, vpointer data)
  {
  unsigned int	index=0;
  unsigned int	count=0;

  if (!table) die("NULL pointer to TableStruct passed.");
  if (!data) die("NULL pointer to user data passed.");

  while ( index < table->next)
    {
    if ( table->data[index] == data )
      { /* Data found in table */
      /* Add index to unused list. */
      table->unused[table->numfree]=index;
      table->numfree++;
      table->data[index] = NULL;
      count++;
      }
    index++;
    }

  return count;
  }


vpointer table_get_data(TableStruct *table, unsigned int index)
  {

  if (!table) die("NULL pointer to TableStruct passed.");

/*  if (index < 0 || index >= table->next) dief("Invalid index (%d) passed.", index);*/
  if (index >= table->next) dief("Invalid index (%d) passed.", index);

  return table->data[index];
  }


/* Return array of all stored pointers.  Caller must deallocate the array. */
vpointer *table_get_data_all(TableStruct *table)
  {
  unsigned int  index=0;
  unsigned int	count=0;
  vpointer      *data;		/* Array of data to return. */

  if (!table) die("NULL pointer to TableStruct passed.");

  data = (vpointer*) s_malloc(sizeof(vpointer)*(table->size-table->numfree));

  while ( index < table->next)
    {
    if (table->data[index] != NULL)
      data[count++] = table->data[index];
    index++;
    }

  return data;
  }


/* Return array of all used indices.  Caller must deallocate the array. */
unsigned int *table_get_index_all(TableStruct *table)
  {
  unsigned int  index=0;
  unsigned int	count=0;
  unsigned int  *data;		/* Array of indices to return. */

  if (!table) die("NULL pointer to TableStruct passed.");

  data = (unsigned int*) s_malloc(sizeof(vpointer)*(table->size-table->numfree));

  while ( index < table->next)
    {
    if (table->data[index] != NULL)
      data[count++] = index;
    index++;
    }

  return data;
  }


/* Returns the index for given data, or TABLE_ERROR_INDEX on failure. */
unsigned int table_lookup_index(TableStruct *table, vpointer data)
  {
  unsigned int	index=0;

  if (!table) die("NULL pointer to TableStruct passed.");
  if (!data) die("NULL vpointer data passed.");

  while ( index < table->next )
    {
    if (table->data[index] == data) return index;
    index++;
    }

  return TABLE_ERROR_INDEX;
  }


unsigned int table_add(TableStruct *table, vpointer data)
  {
  unsigned int	index;

  if (!table) die("NULL pointer to TableStruct passed.");
  if (!data) die("NULL vpointer data passed.");

  if (table->numfree>0)
    {	/* Re-use some old indices. */
    table->numfree--;
    table->data[table->unused[table->numfree]]=data;
    return table->unused[table->numfree];
    }

/* Must append to end of array. */
  index = table->next;
  table->next++;
  table_ensure_size(table, table->next);
  table->data[index] = data;

  return index;
  }


unsigned int table_count_items(TableStruct *table)
  {
  if (!table) die("NULL pointer to TableStruct passed.");

  return (table->next-table->numfree);
  }


void table_diagnostics(void)
  {
  printf("=== Table diagnostics ========================================\n");
  printf("Version:             %s\n", VERSION_STRING);
  printf("Build date:          %s\n", BUILD_DATE_STRING);

  printf("--------------------------------------------------------------\n");
  printf("TABLE_ERROR_INDEX:   %u\n", TABLE_ERROR_INDEX);

  printf("--------------------------------------------------------------\n");
  printf("structure            sizeof\n");
#ifdef IRIX_MIPSPRO_SOURCE
  printf("TableStruct          %lu\n", (unsigned long int) sizeof(TableStruct));
#else
  printf("TableStruct          %Zd\n", sizeof(TableStruct));
#endif
  printf("==============================================================\n");

  return;
  }


#ifdef TABLE_COMPILE_MAIN
int main(int argc, char *argv[])
#else
boolean table_test(void)
#endif
  {
/*
  int           i, j;
*/
  TableStruct	*table;

  printf("Testing my table routines.\n");
  printf("FIXME: Actually add some tests!\n");

  table = table_new();
  table_set_size(table, 200);

/*
vpointer table_remove_index(TableStruct *table, unsigned int index);
vpointer table_get_data(TableStruct *table, unsigned int index);
unsigned int table_add(TableStruct *table, vpointer data);
*/

  table_destroy(table);

#ifdef TABLE_COMPILE_MAIN
  exit(2);
#else
  return TRUE;
#endif
  }
