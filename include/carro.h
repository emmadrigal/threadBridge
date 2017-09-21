/** @file carro.h
 *  @brief header for the carro object
 *
 * This file contains the necessary variables
 * for the carro object
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#ifndef _CARRO_H_
#define _CARRO_H_

/** 
 *  @brief structure containing the variables for this object
 */
struct Carro{
	int velocidad;      /**< Speed of this car in number of car lenghts */
	unsigned char tipo; /**< Type of car; 0 is normal, 1 is ambulance and 2 is radioactive*/
};

#endif
