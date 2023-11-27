use std::f64::consts::PI;

fn main()
{
    let xstart = 70.0;
    let ystart = 153.0;
    const NB_ELTS: usize = 18;
    const NB_ANIM: usize = 60;
    let start_angle = 0.0;
    let elt_width = 6.0;
    let wave_amplitude = 30.0;

    let mut tx = [0.0; NB_ELTS];
    let mut ty = [0.0; NB_ELTS];
    for c in 0..NB_ANIM {
        for i in 0..NB_ELTS {
            let ii = (i + 1) as f64;
            let wave = wave_amplitude * ((ii * (NB_ANIM as f64 / NB_ELTS as f64) - c as f64) * 2.0 * PI / NB_ANIM as f64).sin(); 
            let angle = (start_angle + 2.0 * ii + wave) * PI / 180.0;
            tx[i] = xstart - ii * angle.cos() * elt_width / 1.6; 
            ty[i] = ystart - ii * angle.sin() * elt_width;
        }
        // Evenly distribute sprites on the path
        let mut total_length = 0.0;
        for i in 1..NB_ELTS {
            let dx = tx[i] - tx[i - 1];
            let dy = ty[i] - ty[i - 1];
            total_length += (dx * dx + dy * dy).sqrt();
        }
        let output_point_spacing = total_length / (NB_ELTS - 1) as f64;
        let mut txx = [0.0; NB_ELTS];
        let mut tyy = [0.0; NB_ELTS];
        txx[0] = tx[0];
        tyy[0] = ty[0];
        txx[NB_ELTS - 1] = tx[NB_ELTS - 1];
        tyy[NB_ELTS - 1] = ty[NB_ELTS - 1];
        let mut j = 1; // j is the index of new points
        let mut travelled_so_far = 0.0;
        let mut travelled;
        for i in 1..NB_ELTS {
            travelled = travelled_so_far;
            let dx = tx[i] - tx[i - 1];
            let dy = ty[i] - ty[i - 1];
            travelled_so_far += (dx * dx + dy * dy).sqrt();
            while j < NB_ELTS - 1 && travelled_so_far > j as f64 * output_point_spacing {
                // We should put a new point
                let portion = ((j as f64 * output_point_spacing) - travelled) / (travelled_so_far - travelled); 
                txx[j] = tx[i - 1] + dx * portion;
                tyy[j] = ty[i - 1] + dy * portion;
                j += 1;
            }
        }
        print!("const char dobkeratops_tail{c}_x[{NB_ELTS}] = {{");
        for i in 0..NB_ELTS {
            if i != 0 { print!(", "); }
            print!("{}", txx[i].round() as u8);
        }
        println!("}};");
        print!("const char dobkeratops_tail{c}_y[{NB_ELTS}] = {{");
        for i in 0..NB_ELTS {
            if i != 0 { print!(", "); }
            print!("{}", tyy[i].round() as u8);
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
