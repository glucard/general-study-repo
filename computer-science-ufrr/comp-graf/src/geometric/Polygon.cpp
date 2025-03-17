#include "Polygon.hpp"

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
    rtz::Point p(x, y);
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

std::vector<rtz::Point> snipe_sutherland(std::vector<rtz::Point> vertices, int x_min, int y_min, int x_max, int y_max){
    std::vector<rtz::Point> new_verticies;
    std::vector<std::array<int, 4>> p_codes;

    int n_vertices = vertices.size();

    // 1º Passo: associar códigos aos pontos extremos, usando a regra.
    int i;
    for (i=0; i<n_vertices; i++) {
        std::array<int, 4> p_code;
        p_code[0] = (vertices[i].x < x_min) ?  1 : 0;
        p_code[1] = (vertices[i].x > x_max) ?  1 : 0;
        p_code[2] = (vertices[i].y < y_min) ?  1 : 0;
        p_code[3] = (vertices[i].y > y_max) ?  1 : 0;
        p_codes.push_back(p_code);
    }
    
    // 2º Passo: verificar se a linha é totalmente visível.
    
    p_codes.push_back(p_codes[0]); // completar poligno
    int sum, inter, j;
    for (i=0; i<n_vertices; i++) {
        sum = 0;
        for (j=0; j < 4; j++){
            sum += p_codes[i][j] + p_codes[i+1][j];
        }
        if (sum == 0) {
            std::cout << "Linha totalmente visível.\n";
            new_verticies.push_back(vertices[i]);
            new_verticies.push_back(vertices[i+1]);
            continue;
        } else {
            inter = 0;
            for (j=0; j < 4; j++){
                inter = p_codes[i][j] + p_codes[i+1][j];

                if (inter == 2) {
                    std::cout << "Linha invisivel em " << j << std::endl; 
                    continue;
                }
                int dy = (vertices[i + 1].y - vertices[i].y);
                int dx = (vertices[i + 1].x - vertices[i].x);
                float m =  dy/(float)dx;
                
                // ▪ Esquerda: Xmin = -1 → Y = 2/3. [ -1 - (-3/2)] + 1/6 = ½ {Ymin ≤ Y = ½ ≤ Ymax }
                // ▪ Direita: Xmax = 1 → Y = 2/3. [1 - (-3/2)] + 1/6 = 11/6 {FORA}
                // ▪ Top: Ymax = 1 → X = -3/2 + 3/2. [ 1 - 1/6] = -1/4 {Xmin ≤ -1/4 ≤ Xmax }
                // ▪ Botton: Ymin = -1 → X = -3/2 + 3/2. [ 1 - 1/6] = -13/4 {FORA}
            }
        }
    }


    return new_verticies;
}

void rtz::Polygon::raster(arr::Array2d frame_buffer, bool snipe) {

    if (this->vertices.size() < 3) {
        throw std::invalid_argument("Polygon must have at least 3 vertices");
        return;
    }
    
    std::vector<rtz::Point> raster_vertices = snipe ? snipe_sutherland(vertices, 0, 0, frame_buffer.cols, frame_buffer.rows) : this->vertices;

    rtz::Line lr;
    std::vector<rtz::Point>::iterator previous, i_point, begin, end;
    begin = raster_vertices.begin();
    end = raster_vertices.end();
    int x1, y1, x2, y2;
    for(i_point = begin; i_point != end; ++i_point) {

        if (i_point == raster_vertices.begin()) {
            previous = i_point;
            continue;
        }

        x1 = previous->x;
        y1 = previous->y;
        x2 = i_point->x;
        y2 = i_point->y;
        lr.bresenham(x1, y1, x2, y2, frame_buffer, this->color);
        
        previous = i_point;
    }
    x1 = begin->x;
    y1 = begin->y;
    lr.bresenham(x1, y1, x2, y2, frame_buffer, this->color);  
    
}

void rtz::Polygon::reset(){
    int rows, cols;
    this->vertices.clear();
}


