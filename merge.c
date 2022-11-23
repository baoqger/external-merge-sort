/*
 * Divide the entire input file into different groups based on the available memory
 * resource restrictions. 
 * 
 * Read each group of the input file into the memory buffer, sort the records in the memory buffer, 
 * save the sorted records in a temporary sub file. This process is called one run. 
 *
 * At the end of this sort phase, # temporary sorted sub files will be created.
 * */
