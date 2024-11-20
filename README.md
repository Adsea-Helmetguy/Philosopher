# Philosopher
This is a project where you are to Design and implemented a solution to the classic 
Dining Philosophers Problem, applying concurrency management techniques to prevent 
deadlocks and ensure efficient resource sharing.

Here we learn about using pthreads and now we will come across the problem of:
DATA RACES.

Data Races — What Are They?
To put it simply, they are leaks that you will most likely use to check with:
-fsanitize=thread.

Data races is the main issue you will face in this project, it will occur when there
are 2 or more threads are trying to access and/or modify the same variable at the same time.
Your job is to prevent that.

What i meant for the above is that let's say one waiter takes one order(meatball noodles) and writes in the notepad 
located at the counter and then goes to get another order. However, the 2nd waiter who happens to also do the same thing,
erases the notepad and wrote his order(Chicken soup) instead. What is happening is that instead of writing like a list:
-------------------------
1st waiter
1)meatball noodle
2nd waiter
2)chicken soup
-------------------------


the notepad was written like this:
-------------------------
1st waiter
1)meatball noodle
2nd waiter
1)chicken soup
-------------------------
replacing the meatball order with chickensoup instead.

In order to prevent the above we must ensure that the 2nd waiter does not overwrite the 1)meatball noodle order until it's stored/used.
That's where Mutex comes in.
Taking the previous example we can avoid the overwrite by adding a lock in the deposit function. 
If 2nd waiter's chicken souo reaches the locked thread meatball noodle from 1st waiter, 2nd waiter will just have to wait until 
1st waiter is done saving the order(executing the code) and reaches the unlock, only then 2nd waiter will write down his order.

1)First Step: Checking Valid Input
Ensure that the program will receive 4 or 5 arguments only!
If anything else throw an error!

2)Second Step: creation of Structures
Using structures to save information is easier for me to do in this project.

3)Third Step: Initialization
For our project, the maximum amount of philosophers our program can be tested with is (200).
You can create a init_variable function first to init all variables.

4)Fourth Step: Thread Creation as well as philo's daily eat sleep and think
It bascially monitors the thread and ensures that loop runs and ends as soon as one of them is dead. 
For that, I created a dead flag for the philos. Should one of the philo does, the death flag will be = 1.
Should it be true, the project must free and exit cleanly

While it's not, the philo's, they will eat, sleep and think.

5)Fifth Step: Free all your own created mutex.
Basically free everything and exit cleanly like i mentioned in step 4.


Note:
Using and creating a usleep function and creating a function for getting the time is also important for this project.
