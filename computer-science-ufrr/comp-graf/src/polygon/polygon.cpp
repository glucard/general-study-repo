#include "polygon.hpp"

rtz::Polygon::Polygon(int _color){
    this->color = _color;
    /* 
    this->min.x = 0;
    this->min.y = 0;
    this->max.x = 0;
    this->max.y = 0;
     */
}

void rtz::Polygon::add_vertice(int x, int y){
    Point p;
    p.x = x;
    p.y = y;
    this->vertices.push_back(p);
    /* 
    if (x < this->min.x)
        this->min.x = x;
    if (y < this->min.y)
        this->min.y = y;
    if (x > this->max.x)
        this->max.x = x;
    if (y > this->max.y)
        this->max.y = y;
    */       
}

void rtz::Polygon::raster(arr::Array2d frame_buffer) {

    if (this->vertices.size() < 3) {
        throw std::invalid_argument("Polygon must have at least 3 vertices");
        return;
    }
    
    rtz::Line lr;
    std::vector<Point>::iterator previous, i_point, begin, end;
    begin = this->vertices.begin();
    end = this->vertices.end();
    int x1, y1, x2, y2;
    for(i_point = begin; i_point != end; ++i_point) {
        

        if (i_point == this->vertices.begin()) {
            previous = i_point;
            continue;
        }

        x1 = previous->x;
        y1 = previous->y;
        x2 = i_point->x;
        y2 = i_point->y;
        lr.bresenham(x1, y1, x2, y2, frame_buffer);
        
        previous = i_point;
    }
    x1 = begin->x;
    y1 = begin->y;
    lr.bresenham(x1, y1, x2, y2, frame_buffer);  
    
}
/* 
void rtz::Polygon::fill(int color){
    int rows, cols;
    rows = this->max.x - this->min.x + 2;
    cols = this->max.y - this->min.y + 2;
    arr::Array2d map(rows, cols);

    this->raster(map);
} 
*/