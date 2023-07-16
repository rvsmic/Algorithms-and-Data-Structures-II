# Algorithms and Data Structures II
All assignments and my solutions from the course Algorithms and Data Structures II at the Faculty of Mathematics, Physics and Computer Science at the Maria Curie-Skłodowska University in Lublin conducted by MSc Emil Benedykciuk (laboratories).

## Assignment 1: "Mrok" (Dark) - Dijkstra's Algorithm

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad1/zad1v7.cpp) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad1/zad1v7.cpp)

### Description:
A boy named Jonasz Las discovered the ability to travel in spacetime. He designed a machine that utilizes Cesium-137 and the Higgs field to create a miniature black hole.

However, the machine has flaws. To use and maintain it, the mentioned radioactive isotope of cesium needs to be replenished. This is only found in a few places on Earth, such as radioactive fallout and spent nuclear fuel. Luckily, Jonasz knows these locations and marked them on a map. Another flaw is that the machine is highly susceptible to deviations from the four cardinal points. Any deviation can result in the machine's destruction. To avoid this, Jonasz decides to move only in the four cardinal directions. He is aware that changing direction by 90 degrees disrupts the radioactive equilibrium within the machine and exposes him to radiation.

Therefore, he decides to use his machine for part of the journey, teleporting in one of the four cardinal directions, and walk the remaining part. This modification allows him to teleport any distance but only in one of the four cardinal directions. He can do this at any time, regardless of his previous direction. The cost of teleportation is low, consuming minimal amounts of the nuclide, not affecting the machine's lifespan but impacting its stability. Thus, he cannot use the machine again until it stabilizes, requiring it to be placed in the radioactive isotope of iodine-131, also found in the specified locations.

After plotting the radioactive isotope locations on a grid, he realizes that each of them intersects the x and y axes. One of these locations is where his beloved Marta is, and he wants to help her. After each stop, collecting cesium isotope and stabilizing the machine with iodine isotope, Jonasz can change the direction of movement and teleportation.

For Jonasz, the safety of his beloved and the machine is paramount, and the distance he walks is of utmost importance. The walking distance should be minimized due to the machine's instability and the potential radiation exposure to Jonasz. The number of locations he visits doesn't matter; there can be as many as necessary.

Write a program that enables Jonasz to plan his route to reach the destination location, where his chosen one is, and minimize the walking time. Assume that one unit on the grid equals one unit of distance to be minimized.

### Input:
The first line of input contains a natural number, n, indicating the number of isotope locations, numbered from 0 to n - 1. Then the program should read n sequences of data: x y, representing the coordinates of the stops on the grid plotted by Jonasz. Finally, the program should read two natural numbers, s and d, representing the indices of the starting and destination locations where Marta is located. Each location has different coordinates.

0 <= n <= 32 000

0 <= x, y, s, d <= 2 000 000 000

### Output:
The algorithm should output a single integer, which is the smallest possible number of distance units (walked) on the route from point s to point d.

### Example:

#### Input:
```
5
2 2
1 1
4 5
7 1
6 7
0 4
```
#### Output:
```
2
```


## Assignment 2: "Fortel króla" (King's ruse) - Hopcroft-Karp Algorithm

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad2) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad2/zad2odp.cpp)

### Description:
Elżbieta Harmonia, an avid checkers player, has become bored with the game due to her advanced prediction skills, logical thinking, and flawless gameplay. She is considering new rules and variations for the game.

She contemplates a square chessboard of dimensions N x N, where N is a natural number. The board squares are numbered from 0 to N - 1. Additionally, the pieces on the board can only be placed at the beginning of the game and cannot be moved thereafter. Continuing the game, the pawns must be arranged on all the board squares, meaning that white pawns occupy all the white squares and black pawns occupy all the black squares. Furthermore, the pawns are assigned one of four functions that determine which pawns they can capture and by which pawns they can be captured. The following pawn types are distinguished:

* 0 - Frozen pawn, unable to capture or be captured.
* 1 - A pawn captures one of the pawns located on squares: a square three units away directly ahead or a square two units away directly ahead and one unit to the right or left.
* 2 - A pawn captures one of the pawns located on squares: a square one unit away directly ahead or a square one unit to the right or left.
* 3 - A pawn captures one of the pawns located on squares: a square one unit away directly ahead or a square two units away directly ahead and one unit to the right or left.

It should be noted that Elżbieta has introduced an additional rule to simplify the game. If one pawn (A) can be captured by another pawn (B), then pawn (A) can also capture pawn (B). The direction of capture for white pawns is west (to the left), while for black pawns, it is east (to the right), and the top-left corner (northwest) is a black square.

