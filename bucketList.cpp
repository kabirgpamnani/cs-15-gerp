/*
 *  PassengerQueue.cpp
 *  Isaac Monheit
 *  2/12/2022
 *
 *  CS 15 Proj1 
 *
 *  Implementation and definition of all the header functions in
 *  PassengerQueue.h
 *
 */


#include <iostream>
#include "fileStruct.h"
#include "caseSensitive.h"
#include "bucketList.h"
#include <vector>


/* front()
 *    Purpose: returns the front Passenger but doesn't remove it from the queue
 *    Returns: the front Passenger of the queue
 */
caseSensitive bucketList::caseAt(int index)
{
    return bucket.at(index);
}


/* enqueue()
 *    Purpose: adds an element to the back of the queue
 * Parameters: the passenger being added to the queue
 */
void bucketList::insert(const caseSensitive &oneCase)
{
    bucket.push_back(oneCase);
}

/* size()
 *    Purpose: returns the size of the queue
 *    Returns: an int holding the size of the queue
 */
int bucketList::size()
{
    return bucket.size();
}

