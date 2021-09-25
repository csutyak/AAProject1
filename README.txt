How to run our AAProject1: Flow Network
    There are five way to run our programs, and thus five ways to run our program.

    1. Command to run Breadth-First-Search implementation:
        ./main -b <graphFile.txt> s t
        * make sure to input a real graph file that is inside the graph folder
        * variable 's' represents the source, or the starting node of the BFS
        * variable 't' represents the target, or the ending node of the BFS
        * no other input is needed

    2. Command to run Ford-Fulkerson implementation:
        ./main -f <graphFile.txt>
        * make sure to input a real graph file that is inside the graph folder
            * no other input is needed

    3. Command to run circulation problem implementation:
        ./main -c <graphFile.txt>
            * make sure to input a real circulation file that is inside the graph folder
            * no other input is needed

    4. Command to run capacity scaling problem implementation:
        ./main -CF <graphfile.txt>
            * make sure to input a real capacity scaling file that is inside the graph folder
            * no other input is needed

    5. Command to run graph creator:
        ./main -g <graphfile.txt> n g
            * be careful what graphfile name is inputted. If the file already exists, it will be overwritten. The created file can be found in the 'graphs' folder
            * variable 'n' represents the node count of the new graph
            * variable 'g' represents the usage for the graph created. Depending on what is inputted, it will create a different kind of graph.
                ** accepts 'f' to create a graph with at least one source and one target node
                ** accepts 'c' to create a graph which will add demands to the graph with at least one source and one target node
            * no other input is needed

    Special note:
    ***All input graphs must go into graph folder!!!!!!!! :) ***
