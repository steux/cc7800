use std::f64::consts::PI;

fn main()
{
    let xstart = 70.0;
    let ystart = 153.0;
    const NB_ELTS: usize = 18;
    const NB_ANIM: usize = 60;
    let start_angle = 0.0;
    let elt_width = 7.0;
    let wave_amplitude = 30.0;

    let mut tx = [0.0; NB_ELTS];
    let mut ty = [0.0; NB_ELTS];
    for c in 0..NB_ANIM {
        for i in 0..NB_ELTS {
            let ii = i as f64;
            let wave = wave_amplitude * ((ii * (NB_ANIM as f64 / NB_ELTS as f64) - c as f64) * 2.0 * PI / NB_ANIM as f64).sin(); 
            let angle = (start_angle + 2.0 * ii + wave) * PI / 180.0;
            tx[i] = xstart - ii * angle.cos() * elt_width / 1.6; 
            ty[i] = ystart - ii * angle.sin() * elt_width;
        } 
        print!("const char dobkeratops_tail{c}_x[{NB_ELTS}] = {{");
        for i in 0..NB_ELTS {
            if i != 0 { print!(", "); }
            print!("{}", tx[i].round() as u8);
        }
        println!("}};");
        print!("const char dobkeratops_tail{c}_y[{NB_ELTS}] = {{");
        for i in 0..NB_ELTS {
            if i != 0 { print!(", "); }
            print!("{}", ty[i].round() as u8);
        }
        println!("}};");
    }
    print!("const char *dobkeratops_tail_x[{NB_ANIM}] = {{");
    for c in 0..NB_ANIM {
        if c != 0 { print!(", "); }
        print!("dobkeratops_tail{c}_x");
    }
    println!("}};");
    print!("const char *dobkeratops_tail_y[{NB_ANIM}] = {{");
    for c in 0..NB_ANIM {
        if c != 0 { print!(", "); }
        print!("dobkeratops_tail{c}_y");
    }
    println!("}};");
}
