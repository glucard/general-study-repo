#include <stdio.h>
#include <stdexcept>

#define MAX_P = 40;

int len(char* s) {
    int i;
    for (i=0; s[i] != '\0'; i++);
    return i;
}

void chars_append_slice(char* s, char* s_complement, int start, int end){
    int length = len(s);
    int complement_length = len(s_complement);

    if (start < 0 || end > complement_length || start < end) {
        printf("invalid slice range (start=%d, end=%d, complement_length=%d)", start, end, length);
        throw std::invalid_argument("invalid slice range");
    }
    
    int slice_length = end - start;
    int i;
    for (i=0; i<slice_length; i++) s[length+i] = s_complement[start+i];
    s[length+i] = '\n';
}

int count_char(char* s, char c) {
    int i, count = 0;
    for (i=0; s[i] != '\n'; i++) if (s[i]==c) count++;
    return count; 
}

bool check_valid_triangle(char* triangle) {

    if (len(triangle) != 3){
        throw std::invalid_argument("triangle must have length 3");
        
    }
    return count_char(triangle, 'R') <= 1 ? true : false;
}

int count_triangles(char* platoons) {
    int p = len(platoons);

    if (p % 3 != 0){
        throw std::invalid_argument("invalid");
    }
    
    if (p == 3) {
        if (check_valid_triangle(platoons)){
            return 1;
        }
        return 0;
    }
    
    int count = 0, p1, p2, p3;
    for (p1=0; p1<p; p1++) {
        for (p2=p1+1; p2<p; p2++) {
            for (p3=p2+1; p3<p; p3++) {
                char triangle[MAX_P] = "23123";
                if (check_valid_triangle(format!("{}{}{}", &platoons[p1..p1+1], &platoons[p2..p2+1], &platoons[p3..p3+1]))) {
                    // if p1 != 0{
                    //     count += count_triangles((&platoons[0..p1]).to_string());
                    // }
                    if p2-1 != p1{
                        println!("platoons={}", platoons);
                        count += count_triangles((&platoons[p1+1..p2]).to_string());
                    }
                    if p3-1 != p2{
                        println!("platoons={}", platoons);
                        count += count_triangles((&platoons[p2+1..p3]).to_string());
                    }
                    if p3+1 != p{
                        println!("platoons={}", platoons);
                        count += count_triangles((&platoons[p3+1..p]).to_string());
                    }
                }
            }
        }
    }

    return count;
}

fn b_1058(){
    let platoons: String = String::from("BBBBBBBBBBBB");
    let p: usize = platoons.len();
    let valid_confs:i32 = count_triangles(platoons);
    println!("{}", valid_confs);
}


int main() {
    printf("version: %li\n", __cplusplus);
    return 0;
}