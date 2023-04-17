/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 10:15:38 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/17 10:19:21 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

//  Export[]
//  The supplied names are marked for automatic export to the environment of 
//  subsequently executed commands. If no names are given a list of all names 
//  that are exported in this shell is printed. 
//  If a variable name is followed by =word, the value of the variable is set 
//  to word. Export returns an exit status of 0 unless an invalid option is 
//  encountered, one of the names is not a valid shell variable name.