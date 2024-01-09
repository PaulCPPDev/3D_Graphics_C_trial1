#include "../include/triangle.h"
#include "../include/display.h"
#include "../include/sort.h"
#include "../include/swap.h"

void draw_unfilled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}

void draw_filled_triangle(
    int x0, int y0, 
    int x1, int y1, 
    int x2, int y2, 
    uint32_t color
){
	// Flat Bottom Flat Top technique
	//
	// We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
	if (y0 > y1) {
        	int_swap(&y0, &y1);
        	int_swap(&x0, &x1);
        	// float_swap(&z0, &z1);
        	// float_swap(&w0, &w1);
    	}
    	if (y1 > y2) {
        	int_swap(&y1, &y2);
        	int_swap(&x1, &x2);
        	// float_swap(&z1, &z2);
        	// float_swap(&w1, &w2);
    	}
    	if (y0 > y1) {
        	int_swap(&y0, &y1);
        	int_swap(&x0, &x1);
        	// float_swap(&z0, &z1);
        	// float_swap(&w0, &w1);
    	}
	

	// Find the midpoint and divide the triangle in 2
	int midY = y1;
	int midX = (int)( ( (x2 -x0)*(y1-y0)/(float)(y2-y0) ) + x0);

	////////////////////////////////////
	// Draw FlatBottom triangle
	//
	// calculate inverse slopes
	float inv_slope1 = (x1-x0)/(float)(y1-y0);
	float inv_slope2 = (midX-x0)/(float)(midY-y0);
	//
	// Initial values
	float x_start = x0;
	float x_end = x0;
	//
	// Plot from top to bottom
	for(int y = y0; y<= midY; y ++){
		draw_line((int)x_start, y,(int) x_end, y, color);
		x_start += inv_slope1;
		x_end += inv_slope2;	
	}
	

	///////////////////////
	// Draw FlatTop triangle
	//
	// calculate inverse slopes
	inv_slope1 = (x2-x1)/(float)(y2-y1);
	inv_slope2 = (x2-midX)/(float)(y2-midY);
	//
	// Initial values
	x_start = x2;
	x_end = x2;
	//
	// Plot from bottom to top
	for (int y = y2; y >= midY; y--){
		draw_line((int)x_start, y, (int) x_end, y, color);
		x_start -= inv_slope1;
		x_end -= inv_slope2;
	}
}


