extern crate rand;

struct Dice {
    num: u32,   // Number of dice to roll
    face: u32,  // Highest value face on the dice
}

fn main() {

    // TODO Read from a file on startup to get a list of default dice/previously created dice

    // Prompt
    println!("Enter a dice in the format \"XdY\" where X is the number of dice to roll, and Y is the number of sides on each of those dice: ");

    let input: Vec<char>;

    // Scope brackets so input doesn't stick around
    {
        // Create empty string object to catch input
        let mut line = String::new();

        // Get input
        let bytes = std::io::stdin().read_line(&mut line).unwrap();

        // count the bytes for testing purposes
        println!("{} bytes of data read from input\n", bytes);

        // Dissect string into a char array
        input = line.chars().collect();
    }

    let die = parser(&input);

    println!("The number of dice you're rolling is {} and the size of dice you're rolling is {}. \n", die.num, die.face);

    // Actually roll the dice
    let mut values: Vec<u64>;       // Holds list of values
    let mut total: u64 = 0;         // Holds total of dice roll
    let rng = rand::thread_rng();   // Random number generator

    println!("Your values are: ");
    for i in 1..die.num+1 {
        let x = rng.gen_range(1, die.face+1);

        values.push(x);
        total = total + x;

        print!("{} ", x);
    }

    println!("For a total of: {}", total);
}

// Parses the user input and creates a Dice struct for ease of use through the program
fn parser(input: &Vec<char>) -> Dice
{
    let mut newdie = Dice {num: 0, face: 0,};   // New dice to be returned later.
    let mut d_flag = false;                     // turns to true once "d" is found, so we know to move on to counting number of faces

    // Loop through each element of the vector of chars
    for c in input {

        // Check for carriage return, line break, or end of string. If any is found, leave the loop
        if *c == '\r' || *c == '\0' || *c == '\n'{
            break;
        }

        // check to see if we're at the "d". if we are, just set the flag and skip over it
        if *c == 'd' || *c == 'D' {
            d_flag = true;
            continue;
        }

        // if we're at a space, ignore it
        if *c == ' ' {
            continue;
        }

        // if d flag is false, count number of dice
        if !d_flag {
            newdie.num = newdie.num*10 + c.to_digit(10).unwrap();
        }

        // If d flag is true, count vaue of faces
        else {
            newdie.face = newdie.face*10 + c.to_digit(10).unwrap();
        }
    }

    return newdie;
}