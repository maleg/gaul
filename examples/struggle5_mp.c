/**********************************************************************
  struggle5_mp.c
 **********************************************************************

  struggle5_mp - Test/example program for GAUL.
  Copyright �2002, Stewart Adcock <stewart@linux-domain.com>

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

  Synopsis:	Test/example program for GAUL.

		This example shows the use of multiple populations
		with GAUL's so called "archipelago" scheme.  This is
		the basic island model of evolution, with the islands'
		populations distributed over several processors.

		This program aims to generate the final sentence from
		Chapter 3 of Darwin's "The Origin of Species",
		entitled "Struggle for Existence".

		This example is discussed in docs/html/tutorial9.html

		It is likely that you have problems to compile and/or
		execute this example.  Isuggest the following:
		1) Download and _correctly_ install a MPI implementation.
		2) Confirm that MPI programs work okay.
		3) Use "./configure --enable-mpi=yes" to build GAUL.
		4) Execute this example with something like "mpirum -v -np 4 ./struggle5_mp"

 **********************************************************************/

/*
 * Includes
 */
#include "gaul.h"

/*
 * Specify the number of populations (islands) to use on each processor.
 * (This value doesn't need to be constant across all processors.)
 */
#define GA_STRUGGLE_NUM_POPS_PER_PROC	2

/*
 * The solution string.
 */
char *target_text="When we reflect on this struggle, we may console ourselves with the full belief, that the war of nature is not incessant, that no fear is felt, that death is generally prompt, and that the vigorous, the healthy, and the happy survive and multiply.";


/**********************************************************************
  struggle_score()
  synopsis:	Score solution.
  parameters:
  return:
  updated:	16/06/01
 **********************************************************************/

boolean struggle_score(population *pop, entity *entity)
  {
  int		k;		/* Loop variable over all alleles. */

  entity->fitness = 0.0;

  /* Loop over alleles in chromosome. */
  for (k = 0; k < pop->len_chromosomes; k++)
    {
    if ( ((char *)entity->chromosome[0])[k] == target_text[k])
      entity->fitness+=1.0;
    /*
     * Component to smooth function, which helps a lot in this case:
     * Comment it out if you like.
     */
    entity->fitness += (127.0-fabs(((char *)entity->chromosome[0])[k]-target_text[k]))/50.0;
    }

  return TRUE;
  }


/**********************************************************************
  main()
  synopsis:	The "struggle5" example modified slightly to use
		multiple processors.
  parameters:
  return:
  updated:	29 Jan 2002
 **********************************************************************/

int main(int argc, char **argv)
  {
  int		i;					/* Loop over populations. */
  population	*pops[GA_STRUGGLE_NUM_POPS_PER_PROC];	/* Array of populations. */

  log_set_level(LOG_DEBUG);

  mpi_init(&argc, &argv);

  random_init();
  random_seed(42+mpi_get_rank());

  for (i=0; i<GA_STRUGGLE_NUM_POPS_PER_PROC; i++)
    {
    pops[i] = ga_genesis_char(
       80,			/* const int              population_size */
       1,			/* const int              num_chromo */
       strlen(target_text),	/* const int              len_chromo */
       NULL,		 	/* GAgeneration_hook      generation_hook */
       NULL,			/* GAiteration_hook       iteration_hook */
       NULL,			/* GAdata_destructor      data_destructor */
       NULL,			/* GAdata_ref_incrementor data_ref_incrementor */
       struggle_score,		/* GAevaluate             evaluate */
       ga_seed_printable_random,	/* GAseed                 seed */
       NULL,			/* GAadapt                adapt */
       ga_select_one_roulette,	/* GAselect_one           select_one */
       ga_select_two_roulette,	/* GAselect_two           select_two */
       ga_mutate_printable_singlepoint_drift,	/* GAmutate       mutate */
       ga_crossover_char_allele_mixing,	/* GAcrossover            crossover */
       NULL			/* GAreplace replace */
            );

    ga_population_set_parameters( pops[i], 0.75, 0.25, 0.001);
    ga_population_set_parameters( pops[i], 0.75, 0.25, 0.1);
    }

/*
 * Test chromosome packing.
 */
  for (i=0; i<pops[0]->size; i++)
    {
    int len;
    byte *buffer1=NULL, *buffer2=NULL;
    unsigned int max_len=0;

    len = (int) pops[0]->chromosome_to_bytes(pops[0], pops[0]->entity_iarray[i], &buffer1, &max_len);
    len = (int) pops[0]->chromosome_to_bytes(pops[0], pops[0]->entity_iarray[i], &buffer2, &max_len);
    pops[0]->chromosome_from_bytes(pops[0], pops[0]->entity_iarray[i], buffer1);
    len = (int) pops[0]->chromosome_to_bytes(pops[0], pops[0]->entity_iarray[i], &buffer1, &max_len);
    
    printf("E %d len %d match %d\n", i, len, memcmp(buffer1, buffer2, len));
    }

/*
 * The only significant difference between "examples/struggle5" and
 * "examples/struggle5_mp" is in the following statement.
 */
  ga_evolution_archipelago_mp( GA_STRUGGLE_NUM_POPS_PER_PROC, pops,
       GA_CLASS_DARWIN,	GA_ELITISM_PARENTS_SURVIVE, 250 );

  for (i=0; i<GA_STRUGGLE_NUM_POPS_PER_PROC; i++)
    {
    printf( "The best solution on processor %d, island %d with score %f was:\n%s\n",
            mpi_get_rank(), i,
            ga_get_entity_from_rank(pops[i],0)->fitness,
            ga_chromosome_char_to_staticstring(pops[i], ga_get_entity_from_rank(pops[i],0)) );

    ga_extinction(pops[i]);
    }

  mpi_exit();

  exit(2);
  }

