/**********************************************************************
  ga_crossover.c
 **********************************************************************

  ga_crossover - Genetic algorithm crossover operators.
  Copyright �2000-2001, Stewart Adcock <stewart@bellatrix.pcl.ox.ac.uk>

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

  Synopsis:     Routines for performing GA crossover operations.

		These functions should duplicate user data where
		appropriate.

 **********************************************************************/

#include "ga_core.h"

/**********************************************************************
  ga_singlepoint_crossover_chromosome()
  synopsis:	`Mates' two chromosomes by single-point crossover.
  parameters:
  return:
  last updated: 18/10/00
 **********************************************************************/

void ga_singlepoint_crossover_integer_chromosome( population *pop,
                                         int *father, int *mother,
                                         int *son, int *daughter )
  {
  int	location;	/* Point of crossover */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to chromosome structure passed.");

  /* Choose crossover point and perform operation */
  location=random_int(pop->len_chromosomes);

  memcpy(son, mother, location*sizeof(int));
  memcpy(daughter, father, location*sizeof(int));

  memcpy(&(son[location]), &(father[location]), (pop->len_chromosomes-location)*sizeof(int));
  memcpy(&(daughter[location]), &(mother[location]), (pop->len_chromosomes-location)*sizeof(int));

  return;
  }


/**********************************************************************
  ga_doublepoint_crossover_chromosome()
  synopsis:	`Mates' two chromosomes by double-point crossover.
  parameters:
  return:
  last updated: 31/05/01
 **********************************************************************/

void ga_doublepoint_crossover_integer_chromosome(population *pop, int *father, int *mother, int *son, int *daughter)
  {
  int	location1, location2;	/* Points of crossover. */
  int	tmp;			/* For swapping crossover loci. */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to chromosome structure passed.");

  /* Choose crossover point and perform operation */
  location1=random_int(pop->len_chromosomes);
  do
    {
    location2=random_int(pop->len_chromosomes);
    } while (location2==location1);

    if (location1 > location2)
      {
      tmp = location1;
      location1 = location2;
      location2 = tmp;
      }

  memcpy(son, father, location1*sizeof(int));
  memcpy(daughter, mother, location1*sizeof(int));

  memcpy(&(son[location1]), &(mother[location1]), (location2-location1)*sizeof(int));
  memcpy(&(daughter[location1]), &(father[location1]), (location2-location1)*sizeof(int));

  memcpy(&(son[location2]), &(mother[location2]), (pop->len_chromosomes-location2)*sizeof(int));
  memcpy(&(daughter[location2]), &(father[location2]), (pop->len_chromosomes-location2)*sizeof(int));

  return;
  }


/**********************************************************************
  ga_crossover_integer_singlepoints()
  synopsis:	`Mates' two genotypes by single-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 12/05/00
 **********************************************************************/

void ga_crossover_integer_singlepoints(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;	/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    ga_singlepoint_crossover_integer_chromosome( pop,
                        (int *)father->chromosome[i],
			(int *)mother->chromosome[i],
			(int *)son->chromosome[i],
			(int *)daughter->chromosome[i]);
    }

  return;
  }


/**********************************************************************
  ga_crossover_integer_doublepoints()
  synopsis:	`Mates' two genotypes by double-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 31/05/00
 **********************************************************************/

void ga_crossover_integer_doublepoints( population *pop,
                                        entity *father, entity *mother,
                                        entity *son, entity *daughter )
  {
  int		i;	/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    ga_doublepoint_crossover_integer_chromosome( pop,
                        (int *)father->chromosome[i],
			(int *)mother->chromosome[i],
			(int *)son->chromosome[i],
			(int *)daughter->chromosome[i]);
    }

  return;
  }


/**********************************************************************
  ga_crossover_integer_mixing()
  synopsis:	`Mates' two genotypes by mixing parents chromsomes.
		Keeps all chromosomes intact, and therefore do not
		need to recreate structural data.
  parameters:
  return:
  last updated: 27/04/00
 **********************************************************************/

