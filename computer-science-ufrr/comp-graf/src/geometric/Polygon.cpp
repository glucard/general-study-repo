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

std::vector<rtz::Point> sutherland_hodgman(std::vector<rtz::Point> vertices, int x_min, int y_min, int x_max, int y_max) {
    // Inicialmente, o polígono a ser recortado é o de entrada.
    std::vector<rtz::Point> output = vertices;

    // Função auxiliar que recorta o polígono com base em uma determinada borda.
    // "inside" testa se um ponto está dentro da região para a borda atual.
    // "intersect" calcula a interseção entre uma aresta do polígono e a linha de recorte.
    auto clipEdge = [&](auto inside, auto intersect) -> void {
        std::vector<rtz::Point> input = output;
        output.clear();
        if (input.empty()) return;
        int n = input.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n; // garante fechamento do polígono
            rtz::Point current = input[i];
            rtz::Point next = input[j];

            bool currentInside = inside(current);
            bool nextInside = inside(next);

            if (currentInside && nextInside) {
                // Ambos os pontos estão dentro: adiciona o próximo.
                output.push_back(next);
            } else if (currentInside && !nextInside) {
                // Sai da região: adiciona o ponto de interseção.
                output.push_back(intersect(current, next));
            } else if (!currentInside && nextInside) {
                // Entra na região: adiciona o ponto de interseção e o próximo ponto.
                output.push_back(intersect(current, next));
                output.push_back(next);
            }
            // Se ambos estiverem fora, nada é adicionado.
        }
    };

    // Recorte pela borda esquerda: x >= x_min
    clipEdge(
        [&](const rtz::Point &p) -> bool { return p.x >= x_min; },
        [&](const rtz::Point &p1, const rtz::Point &p2) -> rtz::Point {
            float t = (float)(x_min - p1.x) / (p2.x - p1.x);
            int new_y = static_cast<int>(p1.y + t * (p2.y - p1.y));
            return rtz::Point(x_min, new_y);
        }
    );

    // Recorte pela borda direita: x <= x_max
    clipEdge(
        [&](const rtz::Point &p) -> bool { return p.x <= x_max; },
        [&](const rtz::Point &p1, const rtz::Point &p2) -> rtz::Point {
            float t = (float)(x_max - p1.x) / (p2.x - p1.x);
            int new_y = static_cast<int>(p1.y + t * (p2.y - p1.y));
            return rtz::Point(x_max, new_y);
        }
    );

    // Recorte pela borda inferior: y >= y_min
    clipEdge(
        [&](const rtz::Point &p) -> bool { return p.y >= y_min; },
        [&](const rtz::Point &p1, const rtz::Point &p2) -> rtz::Point {
            float t = (float)(y_min - p1.y) / (p2.y - p1.y);
            int new_x = static_cast<int>(p1.x + t * (p2.x - p1.x));
            return rtz::Point(new_x, y_min);
        }
    );

    // Recorte pela borda superior: y <= y_max
    clipEdge(
        [&](const rtz::Point &p) -> bool { return p.y <= y_max; },
        [&](const rtz::Point &p1, const rtz::Point &p2) -> rtz::Point {
            float t = (float)(y_max - p1.y) / (p2.y - p1.y);
            int new_x = static_cast<int>(p1.x + t * (p2.x - p1.x));
            return rtz::Point(new_x, y_max);
        }
    );

    return output;
}

void rtz::Polygon::raster(arr::Array2d frame_buffer, bool snipe) {

    if (this->vertices.size() < 3) {
        throw std::invalid_argument("Polygon must have at least 3 vertices");
        return;
    }
    
    std::vector<rtz::Point> raster_vertices = snipe ? sutherland_hodgman(vertices, 0, 0, frame_buffer.cols-1, frame_buffer.rows-1) : this->vertices;

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


