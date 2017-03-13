use std::f64;

struct Mass {
    x: f64,
    y: f64,
    m: f64,
    x0: f64,
    y0: f64,
    xn: f64,
    yn: f64,
}

fn main() {
    
    let final_time : f64 = 10.0;
    let total_steps : i32 = 100;

    let m1 = Mass {x:10, y:0.01, m:1, x0:10, y0:0,
                   xn:0,yn:0};

    let m2 = Mass {x:0, y:0.0, m:1, x0:0, y0:0,
                   xn:0,yn:0};
    
   
   println!("Hello, world!");
}