The objective of the game is to arrange the pawns with the appropriate functions so that the fewest pawns remain on the chessboard. The winner is the person who, after analyzing the arrangement, has more remaining pawns. The analysis is conducted by seeking the largest possible connection between the fields of both players, resulting in the maximum number of pawn pairs being captured. Only the opponent's pawns are removed from the chessboard among these pawn pairs. During the analysis, only the connections generated by our pawns are considered, with the exclusion of our pawns and the opponent's pawns with a function of 0. The above analysis seems quite complex, so Elżbieta requests your help in implementing an engine that will assist in considering the gameplay. She asks you to implement an algorithm that determines the maximum number of pawns that will not be captured. Since Elżbieta's favorite color is black, write a program that analyzes the arrangement of black pawns and returns the number of pawns that will remain on the chessboard.

### Input:
The algorithm receives a natural number, N, indicating the size of the chessboard. It should then read N x N natural numbers that determine the functions of the pawns in their respective positions.

0 <= N <= 32 000

### Output:
The algorithm should output the maximum number of pawns that will remain on the board.

### Example:

#### Input:
```
5
1 1 1 1 1
1 1 1 1 1
0 0 1 0 1
1 1 1 1 1
1 1 1 1 1
```

#### Output:
```
19
```

## Assignment 3: "Izba z kart" (House of cards) - BST Tree

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad3) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad3/zad3odp.cpp)

### Description:
Our next assignment features Franciszek Podszyt, a ruthless advocate of party discipline in the Right Democratic Eagle party in the Polish Parliament. Despite his hard work during the parliamentary campaign, he was denied a high-ranking ministerial position by Minister Garrett Dudu. Determined to seek revenge on the head of government, our protagonist's first task was to uncover the reasons behind these decisions. However, he failed to reach any conclusive findings. Franciszek has been contemplating his next move and aims to continue his pursuit of discovering the source of these decisions. This time, he has a new idea for connecting clues and leads.

All the leads have been assigned values and associated with individuals close to Garrett Dudu. The value assigned to each clue represents the influence of political views, with higher values indicating more right-leaning ideologies. Importantly, the sequence of the appearing clues holds great significance since previous events influence the political perception of subsequent leads.

Based on his previous research, Podszyt claims that the correct leads belong to a relatively narrow subset of all the clues. He can even easily dismiss premises that do not belong to this narrow group. His experience suggests that the correct lead lies within a certain range of political influences, allowing him to exclude extreme leads from his considerations. This gives him a chance to identify the individuals who exert the greatest influence on the minister's decisions and eliminate those rivals from the political arena.

Previously, Franciszek was convinced that only one lead could be the correct one, but he has since changed his mind. He now believes that two particular clues are the source of the seemingly illogical decisions. Unfortunately, he only knows the sum of the political influences of these two premises, as their consequence is the current state of affairs. It should be noted that the estimation of the impact of political views on these significant events is subjective. Therefore, our inquisitive parliamentarian may not find the pair of clues that would reveal the reason behind his removal from the government.

Unfortunately, only one pair of clues is correct and will lead our protagonist to solve this puzzle. Franciszek knows that choosing the right pair of clues depends on the chronological order in which they are discovered. Additionally, he has noticed that to find the appropriate pair of leads, which is the source of the minister's decisions, he needs to identify a pair of clues with the smallest difference in political influence.

### Input:
The first line of input contains a natural number, n, representing the number of clues. The program should then read n values of political influence for the chronological order of the clues. Next, the program should read two values, a and b, representing the closed interval boundaries for the political influence values of the premises to be considered. Finally, the program should read the estimated value, k, representing the political influence that led to our protagonist's removal from the government.

0 <= n, k, a, b, political influence values for clues <= 2 000 000 000

### Output:
The program should output a pair of political influence values for the clues that would satisfy the value of k, or "NIE ZNALEZIONO" (not found) otherwise. The values of the pair should be displayed in non-decreasing order.

### Example:

#### Input:
```
7                              
15 10 20 8 12 16 25              
9 16            
25
```

#### Output:
```
10 15
```

## Assignment 4: "Mizerni ślepcy" (Peaky blinders) - Red-Black Tree

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad4) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad4/zad4odp.cpp)

### Description:
The events in this assignment take place in the 1920s, shortly after the end of World War I. It tells the story of Tomasz Ford, who is the chairman of the criminal organization "Mizerni ślepcy" (Miserable Blind). The organization instills fear due to its members wearing black sunglasses called "leonki." As sunglasses were gaining popularity around 1920, it was easy to remember and distinguish the activists of this group. The gang primarily consists of our protagonist's family members, who run a bookmaking business. However, our hero has ambitions to expand his influence, which has made him enemies.

