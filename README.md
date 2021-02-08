# Passenger Ticket Sales Automation System
Implement a passenger ticket sales automation system by using stack and priority queue data structures on C language.

For this purpose; a list of the routes, flights, quotas and passengers must be read from the input file. Store the stacks and queues, I use dynamic memory allocation. There are three different seat classes for each flight: Business, Economy and
Standard. The number of seats in each class in each aircraft is indicated in the input file. Business and Economy class seats are limited. These seats are sold on the principle of "first come first served". However, according to the relevant law, "persons
with diplomatic identity" must be given priority in the business class. On the other hand, for the same law, veterans must be given priority in the economy class. In this project,
you must store “the empty seats in the Stack” and “passengers who want to buy tickets in the Priority Queue” data structure. At the end of the program, the output file is created with predetermined rules according to the given input file.


#### How it works

`$ sellticket [input file name] [output file name]`

`$ ./sellticket input.txt output.txt`

#### Some commands

![c1](https://user-images.githubusercontent.com/72974967/107273168-c2f1dc80-6a5f-11eb-91ff-66aac60cb16a.png)
![c2](https://user-images.githubusercontent.com/72974967/107273170-c2f1dc80-6a5f-11eb-8d18-063d08bde2e3.png)

#### Input format
![inputformat](https://user-images.githubusercontent.com/72974967/107273224-d00ecb80-6a5f-11eb-959d-6538c54a96bc.png)

#### Output file format
![outputformat](https://user-images.githubusercontent.com/72974967/107273228-d13ff880-6a5f-11eb-9f95-9febf2f09c79.png)
