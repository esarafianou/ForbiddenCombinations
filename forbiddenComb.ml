

let comp a b = 
    if List.length a>List.length b then 1
    else if List.length a<List.length b then -1
    else 0;;

        
let parse fileName =
    let f = open_in fileName in
    let (n, m) = Scanf.fscanf f " %d %d" (fun n m -> (n, m)) in
    let forbidden = ref [] in
    for i = 1 to m do
        let k = Scanf.fscanf f " %d" (fun k -> k) in
        let combination = ref [] in
        for j = 1 to k do
            Scanf.fscanf f " %d" (fun x -> combination := x :: !combination)
        done;
    forbidden := (List.rev !combination) :: !forbidden
        done;
  (n, m, List.rev !forbidden)



let rec print res= 
    match res with
    [] ->  Printf.printf "\n"
    | [x] -> Printf.printf "%d\n" x
    | (x :: xs) -> Printf.printf "%d " x; print xs 
;;

let getfirst tup= 
    match tup with 
    (i,_,_) -> i;;

let getsecond tup= 
    match tup with
    (_,n,_) -> n;;

let getthird tup= 
    match tup with
    (_,_,n) -> n;;



let compint a b = 
    if a>b then 1
    else if a<b then -1
    else 0
;;


let push lst newlst = List.append lst newlst;;

let pop lst = 
    match lst with 
    []->((0,[],[]),[])
    |h::t->(h,t)
;;

let rec final big small res= 
    match big, small with
        [], _ -> res
        | l1, [] -> List.append res l1
        | (h1::t1), (h2::t2) -> 
                    if h1=h2 then final t1 t2 res
                    else final t1 (h2::t2) (h1::res)
;;

let rec createlist k lst = 
    match k with
        0 -> lst
        | _ -> createlist (k-1) (k::lst)
;;

let getlist n lst =
    let full = createlist n [] in
        List.sort compint (final full (List.sort compint lst) [])
;;


let rec fillforb head lst elem res = 
    match lst with
        [] -> head::res
        | h::t -> if h=elem then res
                  else fillforb head t elem res
;;		


let rec createnode num forb nd = 
    match forb with
    [] -> (num, getsecond nd, List.rev (getthird nd))
    | h::t ->
                    let newlist = fillforb h h num (getthird nd) in
                    let newnode = (num,getsecond nd, newlist) in 
                    createnode num t newnode
;;  


(* return list of children *)
let rec createchildren node lst children = 
    match lst with 
        [] -> children
        | h::t -> 
                    let child = createnode h (getthird node) (h,(h::(getsecond node)),[]) in
                    createchildren node t (child::children)
;;

let my_is_empty l = 
    match l with 
    [] -> true
    |_ -> false
;;

let rec checkchildren children = 
    match children with 
        [] -> []
        | h::t -> 
                   if my_is_empty (getthird h) then (getsecond h)
                   else checkchildren t
;;

let rec insertChildrenQ children q = 
    push q children
;;


let rec dowork n q forbidden = 
    let current = fst(pop q) in
    let newq = snd(pop q) in
    let newchildren =  createchildren current (List.hd (getthird current)) [] in 
    let check = checkchildren newchildren in
        if check = [] then 
            let newerq = insertChildrenQ newchildren newq in
            dowork n newerq forbidden
        else let final = getlist n check in
            print final 
;;

let danger = 
    let input = parse Sys.argv.(1) in
    let n=getfirst input in
    let forbidden=List.sort comp (getthird input) in
    let t=(0,[],forbidden) in
    let q=push [] [t] in
    dowork n q forbidden
;; 
