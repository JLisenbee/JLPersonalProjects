use std::io::{stdin, stdout, Read, Write};
struct Dice {
    num: u32,   // Number of dice to roll
    face: u32,  // Highest value face on the dice
}

fn main() {

    // TODO Read from a file on startup to get a list of default dice/previously created dice

    // Get the Die
    let die = parser(&get_die());
    println!("You are rolling {} dice with {} sides.\n", die.num, die.face);

    // Roll Die Function Here
    
    // Actually roll the dice
    let mut result: f32;        // Updated in loop with each newest loop
    let mut total: f32 = 0.0;         // Running Total
    let mut rolls: Vec<f32> = vec![];        // Running list of rolls
    for _i in 0..die.num {
        result = fastrand::u32(1..die.face) as f32;
        total = total + result;
        rolls.push(result);
    }

    // Print output
    print!("Your results are: ");
    for n in rolls { 
        print!("{} ", n.floor() as u32);
    }
    println!("\nThe total for your roll is: {}", total);

    // Give fun statistics
    let average: f32 = ((1.0 + die.face as f32) / 2.0) * die.num as f32;
    let distance: f32 = (total - average).abs();
    println!("The average for rolling this set up of dice is: {}", average);
    print!("You were {}% from the average, ", (((total - average)/average) * 100.0).round());

    // Under by more than 20%: Yikes!
    if total < average && distance > average * 0.2 {print!("yikes!");}
    // Under and Within 20%: So close!
    if total < average && distance <= average * 0.2 {print!("so close!");}
    // Over and within 20%: Nice roll!
    if total > average && distance <= average * 0.2 {print!("nice roll!");}
    // Over by more than 20%: Wow!
    if total > average && distance > average * 0.2 {print!("wow!");}
    // Exactly on: Perfectly balanced, as all things should be...
    if distance == 0.0 {print!("perfectly balanced as all things should be...");}

    println!("");

    // Pause the Program so the user can read it
    pause();

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

        // if d flag is false, count number of dice. 
        // do this by multiplying previously parsed digits by 10 and adding the newly parsed digit to the new ones place
        if !d_flag {
            newdie.num = newdie.num*10 + c.to_digit(10).unwrap();
        }

        // If d flag is true, count vaue of faces
        // do this by multiplying previously parsed digits by 10 and adding the newly parsed digit to the new ones place
        else {
            newdie.face = newdie.face*10 + c.to_digit(10).unwrap();
        }
    }

    return newdie;
}

// Retreives user input and returns it as a char array.
fn get_die() -> Vec<char> 
{
    // Prompt for die
    println!("Enter a dice in the format \"XdY\" where X is the number of dice to roll, and Y is the number of sides on each of those dice: ");
    let input: Vec<char>;

    // Scope brackets so input doesn't stick around
    {
        // Create empty string object to catch input
        let mut line = String::new();

        // Get input
        std::io::stdin().read_line(&mut line).unwrap();

        // Dissect string into a char array
        input = line.chars().collect();
    }

    return input;
}

// Pauses the program so it doesn't immediately end in release mode
fn pause() {
    let mut stdout = stdout();
    stdout.write(b"Press Enter to continue...").unwrap();
    stdout.flush().unwrap();
    stdin().read(&mut [0]).unwrap();
}