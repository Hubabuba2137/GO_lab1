﻿# Dokumentacja modułu graficznego

Poniżej znajduje się opis struktur oraz metod zaimplementowanych w module zawierającym funkcjonalności graficzne, które można znaleźć w [go_lib.hpp](d:/Code/Uczelnia/S4/GO/GO_lab01/go_lib.hpp).

---

## Struktura `Node`

Reprezentuje punkt na płaszczyźnie.

### Pola
- **pos** (`Vector2`): Pozycja punktu.
- **radius** (`float`): Promień wykorzystywany przy rysowaniu punktu (domyślnie 5.0).

### Konstruktorzy
- `Node(float x_in, float y_in)` – Inicjalizuje węzeł przyjmując współrzędne.
- `Node(Vector2 pos_in)` – Inicjalizuje węzeł przyjmując strukturę `Vector2`.
- `Node()` – Konstruktor domyślny.

### Metody
- `void draw()` – Rysuje punkt.
- `void move(Vector2 vec)` – Przesuwa punkt o zadany wektor.

---

## Struktura `Segment`

Reprezentuje odcinek utworzony przez dwa punkty.

### Pola
- **tab** (`Node[2]`): Tablica zawierająca dwa węzły, które definiują początek i koniec odcinka.

### Konstruktor
- `Segment(Node node_start, Node node_end)` – Tworzy odcinek przyjmując węzły początkowy i końcowy.

### Metody
- `bool solve_seg(float x, float y)` – Sprawdza, czy podane współrzędne (x, y) należą do odcinka.
- `void draw()` – Rysuje odcinek oraz powiązane punkty.
- `void move(Vector2)` – Przesuwa cały odcinek o zadany wektor.

---

## Struktura `Line`

Reprezentuje prostą, której równanie może być postaci:
- y = a*x + b (dla linii nie-pionowych),
- lub x = c (dla linii pionowych).

### Pola
- **a_coe** (`float`): Współczynnik kierunkowy (nachylenie).
- **b_coe** (`float`): Wyraz wolny (przecięcie z osią Y) lub wartość x dla linii pionowych.
- **start** (`Vector2`): Punkt początkowy linii.
- **end** (`Vector2`): Punkt końcowy linii.

### Konstruktor
- `Line(Node a, Node b)` – Oblicza współczynniki równania na podstawie dwóch węzłów.

### Metody
- `void draw(int window_x, bool write_text)` – Rysuje prostą. Jeśli parametr `write_text` jest ustawiony, wyświetla także równanie prostej.
- `bool solve_equation(float x, float y)` – Sprawdza, czy punkt o zadanych współrzędnych leży na prostej (porównując z równaniem y = a*x + b lub innym odpowiednim równaniem).

---

## Struktura `Vertex`

Reprezentuje wielokąt utworzony z węzłów oraz krawędzi (odcinków) tworzonych na podstawie tych punktów.

### Pola
- **vertices** (`std::vector<Node>`): Lista węzłów (punktów) wielokąta.
- **edges** (`std::vector<Segment>`): Lista krawędzi (odcinków) utworzonych na podstawie kolejnych węzłów.

### Konstruktorzy
- `Vertex(std::vector<Node> nodes)` – Inicjalizuje wielokąt na podstawie zadanej listy węzłów.
- `Vertex()` – Konstruktor domyślny.

### Metody
- `void create_edges()` – Tworzy krawędzie łącząc kolejne węzły. Ostatnia krawędź zamyka wielokąt, łącząc ostatni węzeł z pierwszym.
- `void draw()` – Rysuje wielokąt (wszystkie krawędzie oraz węzły).
- `void add_vertex(Node node)` – Dodaje nowy węzeł do listy, a następnie aktualizuje krawędzie wielokąta.

---

## Funkcje pomocnicze

Te funkcje operują na strukturach zdefiniowanych w module, umożliwiając sprawdzanie położenia punktów względem linii lub odcinków, a także tworzenie odbić punktów.

- `bool is_on_segment(Node node, Segment seg)`  
  Sprawdza, czy dany węzeł znajduje się na odcinku.

- `bool is_on_line(Node node, Line line)`  
  Sprawdza, czy dany węzeł leży na prostej (w oparciu o równanie prostej).

- `bool is_on_right_of_line(Node node, Line line)`  
  Określa, czy węzeł znajduje się po prawej stronie danej prostej (wykorzystuje iloczyn wektorowy).

- `Node flip_node_around_line(Node node, Line line)`  
  Zwraca nowy węzeł, będący odbiciem względem zadanej prostej.

- `Node flip_node_around_segment(Node node, Segment seg)`  
  Zwraca nowy węzeł, będący odbiciem względem odcinka. Funkcjonalność ta opiera się na wykorzystaniu funkcji odbicia względem prostej wyznaczonej przez końce odcinka.

---
