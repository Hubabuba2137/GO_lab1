# Dokumentacja modułu graficznego

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
- `void move(Vector2 vec)` – Przesuwa cały odcinek o zadany wektor.

---

## Struktura `Line`

Reprezentuje prostą, której równanie może być postaci:
- y = a*x + b (dla linii niepionowych),
- x = c (dla linii pionowych).

### Pola
- **a_coe** (`float`): Współczynnik kierunkowy (nachylenie).
- **b_coe** (`float`): Wyraz wolny (przecięcie z osią Y) lub wartość x dla linii pionowych.
- **start** (`Vector2`): Punkt początkowy linii.
- **end** (`Vector2`): Punkt końcowy linii.

### Konstruktor
- `Line(Node a, Node b)` – Oblicza współczynniki równania na podstawie dwóch węzłów.

### Metody
- `void draw(int window_x, bool write_text)` – Rysuje prostą. Jeśli parametr `write_text` jest ustawiony, wyświetla także równanie prostej.
- `bool solve_equation(float x, float y)` – Sprawdza, czy punkt o zadanych współrzędnych leży na prostej zgodnie z równaniem.

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
- `void draw()` – Rysuje wielokąt, w tym wszystkie krawędzie oraz węzły.
- `void add_vertex(Node node)` – Dodaje nowy węzeł do listy, a następnie aktualizuje krawędzie wielokąta.

---

## Funkcje pomocnicze

Funkcje te operują na strukturach zdefiniowanych w module, umożliwiając:
- Sprawdzanie, czy punkt leży na odcinku lub prostej.
- Ustalanie położenia punktu względem prostej.
- Tworzenie odbić punktu względem prostej lub odcinka.

### Lista funkcji

- `bool is_on_segment(Node node, Segment seg)`  
  Sprawdza, czy dany węzeł znajduje się na zadanym odcinku.

- `bool is_on_line(Node node, Line line)`  
  Sprawdza, czy dany węzeł leży na zadanej prostej, bazując na obliczeniach wg równania linii.

- `bool is_on_right_of_line(Node node, Line line)`  
  Określa, czy węzeł znajduje się po prawej stronie danej prostej, wykorzystując iloczyn wektorowy.

- `Node flip_node_around_line(Node node, Line line)`  
  Zwraca nowy węzeł będący odbiciem oryginalnego węzła względem zadanej prostej.

- `Node flip_node_around_segment(Node node, Segment seg)`  
  Zwraca nowy węzeł będący odbiciem oryginalnego węzła względem danego odcinka. Odbicie odbywa się poprzez rzutowanie względem prostej wyznaczonej przez końce odcinka.

---

## Przykłady użycia

```cpp
// Przykład wykorzystania struktury Vertex:
std::vector<Node> nodes = { Node(0, 0), Node(100, 0), Node(100, 100), Node(0, 100) };
Vertex polygon(nodes);
polygon.create_edges();
polygon.draw();

// Dodanie nowego punktu do wielokąta:
Node new_node(50, 150);
polygon.add_vertex(new_node);
polygon.create_edges();
polygon.draw();

// Przykład użycia funkcji pomocniczych:
Segment seg(Node(0, 0), Node(100, 0));
Node test_node(50, 0);
if (is_on_segment(test_node, seg)) {
    // ... wykonaj operacje, gdy węzeł leży na odcinku ...
}

Line line(Node(0, 0), Node(100, 100));
if (is_on_line(test_node, line)) {
    // ... wykonaj operacje, gdy węzeł leży na prostej ...
}

// Tworzenie odbicia punktu względem prostej:
Node flipped = flip_node_around_line(test_node, line);
```