% get a possible next move in a grid of size 5 * 5
move((X,Y), (X1,Y)) :- X > 0, X1 is X - 1.
move((X,Y), (X1,Y)) :- X < 4, X1 is X + 1.
move((X,Y), (X,Y1)) :- Y > 0, Y1 is Y - 1.
move((X,Y), (X,Y1)) :- Y < 4, Y1 is Y + 1.

% get a possible next state
get_next_state(state(Pos, Deliveries), state(NewPos, NewDeliveries)) :-
    move(Pos, NewPos), % get a possible move
    ( select(NewPos, Deliveries, NewDeliveries) -> true ; NewDeliveries = Deliveries ). %if newPos has a deivery then remove it from deliveries.

% heuristic function h(n)
heuristic(state(_, []), 0).
heuristic(state((X,Y), Deliveries), H) :-
    findall(Dist,
        (member((DX,DY), Deliveries),
         Dist is abs(X-DX) + abs(Y-DY)),
        Distances),
    min_list(Distances, H).

% main function
shortest_delivery_path(Deliveries, SolutionPath, TotalDistance) :-
    heuristic(state((0,0), Deliveries), H),
    search_delivery_paths([path_node(state((0,0),Deliveries), [], 0, H)], [], SolutionPath, TotalDistance).

% if my state has no remaining deliveries [], then I have finished.
search_delivery_paths([path_node(state(_,[]), Path, DistanceTravelled, _)|_], _, SolutionPath, DistanceTravelled) :-
    reverse(Path, SolutionPath).

search_delivery_paths([path_node(State, Path, DistanceTravelled, _)|OpenList], Visited, SolutionPath, TotalDistance) :-
        findall(path_node(NextState, [NextPos|Path], NewDistance, F),
        (
            get_next_state(State, NextState), % find all possible next states
            \+ member(NextState, Visited),    % check that i didn't visit them
            NextState = state(NextPos, _),    % get each state position
            NewDistance is DistanceTravelled + 1, % inc dist
            heuristic(NextState, H), %calc heuristic
            F is NewDistance + H % Fn = Gn + Hn
        ),
        GeneratedList),
    append(OpenList, GeneratedList, CombinedList), % compine the unvisited nodes with the new generated nodes
    predsort(compare_paths_nodes, CombinedList, SortedList), % sort to choose the least F the next iteration
    search_delivery_paths(SortedList, [State|Visited], SolutionPath, TotalDistance). % rec call

% compare path nodes based on F and then dist if f is equal
compare_paths_nodes(Order, path_node(_,_,Dist1,Fn1), path_node(_,_,Dist2,Fn2)) :-
    (Fn1 < Fn2 -> Order = '<' ;
    (Fn1 > Fn2 -> Order = '>' ;
    (Dist1 < Dist2 -> Order = '<' ;
     Order = '>'))).

% Test Run
% ?- shortest_delivery_path([(1,2), (2,3), (4,4)], Path, Distance).
% Path = [(1, 0), (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 4), (4, 4)],
% Distance = 8






