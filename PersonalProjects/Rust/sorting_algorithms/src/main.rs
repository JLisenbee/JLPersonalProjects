


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
    
    // **** Bubble Sort **** //
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
    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");

    // Randomize Dataset
    fastrand::shuffle(&mut data);
    for n in &data {
        print!("{} ", n);
    }
    println!("");


    // **** Selection Sort **** //
    for i in 0..data.len() {
        let mut smallest = data[i];
        let mut ismall = i;
        for j in i..data.len() {
            // find the smallest number from i to end
            if data[j] < smallest {
                smallest = data[j];
                ismall = j;
            }
        }
        //At this point you've found the smallest item, so swap them
        let temp = data[ismall];
        data[ismall] = data[i];
        data[i] = temp;
    }
    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");

    // Randomize Dataset
    fastrand::shuffle(&mut data);
    for n in &data {
        print!("{} ", n);
    }

    // Merge Sort
    fn mergesort(array: Vec<u32>) -> Vec<u32>{
        if array.len() == 1 {
            return array;
        }
        else {
            // Compare first elements in the array, and return a combined array with the sub arrays correctly ordered
            let sub1= mergesort(array[..array.len()/2].to_vec());
            let sub2= mergesort(array[array.len()/2..].to_vec());

            println!("sub1[0]: {}\n sub2[0]: {}\n", sub1[0], sub2[0]);
            
            if sub1[0] > sub2[0] {
                return [sub1, sub2].concat();
            }
            else {
                return [sub2, sub1].concat();
            }
        }
    }
    data = mergesort(data); // Perform Sort

    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");


    // Quick Sort

    // Bucket Sort


    // Silly Sorts

    // Stalin Sort

    // Bogo Sort

    // Sleep Sort
}