Recently, Ford has been spending a lot of time analyzing a list of individuals who pose a potential threat to him. Among them are politicians, undercover agents, members of other gangs, uncompromising police inspector Czesław Obozowy, also known as Dzwon, and even a lady from a nearby greengrocer's. Our hero likes order, especially in his affairs. That's why his list is arranged from the most dangerous to the less dangerous individuals. Importantly, the positions on the list dynamically change. For example, if Mrs. Krysia from the greengrocer's suspiciously takes a long time to give change, Tomasz must update the list by moving it a few places higher. Occasionally, he performs other operations such as swapping positions between individuals or adding new ones. However, our hero is concerned that his notebook might fall into unauthorized hands, so he assigned unique pseudonyms to everyone. Managing such a notebook is challenging and time-consuming.

Nevertheless, our protagonist's intellect surpasses his time, and he came up with a brilliant idea. He designed a highly complex structure that allows for easy modifications and recreated this structure on a board in his secret hideout, known only to him. He attached the pseudonyms of his threatening individuals to the board using black or rust-colored nails. Based on specific rules, he performed operations on the board, such as swapping positions, by appropriately rearranging the nails. It should be noted that in the 1920s, there were no computers, let alone advanced self-organizing binary search tree data structures.

Your task is to recreate this advanced structure and present the list of the most dangerous rivals of our hero after he has performed certain specified operations on the list.

### Input:
The program receives the number, n, in the first line of input, indicating the initial number of people on the list. In the next n lines, the program receives character sequences, s, representing the pseudonyms of the individuals. We assume that the first person on the list poses the greatest threat to Tomasz. Next, the program receives the number, m, indicating the number of operations to perform. Finally, in m lines, the program receives operation descriptions. The first character always indicates the action to be performed, followed by the corresponding data according to the following description:

* a s - add a person with the pseudonym s to the end of the list, where s is a character sequence.
* m s x - move the person with the pseudonym s on the list by x positions, where s is a character sequence and x is an integer (positive x moves the person up the list, while negative x moves the person down).
* r s1 s2 - swap the positions of the person with the pseudonym s1 with the person with the pseudonym s2, where s1 and s2 are character sequences.

### Output:
The program should output the list of pseudonyms starting from the most dangerous person.

1 < n <= 50 000

1 < m <= 10 000

### Example:

#### Input:
```
5
Okruszek
Tester
Interfejs
Agent
Scyzoryk
4
r Okruszek Interfejs
a Kontakt
m Kontakt 2
m Interfejs -1
```

#### Output:
```
Tester
Interfejs
Okruszek
Kontakt
Agent
Scyzoryk
```

## Assignment 5: "Jenne" - Knuth-Morris-Pratt Algorithm

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad5) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad5/zad5v3.cpp)

### Description:

Jenne Adam, a young girl attending the "Never Again" Academy, faces various challenges as she navigates her new school, makes new friends, and takes on the role of a detective to solve a series of murders that have occurred in the academy. Jenne is highly intelligent and talented. Additionally, she discovers her psychic powers, manifested in the form of visions of the past and future. These powers are likely inherited from her mother, Mortycja Adam. Although she cannot control these visions, she experiences them when touching objects or individuals of significant importance to her.

During a poetry class on Wednesday, after touching a collection of works by Jan Brzechwa, she has another vision. Within the vision, there is a hidden message that could lead her closer to solving the mystery behind the series of murders at the "Never Again" Academy. To decipher the hidden message, she needs to find a sequence of words of a specific length.

### Input:
The input data consists of two lines. The first line contains the template of the desired phrase, and the second line contains the text in which a matching subword is to be found. The end of the input data is marked by a newline character.

The template can include the following characters:

* a - represents the occurrence of a lowercase letter,
* A - represents the occurrence of an uppercase letter,
* . - represents the occurrence of one of the following punctuation marks: period, question mark, exclamation point, comma, semicolon, colon, or hyphen,
* 0 - represents the occurrence of a digit.

The template can also contain spaces, which correspond to spaces in the desired text. The length of the text is longer than the length of the template and does not exceed 1500001 characters.

### Output:
The program should print T on standard output if the template given in the first line of input matches any subword of the text provided in the second line of input. Otherwise, it should print N.

### Example:
#### Input:
```
aaaaa a aaaaaaaa.
W Szczebrzeszynie chrzaszcz brzmi w trzcinie.
```
#### Output:
```
T
```

