fn main () {
    /* Calculates the golden ratio, performing the operation 
    that defines it "iter" number of times */
    fn calc_golden_ratio(iter: u8) -> f64 {

        // Automatically short circuits if iter is ever higher than the
        // default max callstack depth of 64
        if iter > 64 {
            panic!("Number of iterations was greater than default max callstack depth of 64!");
        }

        // If we've done the requisite amount of calculating, start unwinding.
        if iter == 0 {
            return 1.0;
        }

        // Perform calulation recursively
        return 1.0 + (1.0/calc_golden_ratio(iter-1));
    }

    /* Calculates pi using the formula 1/1 - 1/3 + 1/5 - 1/7 ... = pi/4
    Multipies the result at each step by 4 to get the result to equal pi proper */
    fn calc_pi(iter: u8) -> f64 {

        // Automatically short circuits if iter is ever higher than the
        // default max callstack depth of 64
        if iter > 63 {
            panic!("Number of iterations results in greater than default max callstack depth of 64!");
        }

        return calc_pi_rec(1.0, iter, 1);
    }
    fn calc_pi_rec(pi: f64, iter: u8, negate: i8) -> f64 {

        // If we've done the requisite amount of calculating, start unwinding.
        if iter == 0 {
            return pi;
        }

        // Perform Calculation Recursively
        return 4.0/calc_pi_rec();
    }

    println!("Golden Ratio out to 63 Iterations: {}", calc_golden_ratio(63));
}
