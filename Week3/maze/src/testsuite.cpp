
/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include <cstdio>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"


int main()
{
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();

    /* TODO: Test all the things! */
    Coordinate c(1, 2);
    Coordinate c1(3, 4);
    Coordinate c2(6, 6);
   
    /* STACK CHECKING */
    printf("Checking the Stack\n\n");

    Coordinate c3 = stack->pop();
    printf("Popping from Empty Stack: Return (-1, -1)\n");
    printf("(%d, %d)\n", c3.x, c3.y);

    stack->push(c);
    printf("Pushing (1, 2): Peek Return (1, 2)\n");
    printf("(%d, %d)\n", stack->peek().x, stack->peek().y); 

    stack->push(c1);
    printf("Pushing (3, 4): Peek Return (3, 4)\n");
    printf("(%d, %d)\n", stack->peek().x, stack->peek().y); 

    stack->push(c2);
    printf("Pushing (6, 6): Peek Return (6, 6)\n");
    printf("(%d, %d)\n", stack->peek().x, stack->peek().y);

    Coordinate c4 = stack->pop(); 
    printf("Popping from Stack: Return (6, 6)\n");
    printf("(%d, %d)\n", c4.x, c4.y); 

    printf("Peeking at Stack: (3, 4)\n");
    printf("(%d, %d)\n", stack->peek().x, stack->peek().y);

    Coordinate c5 = stack->pop();
    printf("Popping from Stack: Return (3, 4)\n");
    printf("(%d, %d)\n", c5.x, c5.y);
 
    Coordinate c6 = stack->pop(); 
    printf("Popping from Stack: Return (1, 2)\n");
    printf("(%d, %d)\n", c6.x, c6.y);

    Coordinate c7 = stack->pop(); 
    printf("Popping from Empty Stack: Return (-1, -1)\n");
    printf("(%d, %d)\n", c7.x, c7.y);  

    Coordinate c8 = stack->pop();
    printf("Popping from Empty Stack: Return (-1, -1)\n");
    printf("(%d, %d)\n", c8.x, c8.y);


    /* QUEUE CHECKING */
    printf("\nChecking the Queue\n\n");

    Coordinate c9 = queue->dequeue();
    printf("Dequeue from Empty Queue: Return (-1, -1)\n");
    printf("(%d, %d)\n", c9.x, c9.y);

    queue->enqueue(c); //Adding (1, 2)
    printf("Enqueue (1, 2): Peek Return (1, 2)\n");
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y);

    queue->enqueue(c1);
    printf("Enqueue (3, 4): Peek Return (1, 2)\n"); //Adding (3, 4)
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y);

    queue->enqueue(c2);
    printf("Enqueue (6, 6): Peek Return (1, 2)\n"); //Adding (6, 6)
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y);

    Coordinate c10 = queue->dequeue(); //Removes (1, 2)
    printf("Dequeue: Return (1, 2)\n");
    printf("(%d, %d)\n", c10.x, c10.y);

    printf("Peek: Return (3, 4)\n");
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y);

    Coordinate c11 = queue->dequeue();
    printf("Dequeue: Return (3, 4)\n");
    printf("(%d, %d)\n", c11.x, c11.y);

    printf("Peek: Return (6, 6)\n");
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y); 

    Coordinate c12 = queue->dequeue();
    printf("Dequeue: Return (6, 6)\n");
    printf("(%d, %d)\n", c12.x, c12.y);

    printf("Peek into Empty Queue: Return (-1, -1)\n");
    printf("(%d, %d)\n", queue->peek().x, queue->peek().y); 


    delete queue;
    delete stack;

    return 0;
}
