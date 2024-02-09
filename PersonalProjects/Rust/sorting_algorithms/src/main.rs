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
    println!("");

    // **** Merge Sort ****
    /* 
    fn mergesort(array: Vec<u32>) -> Vec<u32>{
        if array.len() <= 1 {
            return array;
        }
        else {
            // Compare first elements in the array, and return a combined array with the sub arrays correctly ordered
            let sub1= mergesort(array[..array.len()/2].to_vec());
            let sub2= mergesort(array[array.len()/2..].to_vec());

            return merge(sub1, sub2);
        }
    }
    fn merge() -> Vec<u32>{

    }
    data = mergesort(data); // Perform Sort

    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");
    */


    // Quick Sort

    // Bucket Sort


    // Silly Sorts

    // ***Stalin Sort***
    let mut gulag: Vec<u32> = Vec::new();
    gulag.resize(data.len(), 0);
    gulag.copy_from_slice(&data[..]);

    // Like bubble sort, but you just do one pass and any elements that aren't in order are deleted. linear time, but lossy
    let mut i = 0;
    while i < gulag.len()-1 {
        if gulag[i+1] < gulag[i] {
            gulag.remove(i+1);
        }
        else {
            i += 1;
        }
    }

    for m in &gulag {
        print!("{} ", m);
    }
    println!("");
    println!("");

    // No need to reshuffle data

    // **** Bogo Sort ****
    fn is_sorted(arr: &Vec<u32>) -> bool {
        for i in 0..arr.len()-1 {
            if arr[i] > arr[i+1] {return false}
        }
        return true;
    }

    // Reshuffle until list is sorted. God help you.
    let mut attempts = 0;
    while !is_sorted(&data) {
        fastrand::shuffle(&mut data);
        attempts += 1;
    }
    println!("Number of Bogosort Attempts until list was sorted: {}", attempts);

    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");

    // **** Sleep Sort ****
    /* 
    let mut sleepy: Vec<u32> = Vec::new();

    // Make a seperate thread for each value in the array
    for i in 0..data.len() {
        thread::scope(|s| {
            s.spawn(|| {

                let sleepdur = Duration::from_millis(data[i].into());
                // Each thread sleeps for a number of milliseconds equal to it's value
                thread::sleep(sleepdur);

                // Value is then inserted into the sleepy array
                sleepy.push(data[i]);
            });
        });
    }

    // move values from sleepy array to data array.
    data = Vec::from(sleepy);

    for n in &data {
        print!("{} ", n);
    }
    println!("");
    println!("");
    */

}
