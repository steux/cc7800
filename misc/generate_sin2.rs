use std::f64::consts::PI;

fn main() {
    const NB_ELTS: usize = 64;
    let wave_amplitude = 127.0;

    let mut s = [0.0; NB_ELTS];
    for i in 0..NB_ELTS {
        let angle = (i as f64) / (NB_ELTS as f64) * PI / 2.0;
        s[i] = wave_amplitude * angle.sin();
    }
    print!("const signed char sin[{NB_ELTS}] = {{");
    for c in 0..NB_ELTS {
        if c != 0 {
            print!(", ");
        }
        print!("{}", s[c].round() as i8);
    }
    println!("}};");
}
