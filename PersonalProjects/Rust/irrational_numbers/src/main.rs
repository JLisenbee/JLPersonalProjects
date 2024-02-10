fn main() {
    fn calc_e(prev: f64, n: u8) -> f64 {
        if n > u8::MAX {return prev;}

        return calc_e(f64::powf(1.0+1.0/n as f64, n as f64 + 1.0), n+1);
    }
    let e = calc_e(0.0, 1);

    println!("{}", e);
}