## Assignment 6: "Przecinak śniegu" (Snowpiercer) - Graham Scan - Convex Hull Algorithm

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Graham_scan) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad6) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad6/zad6odp.cpp)

### Description:
After unfortunate events on Earth, nuclear weapons led to a rise in temperature and the extinction of all animals. Scientists attempted to save the planet by using cooling bombs, which lowered the temperature to -120°C. The remnants of humanity sought refuge in a self-sustaining iron machine. This multi-level form of transportation was operated by an intelligent woman named Melania Ciosakk.

Mrs. Ciosakk analyzed how to restore a temperature on Earth that would enable life to thrive again. To do so, she marked places on the map where her advanced probes had collected promising readings. The area marked by the pins turned out to be a dense cluster of points. Melania saw potential in the overlapping heads of the pins. She believed that it was an area where she and her fellow travelers could return to a normal life.

However, a problem arose as the area seemed too small to accommodate all representatives of humanity aboard our heroine's machine. Therefore, Mrs. Ciosakk concluded that only a portion of the population residing in the mobile steel structure should remain there. The rest of the crew would return to this place when the inhabitable area expanded. Melania sought the simplest solution to verify whether the inhabitable area was growing. Unfortunately, she lacked advanced measuring tools on board. She noticed a thread from a knitted sweater on her desk. Without hesitation, Melania decided to loop the thread around all the pins on the map so that they were enclosed within the polygon formed by the thread. Although Melania's body was weary from numerous difficulties, her perceptive analytical mind never rested. Mrs. Ciosakk concluded that she needed to calculate the minimum length of thread required to enclose all the pins on her map. By repeating these steps during subsequent measurements when she inserted additional pins, she would know if more or less thread was needed. If more was needed, it meant that the inhabitable space on Earth was expanding.

### Input:
The input begins with a line containing the number n (3 ≤ n ≤ 1 000 000), indicating the number of pins. The following n lines contain integer coordinates x, y (-10 000 ≤ x, y ≤ 10 000) of each pin on the map.

### Output:
The output should display the minimum length of the thread, with a precision of 2 decimal places. The allowed error is 0.01.

### Example:

#### Input:
```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```

#### Output:
```
8.00
```

## Assignment 7: "Łamanie zła" (Breaking bad) - Numerical integration - rectangle method

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Rectangle_method) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/tree/main/zad7) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-II/blob/main/zad7/zad7odp.cpp)

### Description:
The protagonist of the story is a chemistry teacher named Walcerz, who lives in the Małopolskie Voivodeship and is diagnosed with stage three cancer. Given a prognosis of only two years to live, Walcerz decides to enter the dangerous world of non-alcoholic cooling beverages to secure his family financially. With the help of his best student, Jensen, he starts producing drinks that contain C10H15N among other ingredients.

To ensure the best taste and quality of the beverages, Walcerz and Jensen decide to adjust the proportions of the substances, taking into account the impact of temperature on the sensory experience. However, they face the challenge of maintaining the drinks at the optimal temperature without access to professional refrigerators or external assistance. They come up with the idea of using Walcerz's old aquarium, partially filled with icy water, to keep the drinks chilled. As Walcerz frequently samples the beverages, not all bottles are full, and there is a limited capacity in the aquarium. He fears that once the water overflows, his wife Bogumiła will uncover his operation.

Walcerz can easily determine the level of the drink in each bottle, but he struggles to convert it into volume due to the irregular shapes of the bottles. The bottle manufacturer provides him with a mathematical function describing the shape of the container, which is half of its cross-section. Help our hero estimate at which bottle the water in the aquarium will overflow.

### Input:
The program receives three natural numbers x, y, and z in the first line, representing the dimensions of the aquarium in centimeters. The next input is the value of p, which indicates the water level in the aquarium. In the next step, the program reads an integer n, followed by n floating-point numbers j describing the fill level of each bottle. It is assumed that the bottles have negligibly thin walls and are negligibly light. To check the radius of the bottle at any distance from the base, utilize the built-in function **double butelka(double cm)**. The base of the bottle is always located at point 0.

### Output:
The program should output the number of the bottle at which the aquarium overflows. The bottles are numbered starting from 1. If there is no water overflow, the program should display "NIE" (NO).

0 < x, y, z < 100

0 < p < 1

0 < n <= 150

### Example:

#### Input:
```
30 30 20
0.9
5
2.1
3.0
4.1
5.7
1.1
```

#### Output:
```
3
```

#### Function in the example:
```
double butelka(double cm) {
	return 10 - (cm-2) * (cm-2);
}
```