void ga_crossover_integer_mixing(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;		/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    if (random_boolean())
      {
      memcpy(son->chromosome[i], father->chromosome[i], pop->len_chromosomes*sizeof(int));
      memcpy(daughter->chromosome[i], mother->chromosome[i], pop->len_chromosomes*sizeof(int));
      ga_copy_data(pop, son, father, i);
      ga_copy_data(pop, daughter, mother, i);
      }
    else
      {
      memcpy(daughter->chromosome[i], father->chromosome[i], pop->len_chromosomes*sizeof(int));
      memcpy(son->chromosome[i], mother->chromosome[i], pop->len_chromosomes*sizeof(int));
      ga_copy_data(pop, daughter, father, i);
      ga_copy_data(pop, son, mother, i);
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_integer_allele_mixing()
  synopsis:	`Mates' two genotypes by randomizing the parents
		alleles.
		Keeps no chromosomes intact, and therefore will
		need to recreate all structural data.
  parameters:
  return:
  last updated: 30/04/00
 **********************************************************************/

void ga_crossover_integer_allele_mixing( population *pop,
                                 entity *father, entity *mother,
                                 entity *son, entity *daughter )
  {
  int		i, j;		/* Loop over all chromosomes, alleles. */

  /* Checks. */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed.");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    for (j=0; j<pop->len_chromosomes; j++)
      {
      if (random_boolean())
        {
        ((int *)son->chromosome[i])[j] = ((int *)father->chromosome[i])[j];
        ((int *)daughter->chromosome[i])[j] = ((int *)mother->chromosome[i])[j];
        }
      else
        {
        ((int *)daughter->chromosome[i])[j] = ((int *)father->chromosome[i])[j];
        ((int *)son->chromosome[i])[j] = ((int *)mother->chromosome[i])[j];
        }
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_boolean_singlepoints()
  synopsis:	`Mates' two genotypes by single-point crossover of
		each chromosome.  I assume that boolean == integer.
  parameters:
  return:
  last updated: 12/05/00
 **********************************************************************/

void ga_crossover_boolean_singlepoints(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;	/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    ga_singlepoint_crossover_integer_chromosome( pop,
                        (int *)father->chromosome[i],
			(int *)mother->chromosome[i],
			(int *)son->chromosome[i],
			(int *)daughter->chromosome[i]);
    }

  return;
  }


/**********************************************************************
  ga_crossover_boolean_doublepoints()
  synopsis:	`Mates' two genotypes by double-point crossover of
		each chromosome.  I assume that boolean == integer.
  parameters:
  return:
  last updated: 31/05/00
 **********************************************************************/

void ga_crossover_boolean_doublepoints( population *pop,
                                        entity *father, entity *mother,
                                        entity *son, entity *daughter )
  {
  int		i;	/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    ga_doublepoint_crossover_integer_chromosome( pop,
                        (int *)father->chromosome[i],
			(int *)mother->chromosome[i],
			(int *)son->chromosome[i],
			(int *)daughter->chromosome[i]);
    }

  return;
  }


/**********************************************************************
  ga_crossover_boolean_mixing()
  synopsis:	`Mates' two genotypes by mixing parents chromsomes.
		Keeps all chromosomes intact, and therefore do not
		need to recreate structural data.
  parameters:
  return:
  last updated: 27/04/00
 **********************************************************************/

