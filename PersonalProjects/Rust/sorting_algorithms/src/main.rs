
fn main() {
    
    // Create a list of values from 1 to 100
    let mut data: Vec<u32> = Vec::new();
    for i in 0..100 {
        data.push(i);
    }

    // Randomize Dataset
    fastrand::shuffle(&mut data);

    for n in &data {
        print!("{} ", n);
    }

    // Common Sorts
    
    // **** Bubble Sort ****
    for i in 0..data.len()-1 {
        for j in 0..data.len()-i-1 {
            if data[j] > data[j+1] {
                let x = data[j+1];
                data[j+1] = data[j];
                data[j] = x;

            }
        }
    }
    println!("");
    println!("");
    for n in &data {
        print!("{} ", n);
    }
    fastrand::shuffle(&mut data);

    
    // **** Insertion Sort ****
    for i in 0..data.len() {
        let mut min: u32= 0;
        for j in i..data.len()-1 {
            if j < min {
                min = j;
            }
        }
        data[i] = 
    }

    // Selection Sort

    // Merge Sort

    // Quick Sort

    // Bucket Sort


    // Silly Sorts

    // Stalin Sort

    // Bogo Sort
}
