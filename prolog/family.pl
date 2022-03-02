male(dan).%father
male(peter).%son1
male(patrick).%son2
male(bob).%pgrandfather
male(tom).%mgrandfather
male(jhon).%puncle
male(charles).%muncle
male(christopher).%pcousin

female(lera).%mother
female(keti).%daughter1
female(maria).%daughter2
female(sharon).%pgrandmother
female(joy).%mgrandmother
female(rose).%paunt
female(ann).%maunt
female(sonya).%mcousin

parent(dan, peter).
parent(lera, peter).
parent(dan, patrick).
parent(lera, patrick).
parent(dan, keti).
parent(lera, keti).
parent(dan, maria).
parent(lera, maria).

parent(bob, dan).
parent(sharon, dan).
parent(bob, jhon).
parent(sharon, jhon).
parent(bob, rose).
parent(sharon, rose).

parent(tom, lera).
parent(joy, lera).
parent(tom, charles).
parent(joy, charles).
parent(tom, ann).
parent(joy, ann).

parent(jhon, christopher).

parent(ann, sonya).


father(X, Y):- parent(X, Y), male(X).
mother(X, Y):-female(X), parent(X, Y).
son(X, Y):- parent(Y, X), male(X).
daughter(X, Y):- parent(Y, X), female(X).
brother(X, Y):- son(X, Z), parent(Z, Y), X\=Y.
sister(X, Y):- daughter(X, Z), parent(Z, Y), X\=Y.
maternal_grandfather(X, Y):-father(X, Z), mother(Z, Y).
maternal_grandmother(X, Y):-mother(X, Z), mother(Z, Y).
paternal_grandfather(X, Y):-father(X, Z), father(Z, Y).
paternal_grandmother(X, Y):-mother(X, Z), father(Z, Y).
maternal_uncle(X, Y):-brother(X, Z), mother(Z, Y).
maternal_aunt(X, Y):-sister(X, Z), mother(Z, Y).
paternal_uncle(X, Y):-brother(X, Z), father(Z, Y).
paternal_aunt(X, Y):-sister(X, Z), father(Z, Y).
paternal_cousin(X, Y):-parent(A, X), father(Z, Y), brother(Z, A).
maternal_cousin(X, Y):-parent(A, X), mother(Z, Y), sister(Z, A).
