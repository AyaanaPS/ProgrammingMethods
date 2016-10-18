
/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))



/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    unsigned int *seam = new unsigned int[h];
    int **cmap = new int*[w];
    for(int i = 0; i < w; i++)
    {
    	cmap[i] = new int[h];
    }

    //1st Row of CMAP = 1st Row of SMAP
    for(int col1 = 0; col1 < w; col1++)
    {
    	cmap[col1][0] = smap[col1][0];
    }

    //Filling Cost Matrix
    for (int row = 1; row < h; row++)
    {					
    	for (int col = 0; col < w; col++)
    	{	
    		if(col == 0) //Check Edge Case 1
    		{
    			cmap[col][row] = smap[col][row] + min(cmap[col][row-1], cmap[col+1][row-1]);
    		}
    		else if (col == w-1) //Check Edge Case 2
    		{
    			cmap[col][row] = smap[col][row] + min(cmap[col-1][row-1], cmap[col][row-1]);
    		}
    		else //Not the Edge
    		{
    			unsigned int minimum = min(cmap[col-1][row-1], cmap[col][row-1]);
    			minimum = min(minimum, cmap[col+1][row-1]);
    			cmap[col][row] = smap[col][row] + minimum;
    		}
    	}    
    }

    //COST MATRIX COMPLETED
    
	unsigned int startingMin = cmap[0][h-1]; //Initialized as First Column in Last Row
	int colIndex = 0; 
	for(int col = 1; col < w; col ++)
	{
		if (cmap[col][h-1] < startingMin)
		{
			startingMin = cmap[col][h-1];
			colIndex = col;
		} 
	}

	//Starting Min is last Value in Seam
	seam[h-1] = colIndex; //Filling Seam Backwards
	int seamIndex = h-2;
	//Starting from second to last row.
	for(int b = h - 2; b >= 0; b--)
	{
		unsigned int newMin = cmap[colIndex][b]; //New Min initialized as number in box above startingMin
	
		if(colIndex == 0) //Check Edge Case1
		{
			if (cmap[colIndex+1][b]<newMin)
			{
				colIndex = colIndex + 1;
			}
		}
		else if(colIndex == w-1) //Check Edge Case2
		{

			if(cmap[colIndex-1][b]<newMin)
			{
				colIndex = colIndex - 1;
			}
		}
		else //Not the Edge
		{
			if(cmap[colIndex+1][b] < newMin && cmap[colIndex+1][b] < cmap[colIndex-1][b])
			{
				colIndex = colIndex + 1;
			}
			else if(cmap[colIndex-1][b] < newMin && cmap[colIndex-1][b] < cmap[colIndex+1][b]) //if cmap[colIndex-1][b] is the smallest
			{
				colIndex = colIndex - 1;
			}
		}
		seam[seamIndex] = colIndex;
		seamIndex--;
	}

	
	
	//Deallocation of Memory
	for(int i = 0; i < w; i++)
	{
		delete[] cmap[i];
	}
	delete[] cmap;
	
	//Return Statement
	return seam;
}
