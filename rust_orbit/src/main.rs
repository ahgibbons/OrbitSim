use std::f64;
use std::vec;

const G_CONST: f64 = 1.0;

struct Mass {
    x: f64,
    y: f64,
    m: f64,
    x0: f64,
    y0: f64,
    xn: f64,
    yn: f64,
}

fn grav(mass1: Mass, mass2: Mass) -> (f64,f64) {
    // GM1M2 / (r^3/2) * (x)
    let A = G_CONST * mass1.m * mass2.m;
    let dx = mass2.x - mass1.x;
    let dy = mass2.y - mass1.y;
    let r_2 = dx*dx + dy*dy;
    let r_32 = f64::powi(f64::sqrt(r_2),3);

    (A*dx/r_32, A*dy/r_32)
}

fn init_mass(x: f64, y: f64, vx: f64, vy: f64, dt: f64) -> Mass {
    let x1 = x + vx*dt;
    let y1 = y + vy*dt;
    Mass {x: x1, y: y1, m: 1.0, x0: x, y0: y, xn: 0.0, yn: 0.0}
}

fn verlet_step(r0: f64, r1: f64, a: f64, dt: f64) -> f64 {
    2.0*r1 - r0 + dt*dt*a
}

fn main() {
    let final_time : f64 = 10.0;
    let total_steps : i32 = 100;
    let dt : f64 = final_time / (total_steps as f64);
    let m1 = init_mass(10.0,0.0,0.0,0.3,dt);
    let m2 = init_mass(0.0,0.0,0.0,0.0,dt);

    let xs: Vec<f64> = vec![0.0;total_steps as usize];
    let ys: Vec<f64> = vec![0.0;total_steps as usize];
    let ts: Vec<f64> = vec![0.0;total_steps as usize];
    
    for i in 0..total_steps {
        println!("i is {}", i);
        }
    
    println!("dt is: {}", dt);
    println!("(fx,fy) is: ({}, {})", fx, fy);
    println!("Hello, world!");
}