void ga_crossover_boolean_mixing(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;		/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    if (random_boolean())
      {
      memcpy(son->chromosome[i], father->chromosome[i], pop->len_chromosomes*sizeof(boolean));
      memcpy(daughter->chromosome[i], mother->chromosome[i], pop->len_chromosomes*sizeof(boolean));
      ga_copy_data(pop, son, father, i);
      ga_copy_data(pop, daughter, mother, i);
      }
    else
      {
      memcpy(daughter->chromosome[i], father->chromosome[i], pop->len_chromosomes*sizeof(boolean));
      memcpy(son->chromosome[i], mother->chromosome[i], pop->len_chromosomes*sizeof(boolean));
      ga_copy_data(pop, daughter, father, i);
      ga_copy_data(pop, son, mother, i);
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_boolean_allele_mixing()
  synopsis:	`Mates' two genotypes by randomizing the parents
		alleles.
		Keeps no chromosomes intact, and therefore will
		need to recreate all structural data.
  parameters:
  return:
  last updated: 30/04/00
 **********************************************************************/

void ga_crossover_boolean_allele_mixing( population *pop,
                                 entity *father, entity *mother,
                                 entity *son, entity *daughter )
  {
  int		i, j;		/* Loop over all chromosomes, alleles. */

  /* Checks. */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed.");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    for (j=0; j<pop->len_chromosomes; j++)
      {
      if (random_boolean())
        {
        ((boolean *)son->chromosome[i])[j] = ((boolean *)father->chromosome[i])[j];
        ((boolean *)daughter->chromosome[i])[j] = ((boolean *)mother->chromosome[i])[j];
        }
      else
        {
        ((boolean *)daughter->chromosome[i])[j] = ((boolean *)father->chromosome[i])[j];
        ((boolean *)son->chromosome[i])[j] = ((boolean *)mother->chromosome[i])[j];
        }
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_char_mixing()
  synopsis:	`Mates' two genotypes by mixing parents chromsomes.
		Keeps all chromosomes intact, and therefore do not
		need to recreate structural data.
  parameters:
  return:
  last updated: 16/06/01
 **********************************************************************/

void ga_crossover_char_mixing( population *pop,
                               entity *father, entity *mother,
                               entity *son, entity *daughter )
  {
  int		i;		/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    if (random_boolean())
      {
      memcpy( son->chromosome[i], father->chromosome[i],
              pop->len_chromosomes*sizeof(char) );
      memcpy( daughter->chromosome[i], mother->chromosome[i],
              pop->len_chromosomes*sizeof(char) );
      ga_copy_data(pop, son, father, i);
      ga_copy_data(pop, daughter, mother, i);
      }
    else
      {
      memcpy( daughter->chromosome[i], father->chromosome[i],
              pop->len_chromosomes*sizeof(char) );
      memcpy( son->chromosome[i], mother->chromosome[i],
              pop->len_chromosomes*sizeof(char) );
      ga_copy_data(pop, daughter, father, i);
      ga_copy_data(pop, son, mother, i);
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_char_allele_mixing()
  synopsis:	`Mates' two genotypes by randomizing the parents
		alleles.
		Keeps no chromosomes intact, and therefore will
		need to recreate all structural data.
  parameters:
  return:
  last updated: 16/06/01
 **********************************************************************/

void ga_crossover_char_allele_mixing( population *pop,
                                 entity *father, entity *mother,
                                 entity *son, entity *daughter )
  {
  int		i, j;		/* Loop over all chromosomes, alleles. */

  /* Checks. */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed.");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    for (j=0; j<pop->len_chromosomes; j++)
      {
      if (random_boolean())
        {
        ((char *)son->chromosome[i])[j] = ((char *)father->chromosome[i])[j];
        ((char *)daughter->chromosome[i])[j] = ((char *)mother->chromosome[i])[j];
        }
      else
        {
        ((char *)daughter->chromosome[i])[j] = ((char *)father->chromosome[i])[j];
        ((char *)son->chromosome[i])[j] = ((char *)mother->chromosome[i])[j];
        }
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_double_mixing()
  synopsis:	`Mates' two genotypes by mixing parents chromsomes.
		Keeps all chromosomes intact, and therefore do not
		need to recreate structural data.
  parameters:
  return:
  last updated: 16/06/01
 **********************************************************************/

void ga_crossover_double_mixing( population *pop,
                               entity *father, entity *mother,
                               entity *son, entity *daughter )
  {
  int		i;		/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    if (random_boolean())
      {
      memcpy( son->chromosome[i], father->chromosome[i],
              pop->len_chromosomes*sizeof(double) );
      memcpy( daughter->chromosome[i], mother->chromosome[i],
              pop->len_chromosomes*sizeof(double) );
      ga_copy_data(pop, son, father, i);
      ga_copy_data(pop, daughter, mother, i);
      }
    else
      {
      memcpy( daughter->chromosome[i], father->chromosome[i],
              pop->len_chromosomes*sizeof(double) );
      memcpy( son->chromosome[i], mother->chromosome[i],
              pop->len_chromosomes*sizeof(double) );
      ga_copy_data(pop, daughter, father, i);
      ga_copy_data(pop, son, mother, i);
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_double_allele_mixing()
  synopsis:	`Mates' two genotypes by randomizing the parents
		alleles.
		Keeps no chromosomes intact, and therefore will
		need to recreate all structural data.
  parameters:
  return:
  last updated: 16/06/01
 **********************************************************************/

void ga_crossover_double_allele_mixing( population *pop,
                                 entity *father, entity *mother,
                                 entity *son, entity *daughter )
  {
  int		i, j;		/* Loop over all chromosomes, alleles. */

  /* Checks. */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed.");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    for (j=0; j<pop->len_chromosomes; j++)
      {
      if (random_boolean())
        {
        ((double *)son->chromosome[i])[j] = ((double *)father->chromosome[i])[j];
        ((double *)daughter->chromosome[i])[j] = ((double *)mother->chromosome[i])[j];
        }
      else
        {
        ((double *)daughter->chromosome[i])[j] = ((double *)father->chromosome[i])[j];
        ((double *)son->chromosome[i])[j] = ((double *)mother->chromosome[i])[j];
        }
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_char_singlepoints()
  synopsis:	`Mates' two genotypes by single-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 16/07/01
 **********************************************************************/

void ga_crossover_char_singlepoints( population *pop,
                                     entity *father, entity *mother,
                                     entity *son, entity *daughter )
  {
  int		i;		/* Loop variable over all chromosomes. */
  int		location;	/* Point of crossover. */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    /* Choose crossover point and perform operation */
    location=random_int(pop->len_chromosomes);

    memcpy( son->chromosome[i], mother->chromosome[i],
            location*sizeof(char) );
    memcpy( daughter->chromosome[i], father->chromosome[i],
            location*sizeof(char));

    memcpy( &(((char *)son->chromosome[i])[location]),
            &(((char *)father->chromosome[i])[location]),
            (pop->len_chromosomes-location)*sizeof(char) );
    memcpy( &(((char *)daughter->chromosome[i])[location]),
            &(((char *)mother->chromosome[i])[location]),
            (pop->len_chromosomes-location)*sizeof(char) );
    }

  return;
  }


/**********************************************************************
  ga_crossover_char_doublepoints()
  synopsis:	`Mates' two genotypes by double-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 16/07/01
 **********************************************************************/

void ga_crossover_char_doublepoints( population *pop,
                                     entity *father, entity *mother,
                                     entity *son, entity *daughter )
  {
  int	i;			/* Loop variable over all chromosomes. */
  int	location1, location2;	/* Points of crossover. */
  int	tmp;			/* For swapping crossover loci. */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    /* Choose crossover point and perform operation */
    location1=random_int(pop->len_chromosomes);
    do
      {
      location2=random_int(pop->len_chromosomes);
      } while (location2==location1);

    if (location1 > location2)
      {
      tmp = location1;
      location1 = location2;
      location2 = tmp;
      }

    memcpy( son->chromosome[i], father->chromosome[i],
            location1*sizeof(char) );
    memcpy( daughter->chromosome[i], mother->chromosome[i],
            location1*sizeof(char) );

    memcpy( &(((char *)son->chromosome[i])[location1]),
            &(((char *)mother->chromosome[i])[location1]),
            (location2-location1)*sizeof(char) );
    memcpy( &(((char *)daughter->chromosome[i])[location1]),
            &(((char *)father->chromosome[i])[location1]),
            (location2-location1)*sizeof(char) );

    memcpy( &(((char *)son->chromosome[i])[location2]),
            &(((char *)mother->chromosome[i])[location2]),
            (pop->len_chromosomes-location2)*sizeof(char) );
    memcpy( &(((char *)daughter->chromosome[i])[location2]),
            &(((char *)father->chromosome[i])[location2]),
            (pop->len_chromosomes-location2)*sizeof(char) );
    }

  return;
  }


/**********************************************************************
  ga_crossover_bitstring_singlepoints()
  synopsis:	`Mates' two genotypes by single-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 30/06/01
 **********************************************************************/

void ga_crossover_bitstring_singlepoints(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;	/* Loop variable over all chromosomes. */
  int		location;	/* Point of crossover. */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    /* Choose crossover point and perform operation */
    location=random_int(pop->len_chromosomes);

    ga_bit_copy(son->chromosome[i], mother->chromosome[i],
                  0, 0, location);
    ga_bit_copy(daughter->chromosome[i], father->chromosome[i],
                  0, 0, location);

    ga_bit_copy(daughter->chromosome[i], mother->chromosome[i],
                  location, location, pop->len_chromosomes-location);
    ga_bit_copy(son->chromosome[i], father->chromosome[i],
                  location, location, pop->len_chromosomes-location);
    }

  return;
  }


/**********************************************************************
  ga_crossover_bitstring_doublepoints()
  synopsis:	`Mates' two genotypes by double-point crossover of
		each chromosome.
  parameters:
  return:
  last updated: 30/06/01
 **********************************************************************/

void ga_crossover_bitstring_doublepoints( population *pop,
                                        entity *father, entity *mother,
                                        entity *son, entity *daughter )
  {
  int	i;		/* Loop variable over all chromosomes. */
  int	location1, location2;	/* Points of crossover. */
  int	tmp;			/* For swapping crossover loci. */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    /* Choose crossover point and perform operation */
    location1=random_int(pop->len_chromosomes);
    do
      {
      location2=random_int(pop->len_chromosomes);
      } while (location2==location1);

    if (location1 > location2)
      {
      tmp = location1;
      location1 = location2;
      location2 = tmp;
      }

    ga_bit_copy(son->chromosome[i], mother->chromosome[i],
                  0, 0, location1);
    ga_bit_copy(daughter->chromosome[i], father->chromosome[i],
                  0, 0, location1);

    ga_bit_copy(daughter->chromosome[i], mother->chromosome[i],
                  location1, location1, location2-location1);
    ga_bit_copy(son->chromosome[i], father->chromosome[i],
                  location1, location1, location2-location1);

    ga_bit_copy(daughter->chromosome[i], mother->chromosome[i],
                  location2, location2, pop->len_chromosomes-location2);
    ga_bit_copy(son->chromosome[i], father->chromosome[i],
                  location2, location2, pop->len_chromosomes-location2);
    }

  return;
  }


/**********************************************************************
  ga_crossover_bitstring_mixing()
  synopsis:	`Mates' two genotypes by mixing parents chromsomes.
		Keeps all chromosomes intact, and therefore do not
		need to recreate structural data.
  parameters:
  return:
  last updated: 30/06/01
 **********************************************************************/

void ga_crossover_bitstring_mixing(population *pop, entity *father, entity *mother, entity *son, entity *daughter)
  {
  int		i;		/* Loop variable over all chromosomes */

  /* Checks */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    if (random_boolean())
      {
      ga_bit_clone(son->chromosome[i], father->chromosome[i], pop->len_chromosomes);
      ga_bit_clone(daughter->chromosome[i], mother->chromosome[i], pop->len_chromosomes);
      ga_copy_data(pop, son, father, i);
      ga_copy_data(pop, daughter, mother, i);
      }
    else
      {
      ga_bit_clone(daughter->chromosome[i], father->chromosome[i], pop->len_chromosomes);
      ga_bit_clone(son->chromosome[i], mother->chromosome[i], pop->len_chromosomes);
      ga_copy_data(pop, daughter, father, i);
      ga_copy_data(pop, son, mother, i);
      }
    }

  return;
  }


/**********************************************************************
  ga_crossover_bitstring_allele_mixing()
  synopsis:	`Mates' two genotypes by randomizing the parents
		alleles.
		Keeps no chromosomes intact, and therefore will
		need to recreate all structural data.
  parameters:
  return:
  last updated: 30/06/01
 **********************************************************************/

void ga_crossover_bitstring_allele_mixing( population *pop,
                                 entity *father, entity *mother,
                                 entity *son, entity *daughter )
  {
  int		i, j;		/* Loop over all chromosomes, alleles. */

  /* Checks. */
  if (!father || !mother || !son || !daughter)
    die("Null pointer to entity structure passed.");

  for (i=0; i<pop->num_chromosomes; i++)
    {
    for (j=0; j<pop->len_chromosomes; j++)
      {
      if (random_boolean())
        {
        if (ga_bit_get(father->chromosome[i],j))
          ga_bit_set(son->chromosome[i],j);
        else
          ga_bit_clear(son->chromosome[i],j);

        if (ga_bit_get(mother->chromosome[i],j))
          ga_bit_set(daughter->chromosome[i],j);
        else
          ga_bit_clear(daughter->chromosome[i],j);
        }
      else
        {
        if (ga_bit_get(father->chromosome[i],j))
          ga_bit_set(daughter->chromosome[i],j);
        else
          ga_bit_clear(daughter->chromosome[i],j);

        if (ga_bit_get(mother->chromosome[i],j))
          ga_bit_set(son->chromosome[i],j);
        else
          ga_bit_clear(son->chromosome[i],j);
        }
      }
    }

  return;
  }


