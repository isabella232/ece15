<!DOCTYPE TS>
<TS>
  <context>
    <name></name>
    <message>
      <source>getFontSize([&quot;name&quot;]) -> float

Returns the font size in points for the text frame &quot;name&quot;. If this text
frame has some text selected the value assigned to the first character of
the selection is returned.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getFontSize([&quot;name&quot;]) -> float

Vráti velikost písma v bodech rámce &quot;name&quot;. Jestliže je
vybrán nějaký text, vrátí velikost prvního znaku výběru.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getColorNames() -> list

Returns a list containing the names of all defined colors in the document.
If no document is open, returns a list of the default document colors.
</source>
      <translation>getColorNames() -> list

Vrátí seznam se jmény všech barev v dokumentu. Jestliže není žádný dokument
otevřen, vrátí seznam implicitních barev.</translation>
    </message>
    <message>
      <source>newDocDialog() -> bool

Displays the &quot;New Document&quot; dialog box. Creates a new document if the user
accepts the settings. Does not create a document if the user presses cancel.
Returns true if a new document was created.
</source>
      <translation>newDocDialog() -> bool

Zobrazí &quot;Nový dokument&quot; dialogové okno a vytvoří nový dokument poté, co
uživatel potvrdí nastavení. Nic nevytvoří, jestliže uživatel okno zruší. Vrátí true,
pokud je dokument vytvořen.</translation>
    </message>
    <message>
      <source>getFillColor([&quot;name&quot;]) -> string

Returns the name of the fill color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getFillColor([&quot;name&quot;]) -> string

Vrátí jméno výplňové barvy objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>moveObject(dx, dy [, &quot;name&quot;])

Moves the object &quot;name&quot; by dx and dy relative to its current position. The
distances are expressed in the current measurement unit of the document (see
UNIT constants). If &quot;name&quot; is not given the currently selected item is used.
If the object &quot;name&quot; belongs to a group, the whole group is moved.
</source>
      <translation>moveObject(dx, dy [, &quot;name&quot;])

Posune objekt &quot;name&quot; relativně o dx a dy vůči aktuální pozici. Vzdálenosti
jsou vyjádřeny v délkových jednotkách dokumentu (viz. konstanty UNIT).
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt. Jestliže &quot;name&quot;
patří do nějaké skupiny, je posunuta celá skupina.</translation>
    </message>
    <message>
      <source>setRedraw(bool)

Disables page redraw when bool = False, otherwise redrawing is enabled.
This change will persist even after the script exits, so make sure to call
setRedraw(True) in a finally: clause at the top level of your script.
</source>
      <translation>setRedraw(bool)

V případě false zruší překreslování stránek, jinak povolí. Tato změna přetrvá
i po ukončení skriptu, takže se ujistěte, že zavoláte setRedraw(true) v nejvyšší
úrovni skriptu.</translation>
    </message>
    <message>
      <source>createRect(x, y, width, height, [&quot;name&quot;]) -> string

Creates a new rectangle on the current page and returns its name. The
coordinates are given in the current measurement units of the document
(see UNIT constants). &quot;name&quot; should be a unique identifier for the object
because you need this name to reference that object in future. If &quot;name&quot;
is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
</source>
      <translation>createRect(x, y, width, height, [&quot;name&quot;]) -> string

Vytvoří nový čtyřúhelník na aktuální stránce a vráti jeho jméno. X, Y, W a H koordináty
jsou dány ve zvolených měrných jednotkách dokumentu (viz. konstanty UNIT*).
&quot;name&quot; musí být unikátní řetězec, protože slouží jako identifikátor. Jestliže není
&quot;name&quot; zadáno, Scribus jméno vytvoří sám.

Může vyvolat výjimku NameExistsError, když se pokusíte zduplikovat jméno.</translation>
    </message>
    <message>
      <source>newPage(where [,&quot;template&quot;])

Creates a new page. If &quot;where&quot; is -1 the new Page is appended to the
document, otherwise the new page is inserted before &quot;where&quot;. Page numbers are
counted from 1 upwards, no matter what the displayed first page number of your
document is. The optional parameter &quot;template&quot; specifies the name of the
template page for the new page.

May raise IndexError if the page number is out of range
</source>
      <translation>newPage(where [,&quot;template&quot;])

Vytvoří novou stránku. Jestliže je &quot;where&quot; -1, pak je nová stránka přidána na
konec dokumentu, jinak je vsazena před stránku &quot;where&quot;. Číslování stran je od 1,
a nezáleží na tom, jaké je číslo první stránky. Volitelný parametr &quot;template&quot; udává
jméno šablony, která bude aplikována na novou stránku.

Může vyvolat výjimku IndexError, když se pokusíte založit stránku na špatném místě</translation>
    </message>
    <message>
      <source>setGradientFill(type, &quot;color1&quot;, shade1, &quot;color2&quot;, shade2, [&quot;name&quot;])

Sets the gradient fill of the object &quot;name&quot; to type. Color descriptions are
the same as for setFillColor() and setFillShade(). See the constants for
available types (FILL_&lt;type>).
</source>
      <translation>setGradientFill(type, &quot;color1&quot;, shade1, &quot;color2&quot;, shade2, [&quot;name&quot;])

Nastaví gradient výplně objektu &quot;name&quot; na specifikovaný typ. Specifikace barev
je stejná jako v setFillColor() a setFillShade(). Dostupné gradienty viz.
konstanty FILL_&lt;typ>.</translation>
    </message>
    <message>
      <source>messagebarText(&quot;string&quot;)

Writes the &quot;string&quot; into the Scribus message bar (status line). The text
must be UTF8 encoded or 'unicode' string(recommended).
</source>
      <translation>messagebarText(&quot;string&quot;)

Zapíše řetězec &quot;string&quot; do stavového řádku Scribusu. Text musí být kódován
UTF8 nebo unicode (např. unicode(&quot;text&quot;, &quot;iso-8859-2&quot;)).</translation>
    </message>
    <message>
      <source>newDoc(size, margins, orientation, firstPageNumber,
                   unit, facingPages, firstSideLeft) -> bool

Creates a new document and returns true if successful. The parameters have the
following meaning:

    size = A tuple (width, height) describing the size of the document. You can
    use predefined constants named PAPER_&lt;paper_type> e.g. PAPER_A4 etc.

    margins = A tuple (left, right, top, bottom) describing the document
    margins

    orientation = the page orientation - constants PORTRAIT, LANDSCAPE

    firstPageNumber = is the number of the first page in the document used for
    pagenumbering. While you'll usually want 1, it's useful to have higher
    numbers if you're creating a document in several parts.

    unit: this value sets the measurement units used by the document. Use a
    predefined constant for this, one of: UNIT_INCHES, UNIT_MILLIMETERS,
    UNIT_PICAS, UNIT_POINTS.

    facingPages = FACINGPAGES, NOFACINGPAGES

    firstSideLeft = FIRSTPAGELEFT, FIRSTPAGERIGHT

The values for width, height and the margins are expressed in the given unit
for the document. PAPER_* constants are expressed in points. If your document
is not in points, make sure to account for this.

example: newDoc(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 1, UNIT_POINTS,
                FACINGPAGES, FIRSTPAGERIGHT)
</source>
      <translation>newDoc(size, margins, orientation, firstPageNumber, unit, facingPages, firstSideLeft) -> bool

Vytvoří nový dokument a vrátí true v případě úspěchu. Parametry mají tento význam:
    size - Tuple (šířka, výška) rozměrů velikost stránky. Viz. konstanty PAPER_&lt;typ> např. PAPER_A4.
    margins - Tuple (L, P, N, D) popisuje velikost okrajů stránky.
    orientation - Orienrace stránky. Viz. předdefinované konstanty PORTRAIT a LANDSCAPE.
    firstPageNumber - Číslo první stránky dokumentu, které je použito při automatickém číslování stran.
    unit - Nastaví typ měrných jednotek dokumentu. Viz. UNIT_INCHES, UNIT_MILLIMETERS,
             UNIT_PICAS, UNIT_POINTS.
    facingPages - FACINGPAGES, NOFACINGPAGES
    firstSideLeft - FIRSTPAGELEFT, FIRSTPAGERIGHT

Hodnoty výšky, šířky a okrajů jsou uvedeny ve specifikovaných měrných jednotkách dokumentu.
Konstanty PAPER_* jsou v bodech. Jestliže je dokument v jiných jednotkách, musíte provést
patřičnou konverzi.

příklad: newDoc(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 1, UNIT_POINTS, FACINGPAGES, FIRSTPAGERIGHT)</translation>
    </message>
  </context>
  <context>
    <name>@default</name>
    <message>
      <source>getFont([&quot;name&quot;]) -> string

Returns the font name for the text frame &quot;name&quot;. If this text frame
has some text selected the value assigned to the first character
of the selection is returned. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>getFont([&quot;name&quot;]) -> string

Vrátí jméno písma texttového rámce &quot;name&quot;. Jestliže je v rámu vybraný
nějaký text, pak vrátí písmo prvního znaku výběru.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getTextLength([&quot;name&quot;]) -> integer

Returns the length of the text in the text frame &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getTextLength([&quot;name&quot;]) -> integer

Vrátí délku textu textového rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getText([&quot;name&quot;]) -> string

Returns the text of the text frame &quot;name&quot;. If this text frame has some text
selected, the selected text is returned. All text in the frame, not just
currently visible text, is returned. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>getText([&quot;name&quot;]) -> string

Vrátí onsah textového rámce &quot;name&quot;. Jestliže je vrámu nějaký výběr, pak
je výsledkem obsah výběru. Vrátí celý text, ne jen viditelný.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getAllText([&quot;name&quot;]) -> string

Returns the text of the text frame &quot;name&quot; and of all text frames which are
linked with this frame. If this textframe has some text selected, the selected
text is returned. If &quot;name&quot; is not given the currently selected item is
used.
</source>
      <translation>getAllText([&quot;name&quot;]) -> string

Vrátí obsah textového rámce včetně kompletního textu všech zřetězených
rámů. Jestliže existuje nějaký výběr, pak je výsledkem obsah výběru.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getLineSpacing([&quot;name&quot;]) -> float

Returns the line spacing (&quot;leading&quot;) of the text frame &quot;name&quot; expressed in
points. If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getLineSpacing([&quot;name&quot;]) -> float

Vrátí velikost řádkování textového rámce &quot;name&quot; vyjádřené v bodech.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getColumnGap([&quot;name&quot;]) -> float

Returns the column gap size of the text frame &quot;name&quot; expressed in points. If
&quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getColumnGap([&quot;name&quot;]) -> float

Vrátí velikost mezisloupcové mezery textového rámce &quot;name&quot; vyjádřenou v bodech.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getColumns([&quot;name&quot;]) -> integer

Gets the number of columns of the text frame &quot;name&quot;. If &quot;name&quot; is not
given the currently selected item is used.
</source>
      <translation>getColumns([&quot;name&quot;]) -> integer

Vrátí počet sloupců textového rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>setText(&quot;text&quot;, [&quot;name&quot;])

Sets the text of the text frame &quot;name&quot; to the text of the string &quot;text&quot;.
Text must be UTF8 encoded - use e.g. unicode(text, 'iso-8859-2'). See the FAQ
for more details. If &quot;name&quot; is not given the currently selected item is
used.
</source>
      <translation>setText(&quot;text&quot;, [&quot;name&quot;])

Vyplní obsah textového rámce &quot;name&quot; textem &quot;text&quot;. Text musí být v UTF8
kódování - použijte např. unicode(text, 'iso-8859-2'). Viz. FAQ.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>insertText(&quot;text&quot;, pos, [&quot;name&quot;])

Inserts the text &quot;text&quot; at the position &quot;pos&quot; into the text frame. Text
must be UTF encoded (see setText() as reference) The first character has an
index of 0. &quot;name&quot; If &quot;name&quot; is not given the currently selected Item is
used.

May throw IndexError for an insertion out of bounds.
</source>
      <translation>insertText(&quot;text&quot;, pos, [&quot;name&quot;])

Vloží text &quot;text&quot; na pozici &quot;pos&quot; v textovém rámce &quot;name&quot;. Text musí být
v UTF8 kódování (viz. setText()). První znak rámce má pozici 0.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku IndexError, jestliže je &quot;pos&quot; mimo obsah rámce.</translation>
    </message>
    <message>
      <source>setFont(&quot;font&quot;, [&quot;name&quot;])

Sets the font of the text frame &quot;name&quot; to &quot;font&quot;. If there is some text
selected only the selected text is changed.  If &quot;name&quot; is not given the
currently selected item is used.

May throw ValueError if the font cannot be found.
</source>
      <translation>setFont(&quot;font&quot;, [&quot;name&quot;])

Nastaví písmo &quot;font&quot; textového rámce &quot;frame&quot;. Jestliže v rámci existuje
výběr, je písmo aplikováno pouze na něj.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, jestliže písmo neexistuje.</translation>
    </message>
    <message>
      <source>setFontSize(size, [&quot;name&quot;])

Sets the font size of the text frame &quot;name&quot; to &quot;size&quot;. &quot;size&quot; is treated
as a value in points. If there is some text selected only the selected text is
changed. &quot;size&quot; must be in the range 1 to 512. If &quot;name&quot; is not given the
currently selected item is used.

May throw ValueError for a font size that's out of bounds.
</source>
      <translation>setFontSize(size, [&quot;name&quot;])

Nastaví velikost písma textového rámce &quot;name&quot; na velikost &quot;size&quot;. Velikost
je vyjádřena v bodech. Jestliže je v rámu nějaký výběr, pak je změna
aplikována pouze na něj. Velikost musí být v intervalu &lt;1; 512>.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimlu ValueError, jestliže je velikost mimo interval.</translation>
    </message>
    <message>
      <source>setLineSpacing(size, [&quot;name&quot;])

Sets the line spacing (&quot;leading&quot;) of the text frame &quot;name&quot; to &quot;size&quot;.
&quot;size&quot; is a value in points. If &quot;name&quot; is not given the currently selected
item is used.

May throw ValueError if the line spacing is out of bounds.
</source>
      <translation>setLineSpacing(size, [&quot;name&quot;])

Nastaví řádkování textového rámu &quot;name&quot; na velikost &quot;size&quot;. Velikost
je uváděna v bodech.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, jestliže je velikost mimo rozsah.</translation>
    </message>
    <message>
      <source>setColumnGap(size, [&quot;name&quot;])

Sets the column gap of the text frame &quot;name&quot; to the value &quot;size&quot;. If
&quot;name&quot; is not given the currently selected item is used.

May throw ValueError if the column gap is out of bounds (must be positive).
</source>
      <translation>setColumnGap(size, [&quot;name&quot;])

Nastaví mezisloupcovou mezeru textového rámce &quot;name&quot; na velikost &quot;size&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, jestliže není velikost kladná hodnota.</translation>
    </message>
    <message>
      <source>setColumns(nr, [&quot;name&quot;])

Sets the number of columns of the text frame &quot;name&quot; to the integer &quot;nr&quot;.
If &quot;name&quot; is not given the currently selected item is used.

May throw ValueError if number of columns is not at least one.
</source>
      <translation>setColumns(nr, [&quot;name&quot;])

Nastaví počet sloupců textového rámce &quot;name&quot; na počet &quot;nr&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, jetsliže je &quot;nr&quot; menší něž 1.</translation>
    </message>
    <message>
      <source>setTextAlignment(align, [&quot;name&quot;])

Sets the text alignment of the text frame &quot;name&quot; to the specified alignment.
If &quot;name&quot; is not given the currently selected item is used. &quot;align&quot; should
be one of the ALIGN_ constants defined in this module - see dir(scribus).

May throw ValueError for an invalid alignment constant.
</source>
      <translation>setTextAlignment(align, [&quot;name&quot;])

Nastaví zarovnání textu rámce &quot;name&quot;. Jestliže není &quot;name&quot; uvedeno, použije
vybraný objekt. &quot;align&quot; by měla být jedna z předdefinovaných konstant ALIGN_*.

Může vyvolat výjimku ValueError, jestliže je &quot;align&quot; nepodporované číslo.</translation>
    </message>
    <message>
      <source>selectText(start, count, [&quot;name&quot;])

Selects &quot;count&quot; characters of text in the text frame &quot;name&quot; starting from the
character &quot;start&quot;. Character counting starts at 0. If &quot;count&quot; is zero, any
text selection will be cleared.  If &quot;name&quot; is not given the currently
selected item is used.

May throw IndexError if the selection is outside the bounds of the text.
</source>
      <translation>selectText(start, count, [&quot;name&quot;])

Označí jako vybraný počet &quot;count&quot; znaků v textovém rámci &quot;name&quot; od pozice
&quot;start&quot;. První znak rámce má pozici 0. Jestliže je &quot;count&quot; nula, výběr je zrušen.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku IndexError, jestliže je výběr mimo text rámce.</translation>
    </message>
    <message>
      <source>deleteText([&quot;name&quot;])

Deletes any text in the text frame &quot;name&quot;. If there is some text selected,
only the selected text will be deleted. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>deleteText([&quot;name&quot;])

Smaže text z textového rámce &quot;name&quot;. Jestliže je v rámu nějaký výběr,
pak je smazán pouze on. Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>setTextColor(&quot;color&quot;, [&quot;name&quot;])

Sets the text color of the text frame &quot;name&quot; to the color &quot;color&quot;. If there
is some text selected only the selected text is changed. If &quot;name&quot; is not
given the currently selected item is used.
</source>
      <translation>setTextColor(&quot;color&quot;, [&quot;name&quot;])

Nastaví barvu textu rámce &quot;name&quot; na barvu &quot;color&quot;. Jestliže v rámci
existuje výběr, pak je barva aplikována pouze na něj.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>setTextStroke(&quot;color&quot;, [&quot;name&quot;])

Set &quot;color&quot; of the text stroke. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>setTextStroke(&quot;color&quot;, [&quot;name&quot;])

Nastaví obrys textu na barvu &quot;color&quot; v textovém rámci &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>setTextShade(shade, [&quot;name&quot;])

Sets the shading of the text color of the object &quot;name&quot; to &quot;shade&quot;. If
there is some text selected only the selected text is changed. &quot;shade&quot; must
be an integer value in the range from 0 (lightest) to 100 (full color
intensity). If &quot;name&quot; is not given the currently selected item is
used.
</source>
      <translation>setTextShade(shade, [&quot;name&quot;])

Nastaví stín textu v textovém rámci &quot;name&quot; na hodnotu &quot;shade&quot;. Jetsliže
v rámci existuje výběr, pak je aplikován pouze na něj. Stín musí být celé
číslo z intervalu &lt;1; 100>.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>linkTextFrames(&quot;fromname&quot;, &quot;toname&quot;)

Link two text frames. The frame named &quot;fromname&quot; is linked to the
frame named &quot;toname&quot;. The target frame must be an empty text frame
and must not link to or be linked from any other frames already.

May throw ScribusException if linking rules are violated.
</source>
      <translation>linkTextFrames(&quot;fromname&quot;, &quot;toname&quot;)

zřetězí dva textové rámce. Rámec &quot;fromname&quot; je před rámcem &quot;toname&quot;.
&quot;toname&quot; musí být prázdný a ještě neslinkovaný textový rámec.

Může vyvolat výjimku ScribusException, jestliže jsou porušena pravidla řetězení.</translation>
    </message>
    <message>
      <source>unlinkTextFrames(&quot;name&quot;)

Remove the specified (named) object from the text frame flow/linkage. If the
frame was in the middle of a chain, the previous and next frames will be
connected, eg 'a->b->c' becomes 'a->c' when you unlinkTextFrames(b)'

May throw ScribusException if linking rules are violated.
</source>
      <translation>unlinkTextFrames(&quot;name&quot;)

Odstraní objekt &quot;name&quot; ze zřetězených textových rámců. Např. sekvence
a->b->c bude a->c po vykonání unlinkTextFrames(b)

Může vyvolat výjimku ScribusException, jestliže jsou porušena pravidla zřetězení.</translation>
    </message>
    <message>
      <source>traceText([&quot;name&quot;])

Convert the text frame &quot;name&quot; to outlines. If &quot;name&quot; is not given the
currently selected item is used.</source>
      <translation>traceText([&quot;name&quot;])

Převede textový rámec &quot;name&quot; na křivky.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getColor(&quot;name&quot;) -> tuple

Returns a tuple (C, M, Y, K) containing the four color components of the
color &quot;name&quot; from the current document. If no document is open, returns
the value of the named color from the default document colors.

May raise NotFoundError if the named color wasn't found.
May raise ValueError if an invalid color name is specified.
</source>
      <translation>getColor(&quot;name&quot;) -> tuple

Vrátí CMYK složky barvy &quot;name&quot; daného dokumentu. Jestliže není otevřený
žádný dokument, vrátí složky implicitní barvy &quot;name&quot;.

Může vyvolat výjimky NotFoundError (jestliže barvu nenajde) a
ValueError (chybné parametry).</translation>
    </message>
    <message>
      <source>changeColor(&quot;name&quot;, c, m, y, k)

Changes the color &quot;name&quot; to the specified CMYK value. The color value is
defined via four components c = Cyan, m = Magenta, y = Yellow and k = Black.
Color components should be in the range from 0 to 255.

May raise NotFoundError if the named color wasn't found.
May raise ValueError if an invalid color name is specified.
</source>
      <translation>changeColor(&quot;name&quot;, c, m, y, k)

Změní barvu &quot;name&quot; na specifikované CMYK hodnoty &quot;c&quot;, &quot;m&quot;, &quot;y&quot;, &quot;k&quot;.
Každá z barevných komponenty musí být z intervalu &lt;0; 255>.

Může vyvolat výjimky NotFoundError (barva neexistuje) a ValueError
(chybné parametry).</translation>
    </message>
    <message>
      <source>deleteColor(&quot;name&quot;, &quot;replace&quot;)

Deletes the color &quot;name&quot;. Every occurence of that color is replaced by the
color &quot;replace&quot;. If not specified, &quot;replace&quot; defaults to the color
&quot;None&quot; - transparent.

deleteColor works on the default document colors if there is no document open.
In that case, &quot;replace&quot;, if specified, has no effect.

May raise NotFoundError if a named color wasn't found.
May raise ValueError if an invalid color name is specified.
</source>
      <translation>deleteColor(&quot;name&quot;, &quot;replace&quot;)

Smaže barvu &quot;name&quot;. každý výskyt této barvy je nahrazen  barvou &quot;replace&quot;.
Jestliže není &quot;replace&quot; uvedena, zamění mazanou barvu transparentní 
průhlednou &quot;None&quot;.
Jestliže není otevřený žádný dokument pracuje deleteColor s imlicitní
barevnou množinou. &quot;replace&quot; potom nemá žádnou funkčnost.

Může vyvolat výjimky NotFoundError (barva neexistuje) a ValueError
(chybné parametry).</translation>
    </message>
    <message>
      <source>replaceColor(&quot;name&quot;, &quot;replace&quot;)

Every occurence of the color &quot;name&quot; is replaced by the color &quot;replace&quot;.

May raise NotFoundError if a named color wasn't found.
May raise ValueError if an invalid color name is specified.
</source>
      <translation>replaceColor(&quot;name&quot;, &quot;replace&quot;)

Každý výskyt barvy &quot;name&quot; je nahrazen barvou &quot;replace&quot;.
Může vyvolat výjimky NotFoundError (barva neexistuje) a ValueError
(chybné parametry).</translation>
    </message>
    <message>
      <source>fileDialog(&quot;caption&quot;, [&quot;filter&quot;, &quot;defaultname&quot; ,haspreview, issave]) -> string with filename

Shows a File Open dialog box with the caption &quot;caption&quot;. Files are filtered
with the filter string &quot;filter&quot;. A default filename or file path can also
supplied, leave this string empty when you don't want to use it.  A value of
True for haspreview enables a small preview widget in the FileSelect box.  When
the issave parameter is set to True the dialog acts like a &quot;Save As&quot; dialog
otherwise it acts like a &quot;File Open Dialog&quot;. The default for both of the
opional parameters is False.

The filter, if specified, takes the form 'comment (*.type *.type2 ...)'.
For example 'Images (*.png *.xpm *.jpg)'.

Refer to the Qt-Documentation for QFileDialog for details on filters.

Example: fileDialog('Open input', 'CSV files (*.csv)')
Example: fileDialog('Save report', defaultname='report.txt', issave=True)
</source>
      <translation>fileDialog(&quot;caption&quot;, [&quot;filter&quot;, &quot;defaultname&quot; ,haspreview, issave]) -> string with filename

Zobrazí souborové okno/dialog s titulkem &quot;caption&quot;. Soubory mohou být vybrány
podle masky &quot;filter&quot;. Parametr &quot;defaultname&quot; může být použit jako předem nastavená
implicitní cesta. Jestliže je &quot;haspreview&quot; nastaveno na true, bude mít uřivatel
k dispozici náhled vybraných souborů. Jestliže je parametr &quot;issave&quot; nastaven
na true, bude se dialog chovat jako klasický &quot;Uložit jako&quot;.
Maska filtrování souborů může vypadat např. takto: 'Obrázky (*.png *.jpg)'.
Více informací neleznete v dokumentaci Qt.
Příklad: fileDialog('Open input', 'CSV files (*.csv)')
Nebo: fileDialog('Save report', defaultname='report.txt', issave=True)</translation>
    </message>
    <message>
      <source>messageBox(&quot;caption&quot;, &quot;message&quot;,
    icon=ICON_NONE, button1=BUTTON_OK|BUTTONOPT_DEFAULT,
    button2=BUTTON_NONE, button3=BUTTON_NONE) -> integer

Displays a message box with the title &quot;caption&quot;, the message &quot;message&quot;, and
an icon &quot;icon&quot; and up to 3 buttons. By default no icon is used and a single
button, OK, is displayed. Only the caption and message arguments are required,
though setting an icon and appropriate button(s) is strongly
recommended. The message text may contain simple HTML-like markup.

Returns the number of the button the user pressed. Button numbers start
at 1.

For the icon and the button parameters there are predefined constants available
with the same names as in the Qt Documentation. These are the BUTTON_* and
ICON_* constants defined in the module. There are also two extra constants that
can be binary-ORed with button constants:
    BUTTONOPT_DEFAULT   Pressing enter presses this button.
    BUTTONOPT_ESCAPE    Pressing escape presses this button.

Usage examples:
result = messageBox('Script failed',
                    'This script only works when you have a text frame selected.',
                    ICON_ERROR)
result = messageBox('Monkeys!', 'Something went ook! &lt;i>Was it a monkey?&lt;/i>',
                    ICON_WARNING, BUTTON_YES|BUTTONOPT_DEFAULT,
                    BUTTON_NO, BUTTON_IGNORE|BUTTONOPT_ESCAPE)

Defined button and icon constants:
BUTTON_NONE, BUTTON_ABORT, BUTTON_CANCEL, BUTTON_IGNORE, BUTTON_NO,
BUTTON_NOALL, BUTTON_OK, BUTTON_RETRY, BUTTON_YES, BUTTON_YESALL,
ICON_NONE, ICON_INFORMATION, ICON_WARNING, ICON_CRITICAL.
</source>
      <translation>messageBox(&quot;caption&quot;, &quot;message&quot;, icon=ICON_NONE, button1=BUTTON_OK|BUTTONOPT_DEFAULT,
                   button2=BUTTON_NONE, button3=BUTTON_NONE) -> integer

Zobrazí message box s titulkem &quot;caption&quot;, textem &quot;message&quot;, ikonou &quot;icon&quot;
a několika tlačítky. Implicitně není nastavena žádná ikona a zobrazí se jediné
tlačitko (OK). Povinné jsou tedy pouze parametry &quot;caption&quot; a &quot;message&quot;.
&quot;message&quot; může obsahovat jednoduché HTML značky.
Vrátí číslo tlačítka, které uživatel stisknul. Tlačítka jsou číslována od 1.
Jednotlivé typy ikon a tlačitek mají své předdefinované konstanty. Jsou to
BUTTON_* a ICON_*. Existují také dvě konstanty, které mohou být použity
v binárním OR s BUTTON konstantami:
    BUTTONOPT_DEFAULT nastaví příznak &quot;stisk enteru stiskne tlačítko&quot;
    BUTTONOPT_ESCAPE nastaví příznak &quot;stisk escape stiskne tlačítko&quot;
Příklady:
    result = messageBox('Script failed',
                                   'This script only works when you have a text frame selected.',
                                   ICON_ERROR)
    result = messageBox('Monkeys!', 
                                   'Something went ook! &lt;i>Was it a monkey?&lt;/i>',
                                   ICON_WARNING, BUTTON_YES|BUTTONOPT_DEFAULT,
                                   BUTTON_NO, BUTTON_IGNORE|BUTTONOPT_ESCAPE)
Konstanty: BUTTON_NONE, BUTTON_ABORT, BUTTON_CANCEL, 
    BUTTON_IGNORE, BUTTON_NO, BUTTON_NOALL, BUTTON_OK,
    BUTTON_RETRY, BUTTON_YES, BUTTON_YESALL,
    ICON_NONE, ICON_INFORMATION, ICON_WARNING, ICON_CRITICAL.</translation>
    </message>
    <message>
      <source>valueDialog(caption, message [,defaultvalue]) -> string

Shows the common 'Ask for string' dialog and returns its value as a string
Parameters: window title, text in the window and optional 'default' value.

Example: valueDialog('title', 'text in the window', 'optional')
</source>
      <translation>valueDialog(caption, message [,defaultvalue]) -> string

Zobrazí jednoduchý dialog, do kterého uživatel zadává hodnotu,
kterou vráti skriptu jako string. Okno má titulek &quot;caption&quot;,
text &quot;message&quot; a může zobrazit implicitní hodnotu &quot;defaultvalue&quot;.
Např.: valueDialog('title', 'text in the window', 'optional')</translation>
    </message>
    <message>
      <source>closeDoc()

Closes the current document without prompting to save.

May throw NoDocOpenError if there is no document to close
</source>
      <translation>closeDoc()

Zavře aktuální dokument bez výzvy k uložení.

Může vyvolat výjimku NoDocOpenError, kdyý enní žádný dokument otevřen</translation>
    </message>
    <message>
      <source>haveDoc() -> bool

Returns true if there is a document open.
</source>
      <translation>haveDoc() -> bool

Vrátí true, když je otevřený jakýkoli dokument.</translation>
    </message>
    <message>
      <source>openDoc(&quot;name&quot;)

Opens the document &quot;name&quot;.

May raise ScribusError if the document could not be opened.
</source>
      <translation>openDoc(&quot;name&quot;)

Otevře dokument &quot;name&quot;.

Může vyvolat výjimku ScribusError, když dokument nejde otevřít.</translation>
    </message>
    <message>
      <source>saveDoc()

Saves the current document with its current name, returns true if successful.
If the document has not already been saved, this may bring up an interactive
save file dialog.

If the save fails, there is currently no way to tell.
</source>
      <translation>saveDoc()

Uloží aktuální dokument pod platným jménem. Vrátí true v případě úspěchu.
Jestliže nebyl dokument ještě niky uložen, zobrazí se &quot;Uložit jako&quot; okno.
Jestliže ukladání selže, neexituje žádný způsob, jak toto zjistit.</translation>
    </message>
    <message>
      <source>saveDocAs(&quot;name&quot;)

Saves the current document under the new name &quot;name&quot; (which may be a full or
relative path).

May raise ScribusError if the save fails.
</source>
      <translation>saveDocAs(&quot;name&quot;)

Uloží aktuální dokument pod jménem &quot;name&quot;. &quot;name&quot; může být jak celá, tak
relativní cesta souborového systému.

Může vyvolat výjimku ScribusError, jestliže ukládání selže.</translation>
    </message>
    <message>
      <source>saveDocAs(&quot;author&quot;, &quot;info&quot;, &quot;description&quot;) -> bool

Sets the document information. &quot;Author&quot;, &quot;Info&quot;, &quot;Description&quot; are
strings.
</source>
      <translation>saveDocAs(&quot;author&quot;, &quot;info&quot;, &quot;description&quot;) -> bool

Nastaví informace o dokumentu. Parametry jsou textové řetězce.</translation>
    </message>
    <message>
      <source>setMargins(lr, rr, tr, br)

Sets the margins of the document, Left(lr), Right(rr), Top(tr) and Bottom(br)
margins are given in the measurement units of the document - see UNIT_&lt;type>
constants.
</source>
      <translation>setMargins(lr, rr, tr, br)

Nastaví okraje dokumentu - levý, pravý, horní a spodní okraj je zadáván
v aktuálních měrných jednotkách dokumentu. Viz. konstanty UNIT_typ.</translation>
    </message>
    <message>
      <source>setUnit(type)

Changes the measurement unit of the document. Possible values for &quot;unit&quot; are
defined as constants UNIT_&lt;type>.

May raise ValueError if an invalid unit is passed.
</source>
      <translation>setUnit(type)

Změní měrné jednotky dokumentu. Možná nastavení jsou definována jako
konstanty UNIT_*.

Může vyvolat výjimku ValueError při nepodporovaném typu jednotky.</translation>
    </message>
    <message>
      <source>getUnit() -> integer (Scribus unit constant)

Returns the measurement units of the document. The returned value will be one
of the UNIT_* constants:
UNIT_INCHES, UNIT_MILLIMETERS, UNIT_PICAS, UNIT_POINTS.
</source>
      <translation>getUnit() -> integer (Scribus unit constant)

Vrátí typ měrné jednotky dokumentu. Návratová hodnota je jednou z UNIT_*
konstant: UNIT_INCHES, UNIT_MILLIMETERS, UNIT_PICAS, UNIT_POINTS.</translation>
    </message>
    <message>
      <source>loadStylesFromFile(&quot;filename&quot;)

Loads paragraph styles from the Scribus document at &quot;filename&quot; into the
current document.
</source>
      <translation>loadStylesFromFile(&quot;filename&quot;)

Nahraje styly odstavce z dokumentu &quot;filename&quot; do dokumentu aktuálního.</translation>
    </message>
    <message>
      <source>setDocType(facingPages, firstPageLeft)

Sets the document type. To get facing pages set the first parameter to
FACINGPAGES, to switch facingPages off use NOFACINGPAGES instead.  If you want
to be the first page a left side set the second parameter to FIRSTPAGELEFT, for
a right page use FIRSTPAGERIGHT.
</source>
      <translation>setDocType(facingPages, firstPageLeft)

Nastaví typ dokumentu. Parametr facingPages může být FACINGPAGES (dvoustrany)
nebo NOFACINGPAGES (jedna strana). Jestliže chcete, aby dokument začínal
levou stranou nastavte firstPageLeft na FIRSTPAGELEFT, jinak na FIRSTPAGERIGHT.</translation>
    </message>
    <message>
      <source>getLineColor([&quot;name&quot;]) -> string

Returns the name of the line color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getLineColor([&quot;name&quot;]) -> string

Vrátí jméno barvy čar objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getLineWidth([&quot;name&quot;]) -> integer

Returns the line width of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
      <translation>getLineWidth([&quot;name&quot;]) -> integer

Vrátí tloušťku čáry objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getLineShade([&quot;name&quot;]) -> integer

Returns the shading value of the line color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getLineShade([&quot;name&quot;]) -> integer

Vrátí stín barvy objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getLineJoin([&quot;name&quot;]) -> integer (see contants)

Returns the line join style of the object &quot;name&quot;. If &quot;name&quot; is not given
the currently selected item is used.  The join types are:
JOIN_BEVEL, JOIN_MITTER, JOIN_ROUND
</source>
      <translation>getLineJoin([&quot;name&quot;]) -> integer (see contants)

Vrátí typ spojení čar objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Typy spojení: JOIN_BEVEL, JOIN_MITTER, JOIN_ROUND</translation>
    </message>
    <message>
      <source>getLineEnd([&quot;name&quot;]) -> integer (see constants)

Returns the line cap style of the object &quot;name&quot;. If &quot;name&quot; is not given the
currently selected item is used. The cap types are:
CAP_FLAT, CAP_ROUND, CAP_SQUARE
</source>
      <translation>getLineEnd([&quot;name&quot;]) -> integer (see constants)

Vrátí typ ukončení čáry objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Typy jsou: CAP_FLAT, CAP_ROUND, CAP_SQUARE</translation>
    </message>
    <message>
      <source>getLineStyle([&quot;name&quot;]) -> integer (see constants)

Returns the line style of the object &quot;name&quot;. If &quot;name&quot; is not given the
currently selected item is used. Line style constants are:
LINE_DASH, LINE_DASHDOT, LINE_DASHDOTDOT, LINE_DOT, LINE_SOLID
</source>
      <translation>getLineStyle([&quot;name&quot;]) -> integer (see constants)

Vrátí styl čáry objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Styly jsou: LINE_DASH, LINE_DASHDOT, LINE_DASHDOTDOT, LINE_DOT, LINE_SOLID</translation>
    </message>
    <message>
      <source>getFillShade([&quot;name&quot;]) -> integer

Returns the shading value of the fill color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getFillShade([&quot;name&quot;]) -> integer

Vrátí stín výplně objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getImageScale([&quot;name&quot;]) -> (x,y)

Returns a (x, y) tuple containing the scaling values of the image frame
&quot;name&quot;.  If &quot;name&quot; is not given the currently selected item is used.
</source>
      <translation>getImageScale([&quot;name&quot;]) -> (x,y)

Vrátí tuple s velikostmi obrázku rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getImageName([&quot;name&quot;]) -> string

Returns the filename for the image in the image frame. If &quot;name&quot; is not
given the currently selected item is used.
</source>
      <translation>getImageName([&quot;name&quot;]) -> string

Vrátí jméno souboru (obrázku) daného rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getSize([&quot;name&quot;]) -> (width,height)

Returns a (width, height) tuple with the size of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used. The size is
expressed in the current measurement unit of the document - see UNIT_&lt;type>
for reference.
</source>
      <translation>getSize([&quot;name&quot;]) -> (width,height)

Vrátí velikost (tuple) s velikostí rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Velikost je vyjádřena v aktuálních měrných jednotkách (viz. UNIT_typ).</translation>
    </message>
    <message>
      <source>getRotation([&quot;name&quot;]) -> integer

Returns the rotation of the object &quot;name&quot;. The value is expressed in degrees,
and clockwise is positive. If &quot;name&quot; is not given the currently selected item
is used.
</source>
      <translation>getRotation([&quot;name&quot;]) -> integer

Vrátí rotaci objektu &quot;name&quot;. Hodnota je vyjádřena ve stupních. Otočení ve směru
hodinových ručiček je kladné.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getAllObjects() -> list

Returns a list containing the names of all objects on the current page.
</source>
      <translation>getAllObjects() -> list

Vrátí seznam, který obsahuje jména všech objektů na aktuální stránce.</translation>
    </message>
    <message>
      <source>moveObjectAbs(x, y [, &quot;name&quot;])

Moves the object &quot;name&quot; to a new location. The coordinates are expressed in
the current measurement unit of the document (see UNIT constants).  If &quot;name&quot;
is not given the currently selected item is used.  If the object &quot;name&quot;
belongs to a group, the whole group is moved.
</source>
      <translation>moveObjectAbs(x, y [, &quot;name&quot;])

Přesune objekt &quot;name&quot; na nové místo. Paramety x a y jsou vyjádřeny v aktuálních
měrných jednotkách dokumentu (viz. konstanty UNIT).
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Jestliže onjekt &quot;name&quot; patří do skupiny onjektů, je posunuta celá skupina.</translation>
    </message>
    <message>
      <source>rotateObject(rot [, &quot;name&quot;])

Rotates the object &quot;name&quot; by &quot;rot&quot; degrees relatively. The object is
rotated by the vertex that is currently selected as the rotation point - by
default, the top left vertext at zero rotation. Positive values mean counter
clockwise rotation when the default rotation point is used. If &quot;name&quot; is not
given the currently selected item is used.
</source>
      <translation>rotateObject(rot [, &quot;name&quot;])

Otočí relativně objekt &quot;name&quot; o &quot;rot&quot; stupňů. Střed otáčení je aktuální bod otáčení,
implicitně horní levý bod. Kladné hodnoty otáčí po směru hodinových ručiček.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>sizeObject(width, height [, &quot;name&quot;])

Resizes the object &quot;name&quot; to the given width and height. If &quot;name&quot;
is not given the currently selected item is used.
</source>
      <translation>sizeObject(width, height [, &quot;name&quot;])

Změní velikost objektu &quot;name&quot; na danou šířku &quot;width&quot; a výšku &quot;height&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getSelectedObject([nr]) -> string

Returns the name of the selected object. &quot;nr&quot; if given indicates the number
of the selected object, e.g. 0 means the first selected object, 1 means the
second selected Object and so on.
</source>
      <translation>getSelectedObject([nr]) -> string

Vrátí jméno vybraného objektu. Jestliže je zadáno &quot;nr&quot;, pak indikuje,
jaký objekt z výběru vrátí. 0 znamená první objekt atd.</translation>
    </message>
    <message>
      <source>selectionCount() -> integer

Returns the number of selected objects.
</source>
      <translation>selectionCount() -> integer

Vrátí počet objektů ve výběru.</translation>
    </message>
    <message>
      <source>selectObject(&quot;name&quot;)

Selects the object with the given &quot;name&quot;.
</source>
      <translation>selectObject(&quot;name&quot;)

Zařadí objekt &quot;name&quot; do výběru.</translation>
    </message>
    <message>
      <source>deselectAll()

Deselects all objects in the whole document.
</source>
      <translation>deselectAll()

Zruší výběr všech objektů v celém dokumentu.</translation>
    </message>
    <message>
      <source>groupObjects(list)

Groups the objects named in &quot;list&quot; together. &quot;list&quot; must contain the names
of the objects to be grouped. If &quot;list&quot; is not given the currently selected
items are used.
</source>
      <translation>groupObjects(list)

Seskupí objekty vyjmenované v seznamu &quot;list&quot;. Jestliže není seznam zadán,
použijí se vybrané objekty.</translation>
    </message>
    <message>
      <source>unGroupObjects(&quot;name&quot;)

Destructs the group the object &quot;name&quot; belongs to.If &quot;name&quot; is not given the currently selected item is used.</source>
      <translation>unGroupObjects(&quot;name&quot;)

Zruší seskupení objektů, do kterého patří objekt &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>scaleGroup(factor [,&quot;name&quot;])

Scales the group the object &quot;name&quot; belongs to. Values greater than 1 enlarge
the group, values smaller than 1 make the group smaller e.g a value of 0.5
scales the group to 50 % of its original size, a value of 1.5 scales the group
to 150 % of its original size.  The value for &quot;factor&quot; must be greater than
0. If &quot;name&quot; is not given the currently selected item is used.

May raise ValueError if an invalid scale factor is passed.
</source>
      <translation>scaleGroup(factor [,&quot;name&quot;])

Změní velikost seskupených objektů, kam objekt &quot;name&quot; patří. Hodnoty &quot;factor&quot;
větší než 1 zvětšují a naopak. Např. 0.5 znamená 50%, 1.5 150% atd. &quot;factor&quot;
musí být větší než 0.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError při chybném nastavení &quot;factor&quot;.</translation>
    </message>
    <message>
      <source>loadImage(&quot;filename&quot; [, &quot;name&quot;])

Loads the picture &quot;picture&quot; into the image frame &quot;name&quot;. If &quot;name&quot; is
not given the currently selected item is used.

May raise WrongFrameTypeError if the target frame is not an image frame
</source>
      <translation>loadImage(&quot;filename&quot; [, &quot;name&quot;])

Nahraje obrázek &quot;picture&quot; do obrázkového rámce &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku WrongFrameTypeError, není-li objekt obrázkovým rámem</translation>
    </message>
    <message>
      <source>scaleImage(x, y [, &quot;name&quot;])

Sets the scaling factors of the picture in the image frame &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used. A number of 1
means 100 %.

May raise WrongFrameTypeError if the target frame is not an image frame
</source>
      <translation>scaleImage(x, y [, &quot;name&quot;])

Nastaví velikost obrázku v obrázkovém rámu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Číslo 1 znamená 100%.

Může vyvolat výjimku WrongFrameTypeError jestliže rámec není obrázkový</translation>
    </message>
    <message>
      <source>lockObject([&quot;name&quot;]) -> bool

Locks the object &quot;name&quot; if it's unlocked or unlock it if it's locked.
If &quot;name&quot; is not given the currently selected item is used. Returns true
if locked.
</source>
      <translation>lockObject([&quot;name&quot;]) -> bool

Jestliže je objekt &quot;name&quot; zamčený, tak jej odemkne a naopak.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Vrátí true jestliže je objekt zamčený.</translation>
    </message>
    <message>
      <source>isLocked([&quot;name&quot;]) -> bool

Returns true if is the object &quot;name&quot; locked.  If &quot;name&quot; is not given the
currently selected item is used.
</source>
      <translation>isLocked([&quot;name&quot;]) -> bool

Vrátí true kdyý je objekt &quot;name&quot; zamčený.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getFontNames() -> list

Returns a list with the names of all available fonts.
</source>
      <translation>getFontNames() -> list

Vrátí seznam se jmény dostupných písem.</translation>
    </message>
    <message>
      <source>getXFontNames() -> list of tuples

Returns a larger font info. It's a list of the tuples with:
[ (Scribus name, Family, Real name, subset (1|0), embed PS (1|0), font file), (...), ... ]
</source>
      <translation>getXFontNames() -> list of tuples

Vrátí více informací o dostupných písmech. Seznam obsahuje tupple:
[(Scribus name, Family, Real name, subset (1|0), embed PS (1|0), font file), (...), ... ]</translation>
    </message>
    <message>
      <source>rendeFont(&quot;name&quot;, &quot;filename&quot;, &quot;sample&quot;, size) -> bool

Creates an image preview of font &quot;name&quot; with given text &quot;sample&quot; and size.
Image is saved into &quot;filename&quot;. Returns true when success.

May raise NotFoundError if the specified font can't be found.
May raise ValueError if an empty sample or filename is passed.
</source>
      <translation>rendeFont(&quot;name&quot;, &quot;filename&quot;, &quot;sample&quot;, size) -> bool

Vytvoří obrázkovou bitmapu s náhledem písma &quot;name&quot; s textem &quot;sample&quot;
velikosti &quot;size&quot;. Obrázek je pak uložen jako &quot;filename&quot;. Vrátí true v případě
úspěchu.

Může vyvolat výjimky NotFoundError (nenajde písmo) a ValueError (prázdné
filename nebo sample).</translation>
    </message>
    <message>
      <source>getLayers() -> list

Returns a list with the names of all defined layers.
</source>
      <translation>getLayers() -> list

Vrátí seznam se jmény všech vrstev.</translation>
    </message>
    <message>
      <source>setActiveLayer(&quot;name&quot;)

Sets the active layer to the layer named &quot;name&quot;.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>setActiveLayer(&quot;name&quot;)

Přepne dokument na specifikovanou vrstvu &quot;name&quot;.

Může vyvolat výjimky NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>getActiveLayer() -> string

Returns the name of the current active layer.
</source>
      <translation>getActiveLayer() -> string

Vrátí jméno aktuální vrstvy.</translation>
    </message>
    <message>
      <source>sentToLayer(&quot;layer&quot; [, &quot;name&quot;])

Sends the object &quot;name&quot; to the layer &quot;layer&quot;. The layer must exist.
If &quot;name&quot; is not given the currently selected item is used.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>sentToLayer(&quot;layer&quot; [, &quot;name&quot;])

Přesune objekt &quot;name&quot; do vrstvy &quot;layer&quot;. Vrstva musí existovat.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>setLayerVisible(&quot;layer&quot;, visible)

Sets the layer &quot;layer&quot; to be visible or not. If is the visible set to false
the layer is invisible.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>setLayerVisible(&quot;layer&quot;, visible)

Nastaví jestli má být vrstva &quot;layer&quot; viditelná nebo nemá. Je-li &quot;visible&quot;
false, bude vrstva neviditelná.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>setLayerPrintable(&quot;layer&quot;, printable)

Sets the layer &quot;layer&quot; to be printable or not. If is the printable set to
false the layer won't be printed.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>setLayerPrintable(&quot;layer&quot;, printable)

Nastaví jestli má být vrstva &quot;layer&quot; tisknutelná nebo nemá. Je-li &quot;printable&quot;
false, nebude vrstva tisknuta.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>isLayerPrintable(&quot;layer&quot;) -> bool

Returns wether the Layer &quot;layer&quot; is visible or not, a value of True means
that the layer &quot;layer&quot; is visible, a value of False means that the layer
&quot;layer&quot; is invisible.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>isLayerPrintable(&quot;layer&quot;) -> bool

Vrátí příznak, zda jde vrstva &quot;layer&quot; viditelná nebo není. true znamená
viditelná.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>isLayerPrintable(&quot;layer&quot;) -> bool

Returns wether the layer &quot;layer&quot; is printable or not, a value of True means
that the layer &quot;layer&quot; can be printed, a value of False means that printing
the layer &quot;layer&quot; is disabled.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>isLayerPrintable(&quot;layer&quot;) -> bool

Vrátí příznak, zda jde vrstva &quot;layer&quot; tisknutelná nebo není. true znamená
tisknutelná.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>deleteLayer(&quot;layer&quot;)

Deletes the layer with the name &quot;layer&quot;. Nothing happens if the layer doesn't
exists or if it's the only layer in the document.

May raise NotFoundError if the layer can't be found.
May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>deleteLayer(&quot;layer&quot;)

Smaže vrstvu &quot;layer&quot;. Neudělá nic, jestliže je to poslední vrstva dokumentu
nebo vrstva neexistuje.

Může vyvolat výjimku NotFoundError (vrstva nenalezena) a
ValueError (nelze přepnout vrstvu).</translation>
    </message>
    <message>
      <source>createLayer(layer)

Creates a new layer with the name &quot;name&quot;.

May raise ValueError if the layer name isn't acceptable.
</source>
      <translation>createLayer(layer)

Vytvoří novou vrstvu se jménem &quot;layer&quot;.

Může vyvolat výjimku ValueError v případě chyby.</translation>
    </message>
    <message>
      <source>getGuiLanguage() -> string

Returns a string with the -lang value.
</source>
      <translation>getGuiLanguage() -> string

Vrátí řetězec s kódem jazyka, ve kterém Scribus běží (viz. přepínač --lang xx).</translation>
    </message>
    <message>
      <source>createEllipse(x, y, width, height, [&quot;name&quot;]) -> string

Creates a new ellipse on the current page and returns its name.
The coordinates are given in the current measurement units of the document
(see UNIT constants). &quot;name&quot; should be a unique identifier for the object
because you need this name for further referencing of that object. If &quot;name&quot;
is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
</source>
      <translation>createEllipse(x, y, width, height, [&quot;name&quot;]) -> string

Vytvoří novou elipsu na aktuální stránce dokumentu a vrátí její jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.</translation>
    </message>
    <message>
      <source>createImage(x, y, width, height, [&quot;name&quot;]) -> string

Creates a new picture frame on the current page and returns its name. The
coordinates are given in the current measurement units of the document.
&quot;name&quot; should be a unique identifier for the object because you need this
name for further access to that object. If &quot;name&quot; is not given Scribus will
create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
</source>
      <translation>createImage(x, y, width, height, [&quot;name&quot;]) -> string

Vytvoří novoý obrázkový rám na aktuální stránce dokumentu a vrátí jeho jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.</translation>
    </message>
    <message>
      <source>createText(x, y, width, height, [&quot;name&quot;]) -> string

Creates a new text frame on the actual page and returns its name.
The coordinates are given in the actual measurement unit of the document (see
UNIT constants). &quot;name&quot; should be a unique identifier for the object because
you need this name for further referencing of that object. If &quot;name&quot; is not
given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
</source>
      <translation>createText(x, y, width, height, [&quot;name&quot;]) -> string

Vytvoří nový textový rámec na aktuální stránce dokumentu a vrátí jeho jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.</translation>
    </message>
    <message>
      <source>createLine(x1, y1, x2, y2, [&quot;name&quot;]) -> string

Creates a new line from the point(x1, y1) to the point(x2, y2) and returns
its name. The coordinates are given in the current measurement unit of the
document (see UNIT constants). &quot;name&quot; should be a unique identifier for the
object because you need this name for further access to that object. If
&quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
</source>
      <translation>createLine(x1, y1, x2, y2, [&quot;name&quot;]) -> string

Vytvoří novou čáru na aktuální stránce dokumentu a vrátí její jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.</translation>
    </message>
    <message>
      <source>createPolyLine(list, [&quot;name&quot;]) -> string

Creates a new polyline and returns its name. The points for the polyline are
stored in the list &quot;list&quot; in the following order: [x1, y1, x2, y2...xn. yn].
The coordinates are given in the current measurement units of the document (see
UNIT constants). &quot;name&quot; should be a unique identifier for the object because
you need this name for further access to that object. If &quot;name&quot; is not given
Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don't group into points without leftovers.
</source>
      <translation>createPolyLine(list, [&quot;name&quot;]) -> string

Vytvoří novou lomenou čáru na aktuální stránce dokumentu a vrátí její jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.
Seznam bodů má tvar: [x1, y1, x2, y2, ..., xn, yn].

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.
Může vyvolat výjimku ValueError v případě špatných koordinátů.</translation>
    </message>
    <message>
      <source>createPolygon(list, [&quot;name&quot;]) -> string

Creates a new polygon and returns its name. The points for the polygon are
stored in the list &quot;list&quot; in the following order: [x1, y1, x2, y2...xn. yn].
At least three points are required. There is no need to repeat the first point
to close the polygon. The polygon is automatically closed by connecting the
first and the last point.  The coordinates are given in the current measurement
units of the document (see UNIT constants).  &quot;name&quot; should be a unique
identifier for the object because you need this name for further access to that
object. If &quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don't group into points without leftovers.
</source>
      <translation>createPolygon(list, [&quot;name&quot;]) -> string

Vytvoří nový mnohoúhelník na aktuální stránce dokumentu a vrátí jeho jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.
Seznam bodů objeku má tvar: [x1, y1, x2, y2, ..., xn, yn] a jsou nutné alespoň
tři body. Mnohoúhelník je automaticky uzavřen, takže není třeba zadávat poslední
bod jako první.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.
Může vyvolat výjimku ValueError v případě špatných koordinátů.</translation>
    </message>
    <message>
      <source>createBezierLine(list, [&quot;name&quot;]) -> string

Creates a new bezier curve and returns its name. The points for the bezier
curve are stored in the list &quot;list&quot; in the following order:
[x1, y1, kx1, ky1, x2, y2, kx2, ky2...xn. yn, kxn. kyn]
In the points list, x and y mean the x and y coordinates of the point and kx
and ky meaning the control point for the curve.  The coordinates are given in
the current measurement units of the document (see UNIT constants). &quot;name&quot;
should be a unique identifier for the object because you need this name for
further access to that object. If &quot;name&quot; is not given Scribus will create one
for you.

May raise NameExistsError if you explicitly pass a name that's already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don't group into points without leftovers.
</source>
      <translation>createBezierLine(list, [&quot;name&quot;]) -> string

Vytvoří novou Bezierovou křivku na aktuální stránce dokumentu a vrátí jeho jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.
Seznam bodů objeku má tvar: [x1, y1, kx1, ky1, x2, y2, kx2, ky2, ..., xn, yn, kxn, kyn].
x a y jsou koordináty bodů, kx a ky jsou koordináty řídícího bodu křivky.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.
Může vyvolat výjimku ValueError v případě špatných koordinátů.</translation>
    </message>
    <message>
      <source>createPathText(x, y, &quot;textbox&quot;, &quot;beziercurve&quot;, [&quot;name&quot;]) -> string

Creates a new pathText by merging the two objects &quot;textbox&quot; and
&quot;beziercurve&quot; and returns its name. The coordinates are given in the current
measurement unit of the document (see UNIT constants). &quot;name&quot; should be a
unique identifier for the object because you need this name for further access
to that object. If &quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that's already used.
May raise NotFoundError if one or both of the named base object don't exist.
</source>
      <translation>createPathText(x, y, &quot;textbox&quot;, &quot;beziercurve&quot;, [&quot;name&quot;]) -> string

Vytvoří nový text na křivce na aktuální stránce dokumentu a vrátí jeho jméno.
Koordináty jsou zadávány v současných měrných jednotkách (viz. konstanty UNIT).
Jméno &quot;name&quot; musí být unikátní řetězec.
Jestliže není &quot;name&quot; uvedeno, Scribus jméno vytvoří sám.
Text na křivce vyznikne ze dvou objektů - textového rámce &quot;textbox&quot; a Bezierovské
křivky &quot;beziercurve&quot;.

Může vyvolat výjimku NameExistsError když zadáte jméno, které již existuje.
Může vyvolat výjimku NotFoundError v případě neexistujících objektů.</translation>
    </message>
    <message>
      <source>deleteObject([&quot;name&quot;])

Deletes the item with the name &quot;name&quot;. If &quot;name&quot; is not given the currently
selected item is deleted.
</source>
      <translation>deleteObject([&quot;name&quot;])

Smaže objekt &quot;name&quot;. Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>textFlowsAroundFrame(&quot;name&quot; [, state])

Enables/disables &quot;Text Flows Around Frame&quot; feature for object &quot;name&quot;.
Called with parameters string name and optional boolean &quot;state&quot;. If &quot;state&quot;
is not passed, text flow is toggled.
</source>
      <translation>textFlowsAroundFrame(&quot;name&quot; [, state])

Povolí/zakáže vlastnost &quot;Text obtéká okolo rámu&quot; objektu &quot;name&quot;.
Jestliže je &quot;state&quot; true, vlastnost povolí a naopak. V případě, že &quot;state&quot; není
zadáno, stav se obrátí.</translation>
    </message>
    <message>
      <source>objectExists([&quot;name&quot;]) -> bool

Test if an object with specified name really exists in the document.
The optional parameter is the object name. When no object name is given,
returns True if there is something selected.
</source>
      <translation>objectExists([&quot;name&quot;]) -> bool

Vrátí příznak, zda objekt &quot;name&quot; v dokuemntu existuje. Když není &quot;name&quot;
zadáno, vrátí true, jestliže je nějaký objekt vybrán.</translation>
    </message>
    <message>
      <source>setStyle(&quot;style&quot; [, &quot;name&quot;])

Apply the named &quot;style&quot; to the object named &quot;name&quot;. If is no object name
given, it's applied on the selected object.
</source>
      <translation>setStyle(&quot;style&quot; [, &quot;name&quot;])

Aplikuje styl &quot;style&quot; na objekt &quot;name&quot;. Jestliže není &quot;name&quot; uvedeno,
použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getAllStyles() -> list

Return a list of the names of all paragraph styles in the current document.
</source>
      <translation>getAllStyles() -> list

Vrátí seznam všech jmen stylů odstavce v dokumentu.</translation>
    </message>
    <message>
      <source>currentPage() -> integer

Returns the number of the current working page. Page numbers are counted from 1
upwards, no matter what the displayed first page number of your document is.
</source>
      <translation>currentPage() -> integer

Vrátí číslo aktuální stránky dokumentu. Stránky jsou číslovány od 1, přičemž nezáleží
na nastaveném čísle první stránky.</translation>
    </message>
    <message>
      <source>redrawAll()

Redraws all pages.
</source>
      <translation>Překreslí/obnoví všechny stránky.</translation>
    </message>
    <message>
      <source>savePageAsEPS(&quot;name&quot;)

Saves the current page as an EPS to the file &quot;name&quot;.

May raise ScribusError if the save failed.
</source>
      <translation>Uloží aktuální stránku jako EPS do souboru &quot;name&quot;.

Může vyvolat výjimu ScribusErro, dojde-li k chybě.</translation>
    </message>
    <message>
      <source>deletePage(nr)

Deletes the given page. Does nothing if the document contains only one page.
Page numbers are counted from 1 upwards, no matter what the displayed first
page number is.

May raise IndexError if the page number is out of range
</source>
      <translation>deletePage(nr)

Smaže zadanou stránku. Nedělá nic, jestliže dokument obsahuje jedinou stránku.
Stránky jsou číslovány od 1, přičemž nezáleží na nastaveném čísle první stránky.

Může vyvolat výjimku IndexError, jestliže není &quot;nr&quot; číslo existující stránky</translation>
    </message>
    <message>
      <source>gotoPage(nr)

Moves to the page &quot;nr&quot; (that is, makes the current page &quot;nr&quot;). Note that
gotoPage doesn't (curently) change the page the user's view is displaying, it
just sets the page that script commands will operates on.

May raise IndexError if the page number is out of range.
</source>
      <translation>gotoPage(nr)

Nastaví stránku &quot;nr&quot; jako aktuální. Pozor - procedura neposune zobrazení stránky
uživateli, pouze přepne kontext Scripteru (t.j. na jaké stránce budou vykonávány
příkazy).

Může vyvolat výjimku IndexError, jestliže není &quot;nr&quot; číslo existující stránky.</translation>
    </message>
    <message>
      <source>pageCount() -> integer

Returns the number of pages in the document.
</source>
      <translation>Vrátí počet stránek dokumentu.</translation>
    </message>
    <message>
      <source>getHGuides() -> list

Returns a list containing positions of the horizontal guides. Values are in the
document's current units - see UNIT_&lt;type> constants.
</source>
      <translation>getHGuides() -> list

Vrátí seznam s pozicemi horizontálních vodítek. Hodnoty jsou v aktuálních
měrných jednotkách. Viz. konstanty UNIT.</translation>
    </message>
    <message>
      <source>setHGuides(list)

Sets horizontal guides. Input parameter must be a list of guide positions
measured in the current document units - see UNIT_&lt;type> constants.

Example: setHGuides(getHGuides() + [200.0, 210.0] # add new guides without any lost
         setHGuides([90,250]) # replace current guides entirely
</source>
      <translation>setHGuides(list)

Nastaví horizontální vodítka. Vstupní parametr je seznam jejich pozicí
v aktuálních měrných jednotkách (viz. konstanty UNIT).
Např.:
     setHGuides(getHGuides()) + [200.0, 210.0] # prida voditka
     setHGuides([90, 250]) # smaze stara a nastavi nova voditka</translation>
    </message>
    <message>
      <source>getVGuides()

See getHGuides.
</source>
      <translation>Viz. getHGuides().</translation>
    </message>
    <message>
      <source>setVGuides()

See setHGuides.
</source>
      <translation>Viz. setHGuides().</translation>
    </message>
    <message>
      <source>getPageSize() -> tuple

Returns a tuple with page dimensions measured in the document's current units.
See UNIT_&lt;type> constants and getPageMargins()
</source>
      <translation>getPageSize() -> tuple

Vrátí tuple s rozměry stránky v aktuálních měrných jednotkách. Viz. konstanty UNIT
a getPageMargins()</translation>
    </message>
    <message>
      <source>getPageItems() -> list

Returns a list of tuples with items on the current page. The tuple is:
(name, objectType, order) E.g. [('Text1', 4, 0), ('Image1', 2, 1)]
means that object named 'Text1' is a text frame (type 4) and is the first at
the page...
</source>
      <translation>getPageItems() -> list

Vrátí seznam tuple objektů na aktuální stránce: (jmeno, typ, poradi).
Např.: [('Text1', 4, 0), ('Image1', 2, 1)], což znamená, že objekt &quot;Text1&quot;
je textový rámec (4) a je první v pořadí na stránce...</translation>
    </message>
    <message>
      <source>getPageMargins()

Returns the page margins as a (left, right, top, bottom) tuple in the current
units. See UNIT_&lt;type> constants and getPageSize().
</source>
      <translation>getPageMargins()

Vrátí nastavení okrajů stránky (levý, pravý, horní, dolní) v aktuálních měrných
jednotkách. Viz. koonstanty UNIT a getPageSize().</translation>
    </message>
    <message>
      <source>setFillColor(&quot;color&quot;, [&quot;name&quot;])

Sets the fill color of the object &quot;name&quot; to the color &quot;color&quot;. &quot;color&quot;
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
      <translation>setFillColor(&quot;color&quot;, [&quot;name&quot;])

Nastavý výplňovou barvu &quot;color&quot; objektu &quot;name&quot;. &quot;color&quot; je jméno
jedné z definovaných barev. Jestliže není &quot;name&quot; uvedeno, použije 
vybraný objekt.</translation>
    </message>
    <message>
      <source>setLineColor(&quot;color&quot;, [&quot;name&quot;])

Sets the line color of the object &quot;name&quot; to the color &quot;color&quot;. If &quot;name&quot;
is not given the currently selected item is used.
</source>
      <translation>setLineColor(&quot;color&quot;, [&quot;name&quot;])

Nastaví barvu &quot;color&quot; čar objetu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>setLineWidth(width, [&quot;name&quot;])

Sets line width of the object &quot;name&quot; to &quot;width&quot;. &quot;width&quot; must be in the
range from 0.0 to 12.0 inclusive, and is measured in points. If &quot;name&quot; is not
given the currently selected item is used.

May raise ValueError if the line width is out of bounds.
</source>
      <translation>setLineWidth(width, [&quot;name&quot;])

Nastaví šířku čáry objektu &quot;name&quot; na hodnotu &quot;width&quot;. &quot;width&quot; musí
být v intervalu &lt;0.0; 12.0> a je v bodech.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolatvýjimku ValueError, když není hodnota v intervalu.</translation>
    </message>
    <message>
      <source>setLineShade(shade, [&quot;name&quot;])

Sets the shading of the line color of the object &quot;name&quot; to &quot;shade&quot;.
&quot;shade&quot; must be an integer value in the range from 0 (lightest) to 100
(full color intensity). If &quot;name&quot; is not given the currently selected item
is used.

May raise ValueError if the line shade is out of bounds.
</source>
      <translation>setLineShade(shade, [&quot;name&quot;])

Nastaví stín čar objektu &quot;name&quot; na hodnotu &quot;shade&quot;. &quot;shade&quot; musí
být celé číslo z intervalu &lt;0; 100>.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, když je hodnota mimo interval.</translation>
    </message>
    <message>
      <source>setLineJoin(join, [&quot;name&quot;])

Sets the line join style of the object &quot;name&quot; to the style &quot;join&quot;.
If &quot;name&quot; is not given the currently selected item is used. There are
predefined constants for join - JOIN_&lt;type>.
</source>
      <translation>setLineJoin(join, [&quot;name&quot;])

Nastaví typ spojení čar objektu &quot;name&quot; na styl &quot;join&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Viz. předdefinované konstanty JOIN_*.</translation>
    </message>
    <message>
      <source>setLineEnd(endtype, [&quot;name&quot;])

Sets the line cap style of the object &quot;name&quot; to the style &quot;cap&quot;.
If &quot;name&quot; is not given the currently selected item is used. There are
predefined constants for &quot;cap&quot; - CAP_&lt;type>.
</source>
      <translation>setLineEnd(endtype, [&quot;name&quot;])

Nastaví styl konce čar objektu &quot;name&quot; na styl &quot;cap&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Viz. předdefinované konstanty CAP_*.</translation>
    </message>
    <message>
      <source>setLineStyle(style, [&quot;name&quot;])

Sets the line style of the object &quot;name&quot; to the style &quot;style&quot;. If &quot;name&quot;
is not given the currently selected item is used. There are predefined
constants for &quot;style&quot; - LINE_&lt;style>.
</source>
      <translation>setLineStyle(style, [&quot;name&quot;])

Nastaví styl čáry objektu &quot;name&quot; na styl &quot;style&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Viz. předdefinované konstanty LINE_*.</translation>
    </message>
    <message>
      <source>setFillShade(shade, [&quot;name&quot;])

Sets the shading of the fill color of the object &quot;name&quot; to &quot;shade&quot;.
&quot;shade&quot; must be an integer value in the range from 0 (lightest) to 100
(full Color intensity). If &quot;name&quot; is not given the currently selected
Item is used.

May raise ValueError if the fill shade is out of bounds.
</source>
      <translation>setFillShade(shade, [&quot;name&quot;])

Nastaví stín výplně objektu &quot;name&quot; na hodnotu &quot;shade&quot;.
&quot;shade&quot; musí být celé číslo z intervalu &lt;0; 100>.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, jestliže je hodnota mimo interval.</translation>
    </message>
    <message>
      <source>setCornerRadius(radius, [&quot;name&quot;])

Sets the corner radius of the object &quot;name&quot;. The radius is expressed
in points. If &quot;name&quot; is not given the currently selected item is used.

May raise ValueError if the corner radius is negative.
</source>
      <translation>setCornerRadius(radius, [&quot;name&quot;])

Nastaví poloměr zaoblení rohů objektu &quot;name&quot;. Poloměr je vyjádřen v bodech.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku ValueError, když je poloměr negativní.</translation>
    </message>
    <message>
      <source>setMultiLine(&quot;namedStyle&quot;, [&quot;name&quot;])

Sets the line style of the object &quot;name&quot; to the named style &quot;namedStyle&quot;.
If &quot;name&quot; is not given the currently selected item is used.

May raise NotFoundError if the line style doesn't exist.
</source>
      <translation>setMultiLine(&quot;namedStyle&quot;, [&quot;name&quot;])

Nastaví styl čar objektu &quot;name&quot; na definovaný styl &quot;namedStyle&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.

Může vyvolat výjimku NotFoundError, jestliže styl neexistuje.</translation>
    </message>
    <message>
      <source>progressReset()

Cleans up the Scribus progress bar previous settings. It is called before the
new progress bar use. See progressSet.
</source>
      <translation>progressReset()

Zruší předchozí nastavení progress baru. Je to vhodné použít před novým použitím P.B.</translation>
    </message>
    <message>
      <source>progressTotal(max)

Sets the progress bar's maximum steps value to the specified number.
See progressSet.
</source>
      <translation>progressTotal(max)

Nastaví maximální možný počet kroků (zaplnění) progress baru.</translation>
    </message>
    <message>
      <source>progressSet(nr)

Set the progress bar position to &quot;nr&quot;, a value relative to the previously set
progressTotal. The progress bar uses the concept of steps; you give it the
total number of steps and the number of steps completed so far and it will
display the percentage of steps that have been completed. You can specify the
total number of steps with progressTotal(). The current number of steps is set
with progressSet(). The progress bar can be rewound to the beginning with
progressReset(). [based on info taken from Trolltech's Qt docs]
</source>
      <translation>progressSet(nr)

Nastaví pozici progress baru na &quot;nr&quot;. Progress bar využívá koncept &quot;kroků&quot;.
Musíte zadat maximální počet kroků (progressTotal()) a nastavovat je (progressSet()).
Po použití P.B. je vhodné jej vynulovat, t.j. použít progressReset(). Viz. dokumentace
Qt</translation>
    </message>
    <message>
      <source>setCursor()

[UNSUPPORTED!] This might break things, so steer clear for now.
</source>
      <translation>[UNSUPPORTED!] This might break things, so steer clear for now.</translation>
    </message>
    <message>
      <source>docChanged(bool)

Enable/disable save icon in the Scribus icon bar and the Save menu item. It's
useful to call this procedure when you're changing the document, because Scribus
won't automatically notice when you change the document using a script.
</source>
      <translation>docChanged(bool)

Povolí/zakáže ikonu &quot;uložit&quot; a položku menu &quot;Uložit&quot; v hlavním okně Scribusu.
Proceduru volejte, jestliže jste něco ve svém skriptu změnili, protože Scribus
tuto akci nezajistí automaticky.</translation>
    </message>
    <message>
      <source>defineColor(&quot;name&quot;, c, m, y, k)

Defines a new color &quot;name&quot;. The color Value is defined via four components:
c = Cyan, m = Magenta, y = Yellow and k = Black. Color components should be in
the range from 0 to 255.

May raise ValueError if an invalid color name is specified.
</source>
      <translation>defineColor(&quot;name&quot;, c, m, y, k)

Vytvoří novou barvu &quot;name&quot;. Barva je definována čtyřmi složkami modelu CMYK.
Každá složka musí být z intervalu &lt;0; 255>.

Může vyvolat výjimku ValueError, v případě chybného jména barvy.</translation>
    </message>
    <message>
      <source>getCornerRadius([&quot;name&quot;]) -> integer

Returns the corner radius of the object &quot;name&quot;. The radius is
expressed in points. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>getCornerRadius([&quot;name&quot;]) -> integer

Vrátí poloměr zaoblení rohů objektu &quot;name&quot;. Poloměr je vyjádřen
v bodech. Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
    <message>
      <source>getPosition([&quot;name&quot;]) -> (x,y)

Returns a (x, y) tuple with the position of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
The position is expressed in the actual measurement unit of the document
- see UNIT_&lt;type> for reference.
</source>
      <translation>getPosition([&quot;name&quot;]) -> (x,y)

Vrátí (x, y) tuple s pozicí objektu &quot;name&quot;.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.
Pozice je vyjádřena v aktuálních měrných jednotkách dokumentu. Viz. konstanty UNIT*.</translation>
    </message>
    <message>
      <source>rotateObjectAbs(rot [, &quot;name&quot;])

Sets the rotation of the object &quot;name&quot; to &quot;rot&quot;. Positive values
mean counter clockwise rotation. If &quot;name&quot; is not given the currently
selected item is used.
</source>
      <translation>rotateObjectAbs(rot [, &quot;name&quot;])

Nastaví otočení objektu &quot;name&quot; na &quot;rot&quot;. Kladné hodnoty znamenají
otočení po směru hodinových ručiček.
Jestliže není &quot;name&quot; uvedeno, použije vybraný objekt.</translation>
    </message>
  </context>
  <context>
    <name>About</name>
    <message>
      <source>%1. %2 %3 </source>
      <translation>%1. %2 %3</translation>
    </message>
    <message>
      <source>Scribus Version %1
%2 %3</source>
      <translation>Scribus ver. %1(new line)
%2 %3</translation>
    </message>
    <message>
      <source>Build-ID:</source>
      <translation>Build=ID:</translation>
    </message>
    <message>
      <source>Contributions from:</source>
      <translation>Příspěvky od:</translation>
    </message>
    <message>
      <source>Windows port:</source>
      <translation>Windows verze:</translation>
    </message>
    <message>
      <source>German:</source>
      <translation>Německy:</translation>
    </message>
    <message>
      <source>French:</source>
      <translation>Francouzsky:</translation>
    </message>
    <message>
      <source>Italian:</source>
      <translation>Italsky:</translation>
    </message>
    <message>
      <source>Hungarian:</source>
      <translation>Maďarsky:</translation>
    </message>
    <message>
      <source>Ukrainian:</source>
      <translation>Ukrajinsky:</translation>
    </message>
    <message>
      <source>Bulgarian:</source>
      <translation>Bulharsky:</translation>
    </message>
    <message>
      <source>Galician:</source>
      <translation>Galsky:</translation>
    </message>
    <message>
      <source>Turkish:</source>
      <translation>Turecky:</translation>
    </message>
    <message>
      <source>Lithuanian:</source>
      <translation>Litevsky:</translation>
    </message>
    <message>
      <source>Polish:</source>
      <translation>Polsky:</translation>
    </message>
    <message>
      <source>Czech:</source>
      <translation>Česky:</translation>
    </message>
    <message>
      <source>Slovak:</source>
      <translation>Slovensky:</translation>
    </message>
    <message>
      <source>Danish:</source>
      <translation>Dánsky:</translation>
    </message>
    <message>
      <source>Norwegian:</source>
      <translation>Norsky:</translation>
    </message>
    <message>
      <source>Welsh:</source>
      <translation>Velšsky:</translation>
    </message>
    <message>
      <source>Russian:</source>
      <translation>Rusky:</translation>
    </message>
    <message>
      <source>Brazilian:</source>
      <translation>Brazilsky:</translation>
    </message>
    <message>
      <source>Finnish:</source>
      <translation>Finsky:</translation>
    </message>
    <message>
      <source>Basque:</source>
      <translation>Baskitsky:</translation>
    </message>
    <message>
      <source>Slovenian:</source>
      <translation>Slovinsky:</translation>
    </message>
    <message>
      <source>&amp;About</source>
      <translation>O &amp;Scribusu</translation>
    </message>
    <message>
      <source>A&amp;uthors</source>
      <translation>&amp;Autoři</translation>
    </message>
    <message>
      <source>&amp;Translations</source>
      <translation>&amp;Překlady</translation>
    </message>
    <message>
      <source>&amp;Online</source>
      <translation>&amp;Online</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>Development Team:</source>
      <translation>Vývojový tým:</translation>
    </message>
    <message>
      <source>Official Documentation:</source>
      <translation>Oficiální dokumentace:</translation>
    </message>
    <message>
      <source>Other Documentation:</source>
      <translation>Ostatní dokumentace:</translation>
    </message>
    <message>
      <source>English (British):</source>
      <translation>Britská angličtina:</translation>
    </message>
    <message>
      <source>Swedish:</source>
      <translation>Švédsky:</translation>
    </message>
    <message>
      <source>Homepage</source>
      <translation>Webová stránky</translation>
    </message>
    <message>
      <source>Online Reference</source>
      <translation>On-line reference</translation>
    </message>
    <message>
      <source>Bugs and Feature Requests</source>
      <translation>Chyby a požadavky na změnu</translation>
    </message>
    <message>
      <source>Mailing List</source>
      <translation>Mailová skupina</translation>
    </message>
    <message>
      <source>Official Translations and Translators:</source>
      <translation>Oficiální překlady a překladatelé:</translation>
    </message>
    <message>
      <source>Esperanto:</source>
      <translation>Esperanto:</translation>
    </message>
    <message>
      <source>Korean:</source>
      <translation>Korejsky:</translation>
    </message>
    <message>
      <source>Serbian:</source>
      <translation>Srbsky:</translation>
    </message>
    <message>
      <source>Spanish:</source>
      <translation>Španělsky:</translation>
    </message>
    <message>
      <source>Previous Translation Contributors:</source>
      <translation>Předchozí přispěvatelé:</translation>
    </message>
    <message>
      <source>Catalan:</source>
      <translation>Katalánsky:</translation>
    </message>
    <message>
      <source>About Scribus %1</source>
      <translation>O Scribusu %1</translation>
    </message>
    <message>
      <source>This panel shows the version, build date and
 compiled in library support in Scribus
The C-C-T equates to C=littlecms C=CUPS T=TIFF support.
Missing library support is indicated by a *</source>
      <translation>Okno ukazuje verzi programu, datum kompilace
a knihovny v něm použité.
Symboly C-C-T znamenají C-littlecms C-CUPS T-TIFF podporu.
Chybějící knihovny jsou zobrazeny jako *</translation>
    </message>
  </context>
  <context>
    <name>AdvOptions</name>
    <message>
      <source>Advanced Options</source>
      <translation>Pokročilé možnosti</translation>
    </message>
    <message>
      <source>Creates PostScript Level 3</source>
      <translation>Vytvoří PostScript Level 3</translation>
    </message>
    <message>
      <source>Creates PostScript Level 2 only, beware,
this can create huge files</source>
      <translation>Vytviří PostScript Level 2.
Mohou vzniknout velké soubory</translation>
    </message>
    <message>
      <source>Creates PostScript Level 1 only, beware,
this can create huge files</source>
      <translation>Vytviří PostScript Level 1.
Mohou vzniknout velké soubory</translation>
    </message>
    <message>
      <source>Mirror Page(s) &amp;Horizontal</source>
      <translation>Zrcadlit stranu(y) &amp;horizontálně</translation>
    </message>
    <message>
      <source>Mirror Page(s) &amp;Vertical</source>
      <translation>Zrcadlit stranu(y) &amp;vertikálně</translation>
    </message>
    <message>
      <source>Apply &amp;ICC Profiles</source>
      <translation>Aplikovat &amp;ICC profily</translation>
    </message>
    <message>
      <source>PostScript Level &amp;1</source>
      <translation>PostScript Level &amp;1</translation>
    </message>
    <message>
      <source>PostScript Level &amp;2</source>
      <translation>PostScript Level &amp;2</translation>
    </message>
    <message>
      <source>PostScript Level &amp;3</source>
      <translation>PostScript Level &amp;3</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Apply Under Color &amp;Removal</source>
      <translation>Aplikovat tzv. &amp;Under Color Removal</translation>
    </message>
    <message>
      <source>A way of switching off some of the gray shades which are composed
of cyan, yellow and magenta and using black instead.
UCR most affects parts of images which are neutral and/or dark tones
which are close to the gray. Use of this may improve printing some images
and some experimentation and testing is need on a case by case basis.
UCR reduces the possibility of over saturation with CMY inks.</source>
      <translation>UCR - under color removal - odstranění přebytečné barvy, která by 
způsobila rozpíjení (při přílišné saturaci papíru barvou) nebo trhání 
barvy při několika vrstvém (např. barevném) laserovém tisku.
Viz. např. http://www.typo.cz/_pismo/pis-tech-post.html
a jiné.</translation>
    </message>
  </context>
  <context>
    <name>Align</name>
    <message>
      <source>Distribute/Align</source>
      <translation>Umístit/zarovnat</translation>
    </message>
    <message>
      <source>Align</source>
      <translation>Zarovnat</translation>
    </message>
    <message>
      <source>Horizontal</source>
      <translation>Vodorovně</translation>
    </message>
    <message>
      <source>Left Sides</source>
      <translation>Levé strany</translation>
    </message>
    <message>
      <source>Middles</source>
      <translation>Na střed</translation>
    </message>
    <message>
      <source>Right Sides</source>
      <translation>Pravé strany</translation>
    </message>
    <message>
      <source>Vertical</source>
      <translation>Svisle</translation>
    </message>
    <message>
      <source>Top Sides</source>
      <translation>Horní strany</translation>
    </message>
    <message>
      <source>Bottom Sides</source>
      <translation>Spodní strany</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Apply</source>
      <translation>&amp;Aplikovat</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Between:</source>
      <translation>&amp;Mezi:</translation>
    </message>
    <message>
      <source>A&amp;lign</source>
      <translation>&amp;Zarovnat</translation>
    </message>
    <message>
      <source>Di&amp;splacement</source>
      <translation>&amp;Posunutí</translation>
    </message>
    <message>
      <source>Distribute &amp;Evenly</source>
      <translation>&amp;Rozmístit rovnoměrně</translation>
    </message>
    <message>
      <source>Bet&amp;ween:</source>
      <translation>M&amp;ezi:</translation>
    </message>
    <message>
      <source>Do &amp;Not Change</source>
      <translation>&amp;Neměnit</translation>
    </message>
    <message>
      <source>Al&amp;ign</source>
      <translation>&amp;Zarovnat</translation>
    </message>
    <message>
      <source>Dis&amp;placement</source>
      <translation>&amp;Posunutí</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Distribute E&amp;venly</source>
      <translation>&amp;Rozmístit rovnoměrně</translation>
    </message>
    <message>
      <source>&amp;Do Not Change</source>
      <translation>&amp;Neměnit</translation>
    </message>
  </context>
  <context>
    <name>AlignSelect</name>
    <message>
      <source>Align Text Left</source>
      <translation>Zarovnat text doleva</translation>
    </message>
    <message>
      <source>Align Text Right</source>
      <translation>Zarovnat text doprava</translation>
    </message>
    <message>
      <source>Align Text Center</source>
      <translation>Zarovnat text na střed</translation>
    </message>
    <message>
      <source>Align Text Justified</source>
      <translation>Zarovnat text vyrovnaně</translation>
    </message>
    <message>
      <source>Align Text Forced Justified</source>
      <translation>Zarovnat text vynuceně vyrovnaně</translation>
    </message>
  </context>
  <context>
    <name>Annot</name>
    <message>
      <source>Field Properties</source>
      <translation>Vlastnosti pole</translation>
    </message>
    <message>
      <source>Type:</source>
      <translation>Typ:</translation>
    </message>
    <message>
      <source>Button</source>
      <translation>Tlačítko</translation>
    </message>
    <message>
      <source>Text Field</source>
      <translation>Textové pole</translation>
    </message>
    <message>
      <source>Check Box</source>
      <translation>Políčko k zaškrtnuti</translation>
    </message>
    <message>
      <source>Combo Box</source>
      <translation>Výběr</translation>
    </message>
    <message>
      <source>List Box</source>
      <translation>Seznam</translation>
    </message>
    <message>
      <source>Properties</source>
      <translation>Vlastnosti</translation>
    </message>
    <message>
      <source>Name:</source>
      <translation>Název:</translation>
    </message>
    <message>
      <source>Tool-Tip:</source>
      <translation>Tipy pro nástroje:</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Border</source>
      <translation>Ohraničení</translation>
    </message>
    <message>
      <source>Color:</source>
      <translation>Barva:</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Width:</source>
      <translation>Šířka:</translation>
    </message>
    <message>
      <source>Thin</source>
      <translation>Tenký</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Wide</source>
      <translation>Široké</translation>
    </message>
    <message>
      <source>Style:</source>
      <translation>Styl:</translation>
    </message>
    <message>
      <source>Solid</source>
      <translation>Bez přerušení</translation>
    </message>
    <message>
      <source>Dashed</source>
      <translation>Přerušovaný</translation>
    </message>
    <message>
      <source>Underline</source>
      <translation>Podtržené</translation>
    </message>
    <message>
      <source>Beveled</source>
      <translation>Zkosený</translation>
    </message>
    <message>
      <source>Inset</source>
      <translation>Příloha</translation>
    </message>
    <message>
      <source>Other</source>
      <translation>Jiné</translation>
    </message>
    <message>
      <source>Read Only</source>
      <translation>Jen ke čtení</translation>
    </message>
    <message>
      <source>Required</source>
      <translation>Požadované</translation>
    </message>
    <message>
      <source>Don't Export Value</source>
      <translation>Neexportovat hodnotu</translation>
    </message>
    <message>
      <source>Visibility:</source>
      <translation>Viditelnost:</translation>
    </message>
    <message>
      <source>Visible</source>
      <translation>Viditelné</translation>
    </message>
    <message>
      <source>Hidden</source>
      <translation>Skryté</translation>
    </message>
    <message>
      <source>No Print</source>
      <translation>Bez tisku</translation>
    </message>
    <message>
      <source>No View</source>
      <translation>Bez náhledu</translation>
    </message>
    <message>
      <source>Appearance</source>
      <translation>Vzhled</translation>
    </message>
    <message>
      <source>Text for Button Down</source>
      <translation>Text pro tlačítko Dolů</translation>
    </message>
    <message>
      <source>Text for Roll Over</source>
      <translation>Text pro přetočení</translation>
    </message>
    <message>
      <source>Icons</source>
      <translation>Ikony</translation>
    </message>
    <message>
      <source>Use Icons</source>
      <translation>Použít ikony</translation>
    </message>
    <message>
      <source>Remove</source>
      <translation>Odstranit</translation>
    </message>
    <message>
      <source>Pressed</source>
      <translation>Stlačené</translation>
    </message>
    <message>
      <source>Roll Over</source>
      <translation>Přetočit</translation>
    </message>
    <message>
      <source>Icon Placement...</source>
      <translation>Umístění ikon...</translation>
    </message>
    <message>
      <source>Highlight</source>
      <translation>Zvýraznění</translation>
    </message>
    <message>
      <source>Invert</source>
      <translation>Invertovat</translation>
    </message>
    <message>
      <source>Outlined</source>
      <translation>Obkreslené</translation>
    </message>
    <message>
      <source>Push</source>
      <translation>Stisknout</translation>
    </message>
    <message>
      <source>Multi-Line</source>
      <translation>Víceřádkový</translation>
    </message>
    <message>
      <source>Password</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <source>Limit of</source>
      <translation>Omezení</translation>
    </message>
    <message>
      <source>Characters</source>
      <translation>Znaky</translation>
    </message>
    <message>
      <source>Do Not Scroll</source>
      <translation>Neposouvat</translation>
    </message>
    <message>
      <source>Do Not Spell Check</source>
      <translation>Nekontrolovat pravopis</translation>
    </message>
    <message>
      <source>Check Style:</source>
      <translation>Ověřit styl:</translation>
    </message>
    <message>
      <source>Check</source>
      <translation>Kontrolovat</translation>
    </message>
    <message>
      <source>Cross</source>
      <translation>Kříž</translation>
    </message>
    <message>
      <source>Diamond</source>
      <translation>Diamant</translation>
    </message>
    <message>
      <source>Circle</source>
      <translation>Kruh</translation>
    </message>
    <message>
      <source>Star</source>
      <translation>Hvězda</translation>
    </message>
    <message>
      <source>Square</source>
      <translation>Čtverec</translation>
    </message>
    <message>
      <source>Default is Checked</source>
      <translation>Standardně je označené</translation>
    </message>
    <message>
      <source>Editable</source>
      <translation>Upravitelné</translation>
    </message>
    <message>
      <source>Options</source>
      <translation>Možnosti</translation>
    </message>
    <message>
      <source>Java Script</source>
      <translation>JavaScript</translation>
    </message>
    <message>
      <source>Go To</source>
      <translation>Jít na</translation>
    </message>
    <message>
      <source>Submit Form</source>
      <translation>Potvrdit formulář</translation>
    </message>
    <message>
      <source>Reset Form</source>
      <translation>Vynulovat formulář</translation>
    </message>
    <message>
      <source>Import Data</source>
      <translation>Importovat data</translation>
    </message>
    <message>
      <source>Event:</source>
      <translation>Událost:</translation>
    </message>
    <message>
      <source>Mouse Up</source>
      <translation>Uvolnění myši</translation>
    </message>
    <message>
      <source>Mouse Down</source>
      <translation>Stisk tlačítka myši</translation>
    </message>
    <message>
      <source>Mouse Enter</source>
      <translation>Najetí myši</translation>
    </message>
    <message>
      <source>Mouse Exit</source>
      <translation>Opuštění myší</translation>
    </message>
    <message>
      <source>On Focus</source>
      <translation>Po přepnutí na</translation>
    </message>
    <message>
      <source>On Blur</source>
      <translation>Při rozmazání</translation>
    </message>
    <message>
      <source>Script:</source>
      <translation>Skript:</translation>
    </message>
    <message>
      <source>Edit...</source>
      <translation>Upravit...</translation>
    </message>
    <message>
      <source>Submit to URL:</source>
      <translation>Odeslat na URL:</translation>
    </message>
    <message>
      <source>Submit Data as HTML</source>
      <translation>Odeslat údaje jako HTML</translation>
    </message>
    <message>
      <source>Import Data from:</source>
      <translation>Importovat data z:</translation>
    </message>
    <message>
      <source>Destination</source>
      <translation>Cíl</translation>
    </message>
    <message>
      <source>To File:</source>
      <translation>Do souboru:</translation>
    </message>
    <message>
      <source>Change...</source>
      <translation>Změnit...</translation>
    </message>
    <message>
      <source>Page:</source>
      <translation>Strana:</translation>
    </message>
    <message>
      <source>X-Pos:</source>
      <translation>X-Poz:</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Y-Pos:</source>
      <translation>Y-Poz:</translation>
    </message>
    <message>
      <source>Action</source>
      <translation>Akce</translation>
    </message>
    <message>
      <source>Field is formatted as:</source>
      <translation>Pole je naformátované jako:</translation>
    </message>
    <message>
      <source>Plain</source>
      <translation>Obyčejný</translation>
    </message>
    <message>
      <source>Number</source>
      <translation>Číslo</translation>
    </message>
    <message>
      <source>Percentage</source>
      <translation>Procento</translation>
    </message>
    <message>
      <source>Date</source>
      <translation>Datum</translation>
    </message>
    <message>
      <source>Time</source>
      <translation>Čas</translation>
    </message>
    <message>
      <source>Custom</source>
      <translation>Vlastní</translation>
    </message>
    <message>
      <source>Number Format</source>
      <translation>Formát čísla</translation>
    </message>
    <message>
      <source>Decimals:</source>
      <translation>Desetinné:</translation>
    </message>
    <message>
      <source>Use Currency Symbol</source>
      <translation>Použít symbol měny</translation>
    </message>
    <message>
      <source>Prepend Currency Symbol</source>
      <translation>Symbol měny vpředu</translation>
    </message>
    <message>
      <source>Formatting</source>
      <translation>Formátování</translation>
    </message>
    <message>
      <source>Percent Format</source>
      <translation>Formát procent</translation>
    </message>
    <message>
      <source>Date Format</source>
      <translation>Formát data</translation>
    </message>
    <message>
      <source>Time Format</source>
      <translation>Formát času</translation>
    </message>
    <message>
      <source>Custom Scripts</source>
      <translation>Vlastní skripty</translation>
    </message>
    <message>
      <source>Format:</source>
      <translation>Formát:</translation>
    </message>
    <message>
      <source>Keystroke:</source>
      <translation>Stlačení klávesy:</translation>
    </message>
    <message>
      <source>Format</source>
      <translation>Formát</translation>
    </message>
    <message>
      <source>Value is not validated</source>
      <translation>Hodnota není potvrzena</translation>
    </message>
    <message>
      <source>Value must be greater than or equal to:</source>
      <translation>Hodnota musí být větší nebo rovná:</translation>
    </message>
    <message>
      <source>and less or equal to:</source>
      <translation>a menší nebo rovná:</translation>
    </message>
    <message>
      <source>Custom validate script:</source>
      <translation>Vlastní ověření skriptu:</translation>
    </message>
    <message>
      <source>Validate</source>
      <translation>Vyhodnotit</translation>
    </message>
    <message>
      <source>Value is not calculated</source>
      <translation>Hodnota není vypočítaná</translation>
    </message>
    <message>
      <source>Value is the</source>
      <translation>Hodnota je</translation>
    </message>
    <message>
      <source>sum</source>
      <translation>součet</translation>
    </message>
    <message>
      <source>product</source>
      <translation>součin</translation>
    </message>
    <message>
      <source>average</source>
      <translation>průměr</translation>
    </message>
    <message>
      <source>minimum</source>
      <translation>minimum</translation>
    </message>
    <message>
      <source>maximum</source>
      <translation>maximum</translation>
    </message>
    <message>
      <source>of the following fields:</source>
      <translation>následujících polí:</translation>
    </message>
    <message>
      <source>Pick...</source>
      <translation>Vybrat...</translation>
    </message>
    <message>
      <source>Custom calculation script:</source>
      <translation>Vlastní počítací skript:</translation>
    </message>
    <message>
      <source>Calculate</source>
      <translation>Vypočítat</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Enter a comma separated list of fields here</source>
      <translation>Vložte sem čárkami oddělený seznam polí</translation>
    </message>
    <message>
      <source>You need at least the Icon for Normal to use Icons for Buttons</source>
      <translation>Potřebujete minimálně ikonu pro Normal, abyste mohl(a) použít ikony pro tlačítka</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Images (*.tif *.png *.jpg *.xpm);;Postscript (*.eps);;All Files (*)</source>
      <translation>Obrázky (*.tif *.png *.jpg *.xpm);;Postscript (*.eps);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Example:</source>
      <translation>Příklad:</translation>
    </message>
    <message>
      <source>Selection Change</source>
      <translation>Změna výběru</translation>
    </message>
    <message>
      <source>Font for use with PDF 1.3:</source>
      <translation>Písmo užité v PDF 1.3:</translation>
    </message>
    <message>
      <source>Flag is ignored for PDF 1.3</source>
      <translation>Indikátor je v PDF 1.3 ignorován</translation>
    </message>
    <message>
      <source>PDF Files (*.pdf);;All Files (*)</source>
      <translation>PDF soubory (*.pdf);;Všechny soubory (*)</translation>
    </message>
  </context>
  <context>
    <name>Annota</name>
    <message>
      <source>Annotation Properties</source>
      <translation>Vlastnosti poznámky</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Link</source>
      <translation>Odkaz</translation>
    </message>
    <message>
      <source>External Link</source>
      <translation>Odkaz ven</translation>
    </message>
    <message>
      <source>External Web-Link</source>
      <translation>Odkaz ven na web</translation>
    </message>
    <message>
      <source>Destination</source>
      <translation>Cíl</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>PDF-Documents (*.pdf);;All Files (*)</source>
      <translation>PDF dokumenty (*.pdf);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>&amp;Type:</source>
      <translation>&amp;Typ:</translation>
    </message>
    <message>
      <source>C&amp;hange...</source>
      <translation>Z&amp;měnit...</translation>
    </message>
    <message>
      <source>&amp;Page:</source>
      <translation>Str&amp;ana:</translation>
    </message>
    <message>
      <source>&amp;X-Pos</source>
      <translation>&amp;X-Poz</translation>
    </message>
    <message>
      <source>&amp;Y-Pos:</source>
      <translation>&amp;Y-Poz:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>ApplyT</name>
    <message>
      <source>Apply Template</source>
      <translation>Použít šablonu</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>&amp;Template:</source>
      <translation>Ša&amp;blona:</translation>
    </message>
    <message>
      <source>Apply to &amp;Current Page</source>
      <translation>&amp;Použít na aktuální stranu</translation>
    </message>
    <message>
      <source>Apply from &amp;Page:</source>
      <translation>Použít od &amp;strany:</translation>
    </message>
    <message>
      <source>To:</source>
      <translation>po:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Apply to all &amp;even Pages</source>
      <translation>Použít na všechny &amp;sudé strany</translation>
    </message>
    <message>
      <source>Apply to all &amp;odd Pages</source>
      <translation>Použít na všechny &amp;liché strany</translation>
    </message>
  </context>
  <context>
    <name>Biblio</name>
    <message>
      <source>Scrapbook</source>
      <translation>Zápisník</translation>
    </message>
    <message>
      <source>Scrapbooks (*.scs);;All Files (*)</source>
      <translation>Zápisníky (*.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Delete</source>
      <translation>Smazat</translation>
    </message>
    <message>
      <source>Object</source>
      <translation>Objekt</translation>
    </message>
    <message>
      <source>New Entry</source>
      <translation>Nová položka</translation>
    </message>
    <message>
      <source>Rename</source>
      <translation>Přejmenovat</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name &quot;%1&quot; isn't unique.
Please choose another.</source>
      <translation>Název &quot;%1&quot; není jedinečný.
Vyberte, prosím, jiný.</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Load...</source>
      <translation>&amp;Načíst...</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>Save &amp;As...</source>
      <translation>Uložit j&amp;ako...</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>&amp;Small</source>
      <translation>&amp;Malý</translation>
    </message>
    <message>
      <source>&amp;Medium</source>
      <translation>&amp;Střední</translation>
    </message>
    <message>
      <source>&amp;Large</source>
      <translation>&amp;Velký</translation>
    </message>
    <message>
      <source>&amp;File</source>
      <translation>&amp;Soubor</translation>
    </message>
    <message>
      <source>&amp;Preview</source>
      <translation>&amp;Náhled</translation>
    </message>
    <message>
      <source>&amp;Name:</source>
      <translation>&amp;Jméno:</translation>
    </message>
  </context>
  <context>
    <name>BookMView</name>
    <message>
      <source>Bookmarks</source>
      <translation>Záložky</translation>
    </message>
    <message>
      <source>Move Bookmark</source>
      <translation>Přesunout záložku</translation>
    </message>
    <message>
      <source>Insert Bookmark</source>
      <translation>Vložit záložku</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
  </context>
  <context>
    <name>BookPalette</name>
    <message>
      <source>Bookmarks</source>
      <translation>Záložky</translation>
    </message>
  </context>
  <context>
    <name>ButtonIcon</name>
    <message>
      <source>Icon Placement</source>
      <translation>Umístění ikon</translation>
    </message>
    <message>
      <source>Layout:</source>
      <translation>Návrh úpravy sazby:</translation>
    </message>
    <message>
      <source>Caption only</source>
      <translation>Jen popisky</translation>
    </message>
    <message>
      <source>Icon only</source>
      <translation>Jen ikony </translation>
    </message>
    <message>
      <source>Caption below Icon</source>
      <translation>Popisky pod ikonami</translation>
    </message>
    <message>
      <source>Caption above Icon</source>
      <translation>Popisky nad ikonami</translation>
    </message>
    <message>
      <source>Caption right to Icon</source>
      <translation>Popisky vpravo od ikon</translation>
    </message>
    <message>
      <source>Caption left to Icon</source>
      <translation>Popisky vlevo od ikon</translation>
    </message>
    <message>
      <source>Caption overlays Icon</source>
      <translation>Popisky překrývají ikony</translation>
    </message>
    <message>
      <source>Scale:</source>
      <translation>Měřítko:</translation>
    </message>
    <message>
      <source>Always</source>
      <translation>Vždy</translation>
    </message>
    <message>
      <source>When Icon is too small</source>
      <translation>Když jsou ikony příliš malé</translation>
    </message>
    <message>
      <source>When Icon is too big</source>
      <translation>Když jsou ikony příliš velké</translation>
    </message>
    <message>
      <source>Never</source>
      <translation>Nikdy</translation>
    </message>
    <message>
      <source>Scale How:</source>
      <translation>Jak změnit:</translation>
    </message>
    <message>
      <source>Proportional</source>
      <translation>Proporcionálně</translation>
    </message>
    <message>
      <source>Non Proportional</source>
      <translation>Neproporcionálně</translation>
    </message>
    <message>
      <source>Icon</source>
      <translation>Ikona</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Reset</source>
      <translation>Vynulovat</translation>
    </message>
  </context>
  <context>
    <name>CMSPrefs</name>
    <message>
      <source>Color Management Settings</source>
      <translation>Nastavení správy barev</translation>
    </message>
    <message>
      <source>System Profiles</source>
      <translation>Systémové profily</translation>
    </message>
    <message>
      <source>Rendering Intents</source>
      <translation>Účel reprodukce (rendering)</translation>
    </message>
    <message>
      <source>Perceptual</source>
      <translation>Perceptuální (fotografická) transformace</translation>
    </message>
    <message>
      <source>Relative Colorimetric</source>
      <translation>Relativní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Saturation</source>
      <translation>Sytost</translation>
    </message>
    <message>
      <source>Absolute Colorimetric</source>
      <translation>Absolutní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Default color profile for imported images</source>
      <translation>Implicitní barevný profil na importované obrázky</translation>
    </message>
    <message>
      <source>Default color profile for solid colors on the page</source>
      <translation>Implicitní barevný profil na plné barvy na straně</translation>
    </message>
    <message>
      <source>Color profile that you have generated or received from the manufacturer.
This profile should be specific to your monitor and not a generic profile (i.e. sRGB).</source>
      <translation>Barevný profil, který máte vygenerován nebo dodán od výrobce zařízení.
Tento profil by měl být nastavený na váše prostředí - ne obecný (např. sRGB).</translation>
    </message>
    <message>
      <source>Color profile for your printer model from the manufacturer.
This profile should be specific to your printer and not a generic profile (i.e. sRGB).</source>
      <translation>Barevný profil vaší tiskárny, který máte od výrobce.
Tento profil by měl být nastavený na váše prostředí - ne obecný (např. sRGB).</translation>
    </message>
    <message>
      <source>Default rendering intent for your monitor. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
      <translation>Implicitní účel reprodukce monitoru. Jestliže víte, proč jej změnit, zvolte
relativní kolorimetrickou transformaci nebo perceptuální (fotografickou) transformaci.</translation>
    </message>
    <message>
      <source>Default rendering intent for your printer. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
      <translation>Implicitní účel reprodukce tiskárny. Jestliže víte, proč jej změnit, zvolte
relativní kolorimetrickou transformaci nebo perceptuální (fotografickou) transformaci.</translation>
    </message>
    <message>
      <source>Enable 'soft proofing' of how your document colors will print,
based on the chosen printer profile.</source>
      <translation>Povolit &quot;soft proofing&quot; (nátisk) založený na vybraném profilu tiskárny.</translation>
    </message>
    <message>
      <source>Method of showing colors on the screen which may not print properly.
This requires very accurate profiles and serves only as a warning.</source>
      <translation>Výsledek tisku barev bývá rozdílný od toho, jak jsou zobrazeny barvy na monitoru.
Proto jsou důležité kvalitní profily.</translation>
    </message>
    <message>
      <source>Black Point Compensation is a method of improving contrast in photos.
It is recommended that you enable this if you have photos in your document.</source>
      <translation>Mapování černé barvy ze dvou profilů (blackpoint compensation) je způsob,
jakým lze zlepšit kontrast fotografií. Doporučeno, jestliže je máte v dokumentu.</translation>
    </message>
    <message>
      <source>&amp;Activate Color Management</source>
      <translation>&amp;Aktivovat správu barev</translation>
    </message>
    <message>
      <source>&amp;Pictures:</source>
      <translation>&amp;Obrázky:</translation>
    </message>
    <message>
      <source>&amp;Solid Colors:</source>
      <translation>&amp;Plné barvy (Solid colors):</translation>
    </message>
    <message>
      <source>&amp;Monitor:</source>
      <translation>&amp;Monitor:</translation>
    </message>
    <message>
      <source>P&amp;rinter:</source>
      <translation>&amp;Tiskárna:</translation>
    </message>
    <message>
      <source>M&amp;onitor:</source>
      <translation>Mo&amp;nitor:</translation>
    </message>
    <message>
      <source>Pr&amp;inter:</source>
      <translation>Tis&amp;kárna:</translation>
    </message>
    <message>
      <source>Sim&amp;ulate Printer on the Screen</source>
      <translation>Sim&amp;ulace tisku na obrazovce</translation>
    </message>
    <message>
      <source>Mark Colors out of &amp;Gamut</source>
      <translation>Označ netisknutelné barvy (&amp;gamut)</translation>
    </message>
    <message>
      <source>Use &amp;Blackpoint Compensation</source>
      <translation>Použí&amp;t mapování černé ze dvou profilů</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>CMYKChoose</name>
    <message>
      <source>Edit Color</source>
      <translation>Upravit barvu</translation>
    </message>
    <message>
      <source>CMYK</source>
      <translation>CMYK</translation>
    </message>
    <message>
      <source>RGB</source>
      <translation>RGB</translation>
    </message>
    <message>
      <source>Web Safe RGB</source>
      <translation>RGB pro web</translation>
    </message>
    <message>
      <source>New</source>
      <translation>Nový</translation>
    </message>
    <message>
      <source>Old</source>
      <translation>Starý</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>C:</source>
      <translation>C:</translation>
    </message>
    <message>
      <source>M:</source>
      <translation>M:</translation>
    </message>
    <message>
      <source>Y:</source>
      <translation>Y:</translation>
    </message>
    <message>
      <source>K:</source>
      <translation>K:</translation>
    </message>
    <message>
      <source>Dynamic Color Bars</source>
      <translation>Mřížky s dynamickými barvami</translation>
    </message>
    <message>
      <source>Static Color Bars</source>
      <translation>Mřížky se statickými barvami</translation>
    </message>
    <message>
      <source>R:</source>
      <translation>R:</translation>
    </message>
    <message>
      <source>G:</source>
      <translation>G:</translation>
    </message>
    <message>
      <source>B:</source>
      <translation>B:</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name of the Color is not unique</source>
      <translation>Jméno barvy není unikátní</translation>
    </message>
    <message>
      <source>HSV-Colormap</source>
      <translation>HSV-barevná mapa</translation>
    </message>
    <message>
      <source>&amp;Name:</source>
      <translation>&amp;Jméno:</translation>
    </message>
    <message>
      <source>Color &amp;Model</source>
      <translation>&amp;Barevný model</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádná</translation>
    </message>
    <message>
      <source>You cannot create a color named &quot;%1&quot;.
It's a reserved name for transparent color</source>
      <translation>Nelze vytvořit barvu jménem &quot;%1&quot;.
Název je rezervován pro transparentní barvu</translation>
    </message>
  </context>
  <context>
    <name>Cpalette</name>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Horizontal Gradient</source>
      <translation>Vodorovný přechod</translation>
    </message>
    <message>
      <source>Vertical Gradient</source>
      <translation>Vertikální přechod</translation>
    </message>
    <message>
      <source>Diagonal Gradient</source>
      <translation>Úhlopříčný přechod</translation>
    </message>
    <message>
      <source>Cross Diagonal Gradient</source>
      <translation>Obrácený úhlopříčný přechod</translation>
    </message>
    <message>
      <source>Radial Gradient</source>
      <translation>Kruhový přechod</translation>
    </message>
    <message>
      <source>Opacity:</source>
      <translation>Neprůsvitnost:</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Shade:</source>
      <translation>Stín:</translation>
    </message>
    <message>
      <source>Edit Line Color Properties</source>
      <translation>Barva obrysu</translation>
    </message>
    <message>
      <source>Edit Fill Color Properties</source>
      <translation>Barva výplně</translation>
    </message>
    <message>
      <source>Saturation of color</source>
      <translation>Sytost barvy</translation>
    </message>
    <message>
      <source>Normal or gradient fill method</source>
      <translation>Normální výplň nebo přechody</translation>
    </message>
    <message>
      <source>Set the transparency for the color selected</source>
      <translation>Nastavení průhlednosti vybrané barvy</translation>
    </message>
    <message>
      <source>Color of selected object</source>
      <translation>Barva vybraného objektu</translation>
    </message>
    <message>
      <source>Free linear Gradient</source>
      <translation>Volný lineární gradient</translation>
    </message>
    <message>
      <source>Free radial Gradient</source>
      <translation>Volný radiální gradient</translation>
    </message>
    <message>
      <source>X1:</source>
      <translation>X1:</translation>
    </message>
    <message>
      <source>Y1:</source>
      <translation>Y1:</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>X2:</source>
      <translation>X2:</translation>
    </message>
    <message>
      <source>Y2:</source>
      <translation>Y2:</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
  </context>
  <context>
    <name>CsvDialog</name>
    <message>
      <source>CSV Importer Options</source>
      <translation>Nastavení importu CSV</translation>
    </message>
    <message>
      <source>Field delimiter:</source>
      <translation>Oddělovač položek:</translation>
    </message>
    <message>
      <source>(TAB)</source>
      <translation>(TAB)</translation>
    </message>
    <message>
      <source>Value delimiter:</source>
      <translation>Oddělovač hodnot:</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádný</translation>
    </message>
    <message>
      <source>First row is a header</source>
      <translation>První řádek je hlavička</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
  </context>
  <context>
    <name>CupsOptions</name>
    <message>
      <source>Printer Options</source>
      <translation>Možnosti tiskárny</translation>
    </message>
    <message>
      <source>Option</source>
      <translation>Volba</translation>
    </message>
    <message>
      <source>Value</source>
      <translation>Hodnota</translation>
    </message>
    <message>
      <source>Page Set</source>
      <translation>Nastavení strany</translation>
    </message>
    <message>
      <source>All Pages</source>
      <translation>Všechny strany</translation>
    </message>
    <message>
      <source>Even Pages only</source>
      <translation>Pouze sudé strany</translation>
    </message>
    <message>
      <source>Odd Pages only</source>
      <translation>Pouze liché strany</translation>
    </message>
    <message>
      <source>Mirror</source>
      <translation>Zrcadlo</translation>
    </message>
    <message>
      <source>No</source>
      <translation>Ne</translation>
    </message>
    <message>
      <source>Yes</source>
      <translation>Ano</translation>
    </message>
    <message>
      <source>Orientation</source>
      <translation>Orientace</translation>
    </message>
    <message>
      <source>Portrait</source>
      <translation>Na výšku</translation>
    </message>
    <message>
      <source>Landscape</source>
      <translation>Na šířku</translation>
    </message>
    <message>
      <source>N-Up Printing</source>
      <translation>N-Up tisk</translation>
    </message>
    <message>
      <source>Page per Sheet</source>
      <translation>Strana na arch</translation>
    </message>
    <message>
      <source>Pages per Sheet</source>
      <translation>Stran na arch</translation>
    </message>
    <message>
      <source>This panel displays various CUPS options when printing. 
The exact parameters available will depend on your printer driver.
You can confirm CUPS support by selecting Help > About.
Look for the listings: C-C-T These equate to C=CUPS C=littlecms T=TIFF support.
Missing library support is indicated by a *</source>
      <translation>Okno zobrazuje různá nastavení CUPS během tisku.
Dostupnost vlastních parametrů závisí na ovladači vaší tiskárny.
Podporu CUPS zjistíte v menu Nápověda > O Scribusu.
Text: C-C-T znamená podporu C-CUPS, C-littlecms a T-TIFF.
Chybějící knihovny jsou zobrazeny jako *</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>CustomFDialog</name>
    <message>
      <source>Encoding:</source>
      <translation>Kódování:</translation>
    </message>
    <message>
      <source>Moves to your Document Directory.
This can be set in the Preferences.</source>
      <translation>Přesunutí do adresáře dokumentů.
Lze uvést v Nastavení.</translation>
    </message>
    <message>
      <source>&amp;Compress File</source>
      <translation>&amp;Komprimovaný soubor</translation>
    </message>
    <message>
      <source>&amp;Include Fonts</source>
      <translation>Včetně &amp;písem</translation>
    </message>
  </context>
  <context>
    <name>DelColor</name>
    <message>
      <source>Delete Color</source>
      <translation>Smazat barvu</translation>
    </message>
    <message>
      <source>?</source>
      <translation>?</translation>
    </message>
    <message>
      <source>Replace it with:</source>
      <translation>Nahradit čím:</translation>
    </message>
    <message>
      <source>Delete color:</source>
      <translation>Smazat barvu:</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádná</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>DelPages</name>
    <message>
      <source>Delete Pages</source>
      <translation>Smazat strany</translation>
    </message>
    <message>
      <source>Delete from:</source>
      <translation>Smazat od:</translation>
    </message>
    <message>
      <source>to:</source>
      <translation>po:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>DmF</name>
    <message>
      <source>Missing Font</source>
      <translation>Chybějící písmo</translation>
    </message>
    <message>
      <source>The Font %1 is not installed.</source>
      <translation>Písmo %1 není nainstalované.</translation>
    </message>
    <message>
      <source>Use</source>
      <translation>Použít</translation>
    </message>
    <message>
      <source>instead</source>
      <translation>místo</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
  </context>
  <context>
    <name>DocInfos</name>
    <message>
      <source>Document Information</source>
      <translation>Informace o dokumentu</translation>
    </message>
    <message>
      <source>&amp;Title:</source>
      <translation>&amp;Název:</translation>
    </message>
    <message>
      <source>&amp;Author:</source>
      <translation>&amp;Autor:</translation>
    </message>
    <message>
      <source>&amp;Keywords:</source>
      <translation>&amp;Klíčová slova:</translation>
    </message>
    <message>
      <source>Descri&amp;ption:</source>
      <translation>&amp;Popis:</translation>
    </message>
    <message>
      <source>P&amp;ublisher:</source>
      <translation>&amp;Vydavatel:</translation>
    </message>
    <message>
      <source>&amp;Contributors:</source>
      <translation>Př&amp;ispěvatelé:</translation>
    </message>
    <message>
      <source>Dat&amp;e:</source>
      <translation>&amp;Datum:</translation>
    </message>
    <message>
      <source>T&amp;ype:</source>
      <translation>&amp;Typ:</translation>
    </message>
    <message>
      <source>F&amp;ormat:</source>
      <translation>&amp;Formát:</translation>
    </message>
    <message>
      <source>Identi&amp;fier:</source>
      <translation>Identi&amp;fikátor:</translation>
    </message>
    <message>
      <source>&amp;Source:</source>
      <translation>&amp;Zdroj:</translation>
    </message>
    <message>
      <source>&amp;Language:</source>
      <translation>&amp;Jazyk:</translation>
    </message>
    <message>
      <source>&amp;Relation:</source>
      <translation>&amp;Odkaz:</translation>
    </message>
    <message>
      <source>Co&amp;verage:</source>
      <translation>O&amp;blast:</translation>
    </message>
    <message>
      <source>Ri&amp;ghts:</source>
      <translation>P&amp;ráva:</translation>
    </message>
    <message>
      <source>&amp;Document</source>
      <translation>&amp;Dokument</translation>
    </message>
    <message>
      <source>Further &amp;Information</source>
      <translation>Da&amp;lší informace</translation>
    </message>
    <message>
      <source>The person or organisation primarily responsible for making the content of the document.
This field can be embedded in the Scribus document for reference, as well as in the metadata of a PDF</source>
      <translation>Osoba nebo organizace, která je zodpovědná za obsah dokumentu.
Tato položka může být vložena v dokumentu jako reference nebo také jako metadata v PDF</translation>
    </message>
    <message>
      <source>A name given to the document.
This field can be embedded in the Scribus document for reference, as well as in the metadata of a PDF</source>
      <translation>Název dokumentu.
Tato položka může být vložena v dokumentu jako reference nebo také jako metadata v PDF</translation>
    </message>
    <message>
      <source>An account of the content of the document.
This field is for a brief description or abstract of the document. It is embedded in the PDF on export</source>
      <translation>Popis obsahu dokumentu.
Zapište sem abstrakt, ten bude vložen do PDF soubotu při exportu</translation>
    </message>
    <message>
      <source>The topic of the content of the document.
This field is for document keywords you wish to embed in a PDF, to assist searches and indexing of PDF files</source>
      <translation>Shrnutí obsahu dokumentu klíčovými slovy.
Klíčová slova budou vložena do PDF, podle nich bude PDF soubor indexován a vyhledáván automatizovanými nástroji</translation>
    </message>
    <message>
      <source>A person or organisation responsible for making the document available</source>
      <translation>Osoba nebo organizace, která dokument zveřejňuje, publikuje nebo vydává</translation>
    </message>
    <message>
      <source>A person or organisation responsible for making contributions to the content of the document</source>
      <translation>Osoby nebo organizace, které přispěly k obsahu dokumentu</translation>
    </message>
    <message>
      <source>A date associated with an event in the life cycle of the document, in YYYY-MM-DD format, as per ISO 8601</source>
      <translation>Datum přiřazený k události v životním cyklu dokumentu. Použijte RRRR-MM-DD formát podle ISO 8601</translation>
    </message>
    <message>
      <source>The nature or genre of the content of the document, eg. categories, functions, genres, etc</source>
      <translation>Povaha dokumentu. Např. kategorie, finkce atd</translation>
    </message>
    <message>
      <source>The physical or digital manifestation of the document. Media type and dimensions would be worth noting.
RFC2045,RFC2046 for MIME types are also useful here</source>
      <translation>Elektronická reprezentace dokumentu.
Např. RFC2045,RFC2046 t.j. MIME typy</translation>
    </message>
    <message>
      <source>An unambiguous reference to the document within a given context such as ISBN or URI</source>
      <translation>Jednoznačný odkaz na dokument. Např. ISBN nebo URI</translation>
    </message>
    <message>
      <source>A reference to a document from which the present document is derived, eg. ISBN or URI</source>
      <translation>Odkaz na dokument, ze kterého tento vychází. Např. ISBN nebo URI</translation>
    </message>
    <message>
      <source>The language in which the content of the document is written, usually a ISO-639 language code
optionally suffixed with a hypen and an ISO-3166 country code, eg. en-GB, fr-CH</source>
      <translation>Jazyk, ve kterém je dokument napsán. Obvykle kód jazyka ISO-639
volitelně s kódem země ISO-3166 např. cs-CZ, en-GB</translation>
    </message>
    <message>
      <source>A reference to a related document, possibly using a formal identifier such as a ISBN or URI</source>
      <translation>Odkaz na související dokument např. ISBN nebo URI</translation>
    </message>
    <message>
      <source>The extent or scope of the content of the document, possibly including location, time and jurisdiction ranges</source>
      <translation>Rozšířený rámec obsahu dokumentu - oblast působnosti, datum anebo soudní pravomoc atd</translation>
    </message>
    <message>
      <source>Information about rights held in and over the document, eg. copyright, patent or trademark</source>
      <translation>Informace o autorských právech, licencích apod. Např. copyright, patenty nebo obchodní značka</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>Druck</name>
    <message>
      <source>Setup Printer</source>
      <translation>Nastavit tiskárnu</translation>
    </message>
    <message>
      <source>File</source>
      <translation>Soubor</translation>
    </message>
    <message>
      <source>Options</source>
      <translation>Možnosti</translation>
    </message>
    <message>
      <source>All</source>
      <translation>Všechny</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>Postscript-Files (*.ps);;All Files (*)</source>
      <translation>Postscriptové soubory (*.ps);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Cyan</source>
      <translation>Azurová (Cyan)</translation>
    </message>
    <message>
      <source>Magenta</source>
      <translation>Purpurová (Magenta)</translation>
    </message>
    <message>
      <source>Yellow</source>
      <translation>Žlutá (Yellow)</translation>
    </message>
    <message>
      <source>Black</source>
      <translation>Černá (Black)</translation>
    </message>
    <message>
      <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
      <translation>Vložte čárkou oddělený seznam položek, kde
položka může být *, t.j. všechny strany, 1-5,
t.j. interval, nebo jediné číslo strany.</translation>
    </message>
    <message>
      <source>Print Destination</source>
      <translation>Tisk do</translation>
    </message>
    <message>
      <source>&amp;Options...</source>
      <translation>&amp;Možnosti...</translation>
    </message>
    <message>
      <source>&amp;File:</source>
      <translation>&amp;Soubor:</translation>
    </message>
    <message>
      <source>C&amp;hange...</source>
      <translation>&amp;Změnit...</translation>
    </message>
    <message>
      <source>A&amp;lternative Printer Command</source>
      <translation>A&amp;lternativní příkaz tisku</translation>
    </message>
    <message>
      <source>Co&amp;mmand:</source>
      <translation>&amp;Příkaz:</translation>
    </message>
    <message>
      <source>Range</source>
      <translation>Interval</translation>
    </message>
    <message>
      <source>Print &amp;All</source>
      <translation>Tisnout &amp;vše</translation>
    </message>
    <message>
      <source>Print Current Pa&amp;ge</source>
      <translation>Ti&amp;sknout aktuální stranu</translation>
    </message>
    <message>
      <source>Print &amp;Range</source>
      <translation>T&amp;isknout interval</translation>
    </message>
    <message>
      <source>N&amp;umber of Copies:</source>
      <translation>&amp;Počet kopií:</translation>
    </message>
    <message>
      <source>Print &amp;Normal</source>
      <translation>&amp;Normální tisk</translation>
    </message>
    <message>
      <source>Print &amp;Separations</source>
      <translation>Tisk &amp;separací</translation>
    </message>
    <message>
      <source>Pr&amp;int In Color If Available</source>
      <translation>Tisknout &amp;barevně, jestliže je to možné</translation>
    </message>
    <message>
      <source>Print In Gra&amp;yscale</source>
      <translation>Tis&amp;knout v odstínech šedi</translation>
    </message>
    <message>
      <source>Ad&amp;vanced Options...</source>
      <translation>Pok&amp;ročilé možnosti...</translation>
    </message>
    <message>
      <source>&amp;Print</source>
      <translation>&amp;Tisk</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Use an alternative print manager, such as kprinter or gtklp,
to utilize additional printing options</source>
      <translation>Použít alternativní správce tisku, jako jsou např. kprinter nebo gtklp.
Správce tisku nastaví dodatečné volby</translation>
    </message>
  </context>
  <context>
    <name>EPSPlug</name>
    <message>
      <source>Importing File:
%1
failed!</source>
      <translation>Import souboru:
%1
se nepodařil!</translation>
    </message>
    <message>
      <source>Fatal Error</source>
      <translation>Kritická chyba</translation>
    </message>
  </context>
  <context>
    <name>EditStyle</name>
    <message>
      <source>Edit Style</source>
      <translation>Upravit styl</translation>
    </message>
    <message>
      <source>Character</source>
      <translation>Znak</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Vertical Spaces</source>
      <translation>Vertikální mezery</translation>
    </message>
    <message>
      <source>Line Spacing</source>
      <translation>Řádkování</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name of the Style is not unique</source>
      <translation>Název stylu není jedinečný</translation>
    </message>
    <message>
      <source>Effect:</source>
      <translation>Efekt:</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Name of your paragraph style</source>
      <translation>Jméno stylu odstavce</translation>
    </message>
    <message>
      <source>Font of selected text or object</source>
      <translation>Písmo vybraného textu nebo objektu</translation>
    </message>
    <message>
      <source>Font Size</source>
      <translation>Velikost písma</translation>
    </message>
    <message>
      <source>Color of text fill</source>
      <translation>Barva výplně písma</translation>
    </message>
    <message>
      <source>Color of text stroke</source>
      <translation>Barva obrysu písma</translation>
    </message>
    <message>
      <source>Provides an oversized first letter for a paragraph. Used for stylistic effect</source>
      <translation>Nastaví mnohem větší první písmeno odstavce. Stylistický efekt</translation>
    </message>
    <message>
      <source>Determines the overall height, in line numbers, of the Drop Caps</source>
      <translation>Specifikace velikosti kapitálek podle počtu řádek</translation>
    </message>
    <message>
      <source>Align text to baseline grid</source>
      <translation>Zarovnat text k pomocné mřížce</translation>
    </message>
    <message>
      <source>Spacing above the paragraph</source>
      <translation>Horní odsazení odstavce</translation>
    </message>
    <message>
      <source>Spacing below the paragraph</source>
      <translation>Dolní odsazení odstavce</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>Tabulators and Indentation</source>
      <translation>Tabelátory a odsazení</translation>
    </message>
    <message>
      <source>&amp;Name:</source>
      <translation>&amp;Jméno:</translation>
    </message>
    <message>
      <source>&amp;Font:</source>
      <translation>&amp;Písmo:</translation>
    </message>
    <message>
      <source>Si&amp;ze:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <source>&amp;Alignment:</source>
      <translation>&amp;Zarovnání:</translation>
    </message>
    <message>
      <source>&amp;Drop Caps</source>
      <translation>&amp;Iniciály</translation>
    </message>
    <message>
      <source>&amp;Lines:</source>
      <translation>Čá&amp;ry:</translation>
    </message>
    <message>
      <source>F&amp;ill Color:</source>
      <translation>&amp;Barva výplně:</translation>
    </message>
    <message>
      <source>St&amp;roke Color:</source>
      <translation>Barva &amp;obrysu:</translation>
    </message>
    <message>
      <source>Adjust to Baseline &amp;Grid</source>
      <translation>Zarovnat k pomocné &amp;mřížce</translation>
    </message>
    <message>
      <source>Line &amp;Spacing:</source>
      <translation>Řád&amp;kování:</translation>
    </message>
    <message>
      <source>Abo&amp;ve:</source>
      <translation>&amp;Nad:</translation>
    </message>
    <message>
      <source>&amp;Below:</source>
      <translation>&amp;Pod:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>Editor</name>
    <message>
      <source>Editor</source>
      <translation>Editor</translation>
    </message>
    <message>
      <source>Javascripts (*.js);;All Files (*)</source>
      <translation>Java skripty (*.js);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Open...</source>
      <translation>&amp;Otevřít...</translation>
    </message>
    <message>
      <source>Save &amp;As...</source>
      <translation>Uložit j&amp;ako...</translation>
    </message>
    <message>
      <source>&amp;Save and Exit</source>
      <translation>&amp;Uložit a skončit</translation>
    </message>
    <message>
      <source>&amp;Exit without Saving</source>
      <translation>S&amp;končit bez uložení</translation>
    </message>
    <message>
      <source>&amp;Undo</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <source>&amp;Redo</source>
      <translation>&amp;Vpřed</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>&amp;Vymazat</translation>
    </message>
    <message>
      <source>&amp;Get Field Names</source>
      <translation>Získat &amp;jména polí</translation>
    </message>
    <message>
      <source>&amp;File</source>
      <translation>&amp;Soubor</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
  </context>
  <context>
    <name>ExportForm</name>
    <message>
      <source>&amp;All pages</source>
      <translation>Všechny str&amp;any</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>Z&amp;rušit</translation>
    </message>
    <message>
      <source>Change the output directory</source>
      <translation>Změnit výstupní adresář</translation>
    </message>
    <message>
      <source>The output directory - the place to store your images.
Name of the export file will be 'documentname-pagenumber.filetype'</source>
      <translation>Výstupní adresář - místo, kde budou uloženy vaše obrázky.
Jména exportovaných souborů budou ve tvaru 'jmenodokumentu-cislostrany.typ'</translation>
    </message>
    <message>
      <source>Export only the current page</source>
      <translation>Export pouze aktuální strany</translation>
    </message>
    <message>
      <source>Available export formats</source>
      <translation>Dostupné exportní formáty</translation>
    </message>
    <message>
      <source>Choose a Export Directory</source>
      <translation>Vyberte adresář</translation>
    </message>
    <message>
      <source>C&amp;hange...</source>
      <translation>&amp;Změnit...</translation>
    </message>
    <message>
      <source>&amp;Export to Directory:</source>
      <translation>&amp;Export do adresáře:</translation>
    </message>
    <message>
      <source>Image &amp;Type:</source>
      <translation>&amp;Typ obrázku:</translation>
    </message>
    <message>
      <source>&amp;Quality:</source>
      <translation>&amp;Kvalita:</translation>
    </message>
    <message>
      <source>Export as Image(s)</source>
      <translation>Uložit jako obrázky</translation>
    </message>
    <message>
      <source>Options</source>
      <translation>Možnosti</translation>
    </message>
    <message>
      <source>&amp;Resolution:</source>
      <translation>&amp;Rozlišení:</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source> dpi</source>
      <translation>dpi</translation>
    </message>
    <message>
      <source>Range</source>
      <translation>Interval</translation>
    </message>
    <message>
      <source>&amp;Current page</source>
      <translation>&amp;Aktuální strana</translation>
    </message>
    <message>
      <source>&amp;Range</source>
      <translation>&amp;Interval</translation>
    </message>
    <message>
      <source>C</source>
      <translation>C</translation>
    </message>
    <message>
      <source>Export a range of pages</source>
      <translation>Uložit interval stran</translation>
    </message>
    <message>
      <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
      <translation>Vložte čárkou oddělený seznam položek, kde
položka může být *, t.j. všechny strany, 1-5,
t.j. interval, nebo jediné číslo strany.</translation>
    </message>
    <message>
      <source>Export all pages</source>
      <translation>Uložit všechny strany</translation>
    </message>
    <message>
      <source>Resolution of the Images
Use 72 dpi for Images intended for the Screen</source>
      <translation>Rozlišení obrázků
Použijte 72 dpi, jestliže je obrázek určen na web nebo monitor</translation>
    </message>
    <message>
      <source>The quality of your images - 100% is the best, 1% the lowest quality</source>
      <translation>Kvalita obrázků - 100% je nejvyšší, 1% nejnižší</translation>
    </message>
    <message>
      <source>&amp;Size:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <source>Size of the images. 100% for no changes, 200% for two times larger etc.</source>
      <translation>Velikost obrázků. 100% beze změny, 200% dvakrát větší atd.</translation>
    </message>
  </context>
  <context>
    <name>FDialogPreview</name>
    <message>
      <source>Size:</source>
      <translation>Velikost:</translation>
    </message>
    <message>
      <source>Title:</source>
      <translation>Název:</translation>
    </message>
    <message>
      <source>No Title</source>
      <translation>Bez názvu</translation>
    </message>
    <message>
      <source>Author:</source>
      <translation>Autor:</translation>
    </message>
    <message>
      <source>Unknown</source>
      <translation>Neznámý</translation>
    </message>
    <message>
      <source>Scribus Document</source>
      <translation>Scribus dokument</translation>
    </message>
  </context>
  <context>
    <name>Farbmanager</name>
    <message>
      <source>Colors</source>
      <translation>Barvy</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Documents (*.sla *.scd);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Copy of %1</source>
      <translation>Kopie %1</translation>
    </message>
    <message>
      <source>Color Sets</source>
      <translation>Množiny barev</translation>
    </message>
    <message>
      <source>Current Color Set:</source>
      <translation>Aktuálí množina barev:</translation>
    </message>
    <message>
      <source>Choose a Name</source>
      <translation>Vybrat jméno</translation>
    </message>
    <message>
      <source>New Color</source>
      <translation>Nová barva</translation>
    </message>
    <message>
      <source>Choose a color set to load</source>
      <translation>Nahrát množinu barev</translation>
    </message>
    <message>
      <source>Save the current color set</source>
      <translation>Uložit aktuální množinu barev</translation>
    </message>
    <message>
      <source>Remove unused colors from current document's color set</source>
      <translation>Odstranit nepoužité barvy z aktuální množiny barev</translation>
    </message>
    <message>
      <source>Append colors to the current set from an existing document</source>
      <translation>Přidat barvy z již existujícího dokumentu</translation>
    </message>
    <message>
      <source>Create a new color within the current set</source>
      <translation>Vytvořit novou barvu v aktuální množině</translation>
    </message>
    <message>
      <source>Edit the currently selected color</source>
      <translation>Upravit zvolenou barvu</translation>
    </message>
    <message>
      <source>Make a copy of the currently selected color</source>
      <translation>Vytvořit kopii vybrané barvy</translation>
    </message>
    <message>
      <source>Delete the currently selected color</source>
      <translation>Smazat vybranou barvu</translation>
    </message>
    <message>
      <source>Make the current colorset the default color set</source>
      <translation>Nastavit aktuální množinu barev jako implicitní</translation>
    </message>
    <message>
      <source>&amp;Append</source>
      <translation>Připoji&amp;t</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
    <message>
      <source>D&amp;uplicate</source>
      <translation>&amp;Duplikovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Remove Unused</source>
      <translation>&amp;Odstranit nepoužité</translation>
    </message>
    <message>
      <source>&amp;Save Color Set</source>
      <translation>&amp;Uložit množinu barev</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Name:</source>
      <translation>&amp;Jméno:</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádná</translation>
    </message>
  </context>
  <context>
    <name>FontPrefs</name>
    <message>
      <source>Global Font Settings</source>
      <translation>Všeobecné nastavení písma</translation>
    </message>
    <message>
      <source>Available Fonts</source>
      <translation>Dostupná písma</translation>
    </message>
    <message>
      <source>Font Substitutions</source>
      <translation>Substituce písem</translation>
    </message>
    <message>
      <source>Additional Paths</source>
      <translation>Dodatečné cesty</translation>
    </message>
    <message>
      <source>Postscript</source>
      <translation>Postsript</translation>
    </message>
    <message>
      <source>Yes</source>
      <translation>Ano</translation>
    </message>
    <message>
      <source>Font Name</source>
      <translation>Název písma</translation>
    </message>
    <message>
      <source>Use Font</source>
      <translation>Použít písmo</translation>
    </message>
    <message>
      <source>Embed in:</source>
      <translation>Obsažen v:</translation>
    </message>
    <message>
      <source>Subset</source>
      <translation>Podmnožina glyphů</translation>
    </message>
    <message>
      <source>Type</source>
      <translation>Typ</translation>
    </message>
    <message>
      <source>Path to Font File</source>
      <translation>Cesta k souboru s písmem</translation>
    </message>
    <message>
      <source>Replacement</source>
      <translation>Náhrada</translation>
    </message>
    <message>
      <source>Choose a Directory</source>
      <translation>Vybrat adresář</translation>
    </message>
    <message>
      <source>&amp;Available Fonts</source>
      <translation>&amp;Dostupná písma</translation>
    </message>
    <message>
      <source>Font &amp;Substitutions</source>
      <translation>&amp;Substituce písem</translation>
    </message>
    <message>
      <source>Additional &amp;Paths</source>
      <translation>Dodatečné &amp;cesty</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>C&amp;hange...</source>
      <translation>&amp;Změnit...</translation>
    </message>
    <message>
      <source>A&amp;dd...</source>
      <translation>&amp;Připojit...</translation>
    </message>
    <message>
      <source>&amp;Remove</source>
      <translation>&amp;Odstranit</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>FontPreview</name>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>Alt+O</source>
      <translation>Alt+O</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Alt+C</source>
      <translation>Alt+Z</translation>
    </message>
    <message>
      <source>Woven silk pyjamas exchanged for blue quartz</source>
      <translation>Příliš žluťoučký kůň úpěl ďábelské Ódy</translation>
    </message>
    <message>
      <source>Fonts Preview</source>
      <translation>Náhled písem</translation>
    </message>
    <message>
      <source>Append selected font into Style, Font menu</source>
      <translation>Přidat zvolené písmo do Styl, Písmo menu</translation>
    </message>
    <message>
      <source>Leave preview</source>
      <translation>Zavřít náhled písem</translation>
    </message>
  </context>
  <context>
    <name>GradientEditor</name>
    <message>
      <source>Position:</source>
      <translation>Pozice:</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Here you can add, change or remove Color-Stops.</source>
      <translation>Zde můžete přidat, změnit nemo odstranit Požadované barvy (Stop-colors).</translation>
    </message>
  </context>
  <context>
    <name>GuideManager</name>
    <message>
      <source>Manage Guides</source>
      <translation>Ovládání vodítek</translation>
    </message>
    <message>
      <source>Horizontal Guides</source>
      <translation>Vodorovná vodítka</translation>
    </message>
    <message>
      <source>Vertical Guides</source>
      <translation>Svislá vodítka</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>&amp;Y-Pos:</source>
      <translation>&amp;Y-Poz:</translation>
    </message>
    <message>
      <source>&amp;Add</source>
      <translation>&amp;Připojit</translation>
    </message>
    <message>
      <source>D&amp;elete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;X-Pos:</source>
      <translation>&amp;X-Poz:</translation>
    </message>
    <message>
      <source>A&amp;dd</source>
      <translation>Přip&amp;ojit</translation>
    </message>
    <message>
      <source>De&amp;lete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Lock Guides</source>
      <translation>&amp;Zamknout vodítka</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>HelpBrowser</name>
    <message>
      <source>Sorry, no manual available! Please see: http://docs.scribus.net for updated docs
and www.scribus.net for downloads.</source>
      <translation>Lituji, ale není dostupný žádný manuál! Navštivte prosím: http://docs.scribus.net
kde naleznete aktuální dokumentaci.</translation>
    </message>
    <message>
      <source>Contents</source>
      <translation>Obsah</translation>
    </message>
    <message>
      <source>Link</source>
      <translation>Odkaz</translation>
    </message>
    <message>
      <source>Scribus Online Help</source>
      <translation>Scribus nápověda</translation>
    </message>
  </context>
  <context>
    <name>HyAsk</name>
    <message>
      <source>Possible Hyphenation</source>
      <translation>Přijatelné dělení slov</translation>
    </message>
    <message>
      <source>Accept</source>
      <translation>Akceptovat</translation>
    </message>
    <message>
      <source>Skip</source>
      <translation>Přeskočit</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
  </context>
  <context>
    <name>HySettings</name>
    <message>
      <source>Hyphenator Settings</source>
      <translation>Nastavení dělení slov</translation>
    </message>
    <message>
      <source>Length of the smallest word to be hyphenated.</source>
      <translation>Délka nejkratšího slova, které může být děleno.</translation>
    </message>
    <message>
      <source>Maximum number of Hyphenations following each other.
A value of 0 means unlimited hyphenations.</source>
      <translation>Maximální počet po sobě následujících dělení slov.
Nula (0) funkci vypíná. Pozn. překl.: V české typografii max. 3.</translation>
    </message>
    <message>
      <source>&amp;Language:</source>
      <translation>&amp;Jazyk:</translation>
    </message>
    <message>
      <source>&amp;Smallest Word:</source>
      <translation>&amp;Nejmenší slovo:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Hyphenation Suggestions</source>
      <translation>Návrhy &amp;dělění</translation>
    </message>
    <message>
      <source>Hyphenate Text Automatically &amp;During Typing</source>
      <translation>&amp;Automaticky dělit slova při psaní</translation>
    </message>
    <message>
      <source>A dialog box showing all possible hyphens for each word will show up when you use the Extras, Hyphenate Text option.</source>
      <translation>Po volbě &quot;Extra&quot;, &quot;Dělení slov v textu&quot; se objeví dialog,
ve kterém budou zobrazeny všechny možnosti dělení slova.</translation>
    </message>
    <message>
      <source>Enables automatic hyphenation of your text while typing.</source>
      <translation>Povolí automatické dělení slov během psaní textu.</translation>
    </message>
    <message>
      <source>Consecutive Hyphenations &amp;Allowed:</source>
      <translation>&amp;Maximální počet po sobě následujících dělění:</translation>
    </message>
  </context>
  <context>
    <name>InsPage</name>
    <message>
      <source>Insert Page</source>
      <translation>Vložit stranu</translation>
    </message>
    <message>
      <source>Inserting</source>
      <translation>Vkládání</translation>
    </message>
    <message>
      <source>before Page</source>
      <translation>před stranu</translation>
    </message>
    <message>
      <source>after Page</source>
      <translation>za stranu</translation>
    </message>
    <message>
      <source>at End</source>
      <translation>na konec</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Template (Right Page):</source>
      <translation>Šablona (pravá strana):</translation>
    </message>
    <message>
      <source>&amp;Inserting</source>
      <translation>&amp;Vkládání</translation>
    </message>
    <message>
      <source>Page(s)</source>
      <translation>Strana(y)</translation>
    </message>
    <message>
      <source>&amp;Template (Left Page):</source>
      <translation>Šab&amp;lona (levá strana):</translation>
    </message>
    <message>
      <source>&amp;Template:</source>
      <translation>Ša&amp;blona:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>InsertTable</name>
    <message>
      <source>Insert Table</source>
      <translation>Vložit tabulku</translation>
    </message>
    <message>
      <source>Number of Rows:</source>
      <translation>Počet řádků:</translation>
    </message>
    <message>
      <source>Number of Columns:</source>
      <translation>Počet sloupců:</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
  </context>
  <context>
    <name>JavaDocs</name>
    <message>
      <source>New Script</source>
      <translation>Nový skript</translation>
    </message>
    <message>
      <source>Edit JavaScripts</source>
      <translation>Editace Java skriptů</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>&amp;Edit...</source>
      <translation>&amp;Upravit...</translation>
    </message>
    <message>
      <source>&amp;Add...</source>
      <translation>&amp;Přidat...</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>&amp;New Script:</source>
      <translation>&amp;Nový skript:</translation>
    </message>
    <message>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <source>&amp;Yes</source>
      <translation>&amp;Ano</translation>
    </message>
    <message>
      <source>Do you really want to delete this Script?</source>
      <translation>Opravdu chcete smazat tento skript?</translation>
    </message>
  </context>
  <context>
    <name>KeyManager</name>
    <message>
      <source>Manage Keyboard Shortcuts</source>
      <translation>Správa klávesových zkratek</translation>
    </message>
    <message>
      <source>Action</source>
      <translation>Akce</translation>
    </message>
    <message>
      <source>Current Key</source>
      <translation>Aktuální klávesa</translation>
    </message>
    <message>
      <source>Select a Key for this Action</source>
      <translation>Zvolte klávesu pro tuto akci</translation>
    </message>
    <message>
      <source>ALT+SHIFT+T</source>
      <translation>ALT+SHIFT+T</translation>
    </message>
    <message>
      <source>Alt</source>
      <translation>Alt</translation>
    </message>
    <message>
      <source>Ctrl</source>
      <translation>Ctrl</translation>
    </message>
    <message>
      <source>Shift</source>
      <translation>Shift</translation>
    </message>
    <message>
      <source>Shift+</source>
      <translation>Shift+</translation>
    </message>
    <message>
      <source>Alt+</source>
      <translation>Alt+</translation>
    </message>
    <message>
      <source>Ctrl+</source>
      <translation>ctrl+</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>&amp;No Key</source>
      <translation>Žádná &amp;klávesa</translation>
    </message>
    <message>
      <source>&amp;User Defined Key</source>
      <translation>Definováno &amp;uživatelem</translation>
    </message>
    <message>
      <source>Set &amp;Key</source>
      <translation>&amp;Nastavit klávesu</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>This Key Sequence is already in use</source>
      <translation>Tato sekvence kláves je už používána</translation>
    </message>
  </context>
  <context>
    <name>LayerPalette</name>
    <message>
      <source>Layers</source>
      <translation>Vrstvy</translation>
    </message>
    <message>
      <source>Add a new Layer</source>
      <translation>Přidat novou vrstvu</translation>
    </message>
    <message>
      <source>Delete Layer</source>
      <translation>Smazat vrstvu</translation>
    </message>
    <message>
      <source>Raise Layer</source>
      <translation>Vrstvu dopředu</translation>
    </message>
    <message>
      <source>Lower Layer</source>
      <translation>Vrstvu dozadu</translation>
    </message>
    <message>
      <source>New Layer</source>
      <translation>Nová vrstva</translation>
    </message>
    <message>
      <source>Do you want to delete all Objects on this Layer too?</source>
      <translation>Opravdu chcete také smazat všechny objekty z této hladiny?</translation>
    </message>
  </context>
  <context>
    <name>LineFormate</name>
    <message>
      <source>Edit Line Styles</source>
      <translation>Editace stylů čar</translation>
    </message>
    <message>
      <source>Copy of %1</source>
      <translation>Kopie %1</translation>
    </message>
    <message>
      <source>New Style</source>
      <translation>Nový styl</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Documents (*.sla *.scd);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>&amp;Append</source>
      <translation>Připoji&amp;t</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
    <message>
      <source>D&amp;uplicate</source>
      <translation>&amp;Duplikovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <source>&amp;Yes</source>
      <translation>&amp;Ano</translation>
    </message>
    <message>
      <source>Do you really want to delete this Style?</source>
      <translation>Opravdu chcete smazat tento styl?</translation>
    </message>
  </context>
  <context>
    <name>MSpinBox</name>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source>in</source>
      <translation>in</translation>
    </message>
    <message>
      <source>p</source>
      <translation>p</translation>
    </message>
  </context>
  <context>
    <name>Mdup</name>
    <message>
      <source>Multiple Duplicate</source>
      <translation>Vícenásobné duplikování</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>&amp;Number of Copies:</source>
      <translation>&amp;Počet kopií:</translation>
    </message>
    <message>
      <source>&amp;Horizontal Shift:</source>
      <translation>&amp;Vodorovné posunutí:</translation>
    </message>
    <message>
      <source>&amp;Vertical Shift:</source>
      <translation>&amp;Svislé posunutí:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>Measurements</name>
    <message>
      <source>Distances</source>
      <translation>Vzdálenosti</translation>
    </message>
    <message>
      <source>X1:</source>
      <translation>X1:</translation>
    </message>
    <message>
      <source>Y1:</source>
      <translation>Y1:</translation>
    </message>
    <message>
      <source>X2:</source>
      <translation>X2:</translation>
    </message>
    <message>
      <source>Y2:</source>
      <translation>Y2:</translation>
    </message>
    <message>
      <source>DX:</source>
      <translation>DX:</translation>
    </message>
    <message>
      <source>DY:</source>
      <translation>DY:</translation>
    </message>
    <message>
      <source>Angle:</source>
      <translation>Úhel:</translation>
    </message>
    <message>
      <source>Length:</source>
      <translation>Délka:</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
  </context>
  <context>
    <name>MenuTest</name>
    <message>
      <source>Script error</source>
      <translation>Chyba ve skriptu</translation>
    </message>
    <message>
      <source>If you are running an official script report it at &lt;a href=&quot;http://bugs.scribus.net&quot;>bugs.scribus.net&lt;/a> please.</source>
      <translation>Jestliže běžel skript distribuovaný s programem, informujte nás o chybě na &lt;a href=&quot;http://bugs.scribus.net&quot;>bugs.scribus.net&lt;/a> - děkujeme vám.</translation>
    </message>
    <message>
      <source>Show &amp;Console</source>
      <translation>Ukázat &amp;konzoli</translation>
    </message>
    <message>
      <source>Hide &amp;Console</source>
      <translation>Skrýt &amp;konzoli</translation>
    </message>
    <message>
      <source>This message is in your clipboard too. Use Ctrl+V to paste it into bug tracker.</source>
      <translation>Tato chybová zpráva je ve vaší systémové schránce. Použijte Ctrl+V, tím ji
můžete zkopírovat do chybového hlášení.</translation>
    </message>
  </context>
  <context>
    <name>MergeDoc</name>
    <message>
      <source>Change...</source>
      <translation>Změnit...</translation>
    </message>
    <message>
      <source>Import</source>
      <translation>Import</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Documents (*.sla *.scd);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Import Template</source>
      <translation>Importovat šablonu</translation>
    </message>
    <message>
      <source>Import Page(s)</source>
      <translation>Importovat stranu(y)</translation>
    </message>
    <message>
      <source>From Document:</source>
      <translation>Z dokumenu:</translation>
    </message>
    <message>
      <source>Import Page(s):</source>
      <translation>Importovat stranu(y):</translation>
    </message>
    <message>
      <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
      <translation>Vložte čárkou oddělený seznam položek, kde
položka může být *, t.j. všechny strany, 1-5,
t.j. interval, nebo jediné číslo strany.</translation>
    </message>
    <message>
      <source> from 0</source>
      <translation>od 0</translation>
    </message>
    <message>
      <source>Create Page(s)</source>
      <translation>Vytvořit stranu(y)</translation>
    </message>
    <message>
      <source>before Page</source>
      <translation>před stranu</translation>
    </message>
    <message>
      <source>after Page</source>
      <translation>za stranu</translation>
    </message>
    <message>
      <source>at End</source>
      <translation>na konec</translation>
    </message>
    <message>
      <source> from %1</source>
      <translation>od %1</translation>
    </message>
  </context>
  <context>
    <name>MovePages</name>
    <message>
      <source>Move Pages</source>
      <translation>Přesunout strany</translation>
    </message>
    <message>
      <source>Copy Page</source>
      <translation>Kopírovat stranu</translation>
    </message>
    <message>
      <source>Move Page(s):</source>
      <translation>Posun stran:</translation>
    </message>
    <message>
      <source>to:</source>
      <translation>po:</translation>
    </message>
    <message>
      <source>before Page</source>
      <translation>před stranu</translation>
    </message>
    <message>
      <source>after Page</source>
      <translation>za stranu</translation>
    </message>
    <message>
      <source>at End</source>
      <translation>na konec</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>Mpalette</name>
    <message>
      <source>Properties</source>
      <translation>Vlastnosti</translation>
    </message>
    <message>
      <source>Name</source>
      <translation>Jméno</translation>
    </message>
    <message>
      <source>Geometry</source>
      <translation>Geometrie</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Basepoint:</source>
      <translation>Střed otáčení:</translation>
    </message>
    <message>
      <source>Level</source>
      <translation>Hladina</translation>
    </message>
    <message>
      <source>Shape:</source>
      <translation>Obrys:</translation>
    </message>
    <message>
      <source>Distance of Text</source>
      <translation>Vzdálenost textu</translation>
    </message>
    <message>
      <source>Show Curve</source>
      <translation>Zobrazit křivku</translation>
    </message>
    <message>
      <source>Start Offset:</source>
      <translation>Počáteční posun:</translation>
    </message>
    <message>
      <source>Distance from Curve:</source>
      <translation>Vzdálenost od křivky:</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Custom Spacing</source>
      <translation>Vlastní proklad</translation>
    </message>
    <message>
      <source>Input Profile:</source>
      <translation>Vložit profil:</translation>
    </message>
    <message>
      <source>Rendering Intent:</source>
      <translation>Účel reprodukce:</translation>
    </message>
    <message>
      <source>Perceptual</source>
      <translation>Perceptuální (fotografická) transformace</translation>
    </message>
    <message>
      <source>Relative Colorimetric</source>
      <translation>Relativní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Saturation</source>
      <translation>Sytost</translation>
    </message>
    <message>
      <source>Absolute Colorimetric</source>
      <translation>Absolutní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Left Point</source>
      <translation>Levý bod</translation>
    </message>
    <message>
      <source>End Points</source>
      <translation>Koncové body</translation>
    </message>
    <message>
      <source>Miter Join</source>
      <translation>Kolmý spoj</translation>
    </message>
    <message>
      <source>Bevel Join</source>
      <translation>Zkosený spoj</translation>
    </message>
    <message>
      <source>Round Join</source>
      <translation>Oblý spoj</translation>
    </message>
    <message>
      <source>Flat Cap</source>
      <translation>Ostrá hlavička</translation>
    </message>
    <message>
      <source>Square Cap</source>
      <translation>Čtvercová hlavička</translation>
    </message>
    <message>
      <source>Round Cap</source>
      <translation>Oblá hlavička</translation>
    </message>
    <message>
      <source>No Style</source>
      <translation>Bez stylu</translation>
    </message>
    <message>
      <source>Font Size</source>
      <translation>Velikost písma</translation>
    </message>
    <message>
      <source>Line Spacing</source>
      <translation>Řádkování</translation>
    </message>
    <message>
      <source>Manual Kerning</source>
      <translation>Ruční vyrovnání znaků (Kerning)</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name &quot;%1&quot; isn't unique.
Please choose another.</source>
      <translation>Název &quot;%1&quot; není jedinečný.
Vyberte, prosím, jiný.</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Shade:</source>
      <translation>Stín:</translation>
    </message>
    <message>
      <source>Name of selected object</source>
      <translation>Jméno vybraného objektu</translation>
    </message>
    <message>
      <source>Horizontal position of current basepoint</source>
      <translation>Horizontální umístění středu otáčení</translation>
    </message>
    <message>
      <source>Vertical position of current basepoint</source>
      <translation>Vertikální umístění středu otáčení</translation>
    </message>
    <message>
      <source>Width</source>
      <translation>Šířka</translation>
    </message>
    <message>
      <source>Height</source>
      <translation>Výška</translation>
    </message>
    <message>
      <source>Rotation of object at current basepoint</source>
      <translation>Rotace objektu podle aktuálního středu otáčení</translation>
    </message>
    <message>
      <source>Point from which measurements or rotation angles are referenced</source>
      <translation>Bod (počátek souřadnic), od kterého jsou 
odvozeny vzdálenosti nebo úhly rotace</translation>
    </message>
    <message>
      <source>Select top left for basepoint</source>
      <translation>Střed otáčení vlevo nahoře</translation>
    </message>
    <message>
      <source>Select top right for basepoint</source>
      <translation>Střed otáčení vpravo nahoře</translation>
    </message>
    <message>
      <source>Select bottom left for basepoint</source>
      <translation>Střed otáčení vlevo dole</translation>
    </message>
    <message>
      <source>Select bottom right for basepoint</source>
      <translation>Střed otáčení vpravo dole</translation>
    </message>
    <message>
      <source>Select center for basepoint</source>
      <translation>Střed otáčení uprostřed</translation>
    </message>
    <message>
      <source>Flip Horizontal</source>
      <translation>Překlopit vodorovně</translation>
    </message>
    <message>
      <source>Flip Vertical</source>
      <translation>Překlopit svisle</translation>
    </message>
    <message>
      <source>Move one level up</source>
      <translation>O hladinu výš</translation>
    </message>
    <message>
      <source>Move one level down</source>
      <translation>O hladinu níž</translation>
    </message>
    <message>
      <source>Move to front</source>
      <translation>Přesunout navrch</translation>
    </message>
    <message>
      <source>Move to back</source>
      <translation>Přesunout dospodu</translation>
    </message>
    <message>
      <source>Lock or unlock the object</source>
      <translation>Zamknout nebo odemknout objekt</translation>
    </message>
    <message>
      <source>Lock or unlock the size of the object</source>
      <translation>Zamknout nebo odemknout rozměry objektu</translation>
    </message>
    <message>
      <source>Enable or disable printing of the object</source>
      <translation>Povolit nebo zakázat tisk objektu</translation>
    </message>
    <message>
      <source>Font of selected text or object</source>
      <translation>Písmo vybraného textu nebo objektu</translation>
    </message>
    <message>
      <source>Scaling width of characters</source>
      <translation>Změna šířky znaků písma</translation>
    </message>
    <message>
      <source>Color of text stroke</source>
      <translation>Barva obrysu písma</translation>
    </message>
    <message>
      <source>Color of text fill</source>
      <translation>Barva výplně písma</translation>
    </message>
    <message>
      <source>Saturation of color of text stroke</source>
      <translation>Sytost barvy obrysu písma</translation>
    </message>
    <message>
      <source>Saturation of color of text fill</source>
      <translation>Sytost barvy výplně písma</translation>
    </message>
    <message>
      <source>Style of current paragraph</source>
      <translation>Styl aktuálního odstavce</translation>
    </message>
    <message>
      <source>Change settings for left or end points</source>
      <translation>Změna nastavení bodů čáry</translation>
    </message>
    <message>
      <source>Pattern of line</source>
      <translation>Styl čáry</translation>
    </message>
    <message>
      <source>Thickness of line</source>
      <translation>Šířka (tloušťka) čáry</translation>
    </message>
    <message>
      <source>Type of line joins</source>
      <translation>Typy spojení čar</translation>
    </message>
    <message>
      <source>Type of line end</source>
      <translation>Typy ukončení čáry</translation>
    </message>
    <message>
      <source>Line style of current object</source>
      <translation>Styl čáry aktuálního objektu</translation>
    </message>
    <message>
      <source>Choose the shape of frame...</source>
      <translation>Výběr obrys rámu...</translation>
    </message>
    <message>
      <source>Edit shape of the frame...</source>
      <translation>Úprava obrysu rámu...</translation>
    </message>
    <message>
      <source>Set radius of corner rounding</source>
      <translation>Nastavní poloměru zakulacení rohů</translation>
    </message>
    <message>
      <source>Number of columns in text frame</source>
      <translation>Počet sloupců v textovém rámu</translation>
    </message>
    <message>
      <source>Distance between columns</source>
      <translation>Vzdálenost mezi sloupci</translation>
    </message>
    <message>
      <source>Distance of text from top of frame</source>
      <translation>Vzdálenost textu od horního obrysu rámu</translation>
    </message>
    <message>
      <source>Distance of text from bottom of frame</source>
      <translation>Vzdálenost textu od spodního obrysu rámu</translation>
    </message>
    <message>
      <source>Distance of text from left of frame</source>
      <translation>Vzdálenost textu od levého obrysu rámu</translation>
    </message>
    <message>
      <source>Distance of text from right of frame</source>
      <translation>Vzdálenost textu od pravého obrysu rámu</translation>
    </message>
    <message>
      <source>Edit tab settings of text frame...</source>
      <translation>Nastavení tabelátorů textového rámu...</translation>
    </message>
    <message>
      <source>Allow the image to be a different size to the frame</source>
      <translation>Možnost nastavit jiné rozměry obrázku než rámce</translation>
    </message>
    <message>
      <source>Horizontal offset of image within frame</source>
      <translation>Vodorovné posunutí obrázku vůči rámu</translation>
    </message>
    <message>
      <source>Vertical offset of image within frame</source>
      <translation>Svislé posunutí obrázku vůči rámu</translation>
    </message>
    <message>
      <source>Resize the image horizontally</source>
      <translation>Změnit šířku obrázku</translation>
    </message>
    <message>
      <source>Resize the image vertically</source>
      <translation>Změnit výšku obrázku</translation>
    </message>
    <message>
      <source>Keep the X and Y scaling the same</source>
      <translation>Použít stejnou změnu velikosti pro oba rozměry (X a Y)</translation>
    </message>
    <message>
      <source>Make the image fit within the size of the frame</source>
      <translation>Obrázek změní velikost podle rozměru rámu</translation>
    </message>
    <message>
      <source>Use image proportions rather than those of the frame</source>
      <translation>Obrázek si zachová své proporce</translation>
    </message>
    <message>
      <source>Cell Lines</source>
      <translation>Čáry buňky tabulky</translation>
    </message>
    <message>
      <source>Line at Top</source>
      <translation>Horní čára</translation>
    </message>
    <message>
      <source>Line at the Left</source>
      <translation>Levá čára</translation>
    </message>
    <message>
      <source>Line at the Right </source>
      <translation>Pravá čára</translation>
    </message>
    <message>
      <source>Line at Bottom</source>
      <translation>Dolní čára</translation>
    </message>
    <message>
      <source>Keep the aspect ratio</source>
      <translation>Dodržet poměr stran</translation>
    </message>
    <message>
      <source>Source profile of the image</source>
      <translation>Zdrojový profil obrázku</translation>
    </message>
    <message>
      <source>Rendering intent for the image</source>
      <translation>Účel reprodukce obrázku</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>Path Text Properties</source>
      <translation>Vlastnosti textu na křivky</translation>
    </message>
    <message>
      <source>Indicates the level the object is on, 0 means the object is at the bottom</source>
      <translation>Ukazuje hladinu zvoleného objektu. 0 znamená, že je objekt nejníž</translation>
    </message>
    <message>
      <source>Make text in lower frames flow around the object shape</source>
      <translation>Povolit obtékání textu v nižších objektech kolem zvoleného obrysu</translation>
    </message>
    <message>
      <source>Switches between Gap or Column width</source>
      <translation>Přepínat mezi mezisloupcovou mezerou a šířkou sloupce</translation>
    </message>
    <message>
      <source>Column width</source>
      <translation>Šířka sloupce</translation>
    </message>
    <message>
      <source>X, Y, &amp;Z</source>
      <translation>X, Y, &amp;Z</translation>
    </message>
    <message>
      <source>&amp;Shape</source>
      <translation>&amp;Tvar</translation>
    </message>
    <message>
      <source>&amp;Text</source>
      <translation>&amp;Text</translation>
    </message>
    <message>
      <source>&amp;Image</source>
      <translation>&amp;Obrázek</translation>
    </message>
    <message>
      <source>&amp;Line</source>
      <translation>Čá&amp;ra</translation>
    </message>
    <message>
      <source>&amp;Colors</source>
      <translation>&amp;Barvy</translation>
    </message>
    <message>
      <source>&amp;X-Pos:</source>
      <translation>&amp;X-Poz:</translation>
    </message>
    <message>
      <source>&amp;Y-Pos:</source>
      <translation>&amp;Y-Poz:</translation>
    </message>
    <message>
      <source>&amp;Width:</source>
      <translation>Šíř&amp;ka:</translation>
    </message>
    <message>
      <source>&amp;Height:</source>
      <translation>&amp;Výška:</translation>
    </message>
    <message>
      <source>&amp;Rotation:</source>
      <translation>&amp;Rotace:</translation>
    </message>
    <message>
      <source>&amp;Edit Shape...</source>
      <translation>Upravit &amp;obrys...</translation>
    </message>
    <message>
      <source>R&amp;ound
Corners:</source>
      <translation>Zakolatit
&amp;rohy:</translation>
    </message>
    <message>
      <source>Colu&amp;mns:</source>
      <translation>S&amp;loupce:</translation>
    </message>
    <message>
      <source>&amp;Gap:</source>
      <translation>&amp;Odstup:</translation>
    </message>
    <message>
      <source>To&amp;p:</source>
      <translation>&amp;Horní:</translation>
    </message>
    <message>
      <source>&amp;Bottom:</source>
      <translation>&amp;Dolní:</translation>
    </message>
    <message>
      <source>&amp;Left:</source>
      <translation>&amp;Levý:</translation>
    </message>
    <message>
      <source>&amp;Right:</source>
      <translation>&amp;Pravý:</translation>
    </message>
    <message>
      <source>T&amp;abulators...</source>
      <translation>&amp;Tabelátory...</translation>
    </message>
    <message>
      <source>Text &amp;Flows Around Frame</source>
      <translation>Te&amp;xt obtéká okolo rámu</translation>
    </message>
    <message>
      <source>Use &amp;Bounding Box</source>
      <translation>Použít &amp;celostránkový rámec</translation>
    </message>
    <message>
      <source>&amp;Use Contour Line</source>
      <translation>Použít &amp;konturu</translation>
    </message>
    <message>
      <source>&amp;Font Size:</source>
      <translation>&amp;Velikost písma:</translation>
    </message>
    <message>
      <source>&amp;Kerning:</source>
      <translation>Vyrovnání zna&amp;ků (kerning):</translation>
    </message>
    <message>
      <source>L&amp;ine Spacing:</source>
      <translation>Řád&amp;kování:</translation>
    </message>
    <message>
      <source>St&amp;yle:</source>
      <translation>St&amp;yl:</translation>
    </message>
    <message>
      <source>Lan&amp;guage:</source>
      <translation>&amp;Jazyk:</translation>
    </message>
    <message>
      <source>&amp;Free Scaling</source>
      <translation>Vo&amp;lná změna velikosti</translation>
    </message>
    <message>
      <source>X-Sc&amp;ale:</source>
      <translation>X-Měří&amp;tko:</translation>
    </message>
    <message>
      <source>Y-Scal&amp;e:</source>
      <translation>Y-Měřít&amp;ko:</translation>
    </message>
    <message>
      <source>Scale &amp;To Frame Size</source>
      <translation>Změni&amp;t velikost na rozměr rámu</translation>
    </message>
    <message>
      <source>P&amp;roportional</source>
      <translation>&amp;Proporcionálně</translation>
    </message>
    <message>
      <source>&amp;Basepoint:</source>
      <translation>&amp;Střed otáčení:</translation>
    </message>
    <message>
      <source>T&amp;ype of Line:</source>
      <translation>&amp;Typ čáry:</translation>
    </message>
    <message>
      <source>Line &amp;Width:</source>
      <translation>Šíř&amp;ka čáry:</translation>
    </message>
    <message>
      <source>Ed&amp;ges:</source>
      <translation>&amp;Hrany:</translation>
    </message>
    <message>
      <source>&amp;Endings:</source>
      <translation>&amp;Ukončení:</translation>
    </message>
    <message>
      <source>&amp;X1:</source>
      <translation>&amp;X1:</translation>
    </message>
    <message>
      <source>X&amp;2:</source>
      <translation>X&amp;2:</translation>
    </message>
    <message>
      <source>Y&amp;1:</source>
      <translation>Y&amp;1:</translation>
    </message>
    <message>
      <source>&amp;Y2:</source>
      <translation>&amp;Y2:</translation>
    </message>
    <message>
      <source>Use a surrounding box instead of the frame's shape for text flow</source>
      <translation>Použít obrys celého rámu místo obysu objektu</translation>
    </message>
    <message>
      <source>Use a second line originally based on the frame's shape for text flow</source>
      <translation>Použít druhou čáru, založenou na obrysu rámu, při řetězení textu</translation>
    </message>
    <message>
      <source>Hyphenation language of frame</source>
      <translation>Jazyk dělení slov</translation>
    </message>
    <message>
      <source>Right to Left Writing</source>
      <translation>Psaní zprava doleva</translation>
    </message>
  </context>
  <context>
    <name>MultiLine</name>
    <message>
      <source>Edit Style</source>
      <translation>Upravit styl</translation>
    </message>
    <message>
      <source>Flat Cap</source>
      <translation>Ostrá hlavička</translation>
    </message>
    <message>
      <source>Square Cap</source>
      <translation>Čtvercová hlavička</translation>
    </message>
    <message>
      <source>Round Cap</source>
      <translation>Oblá hlavička</translation>
    </message>
    <message>
      <source>Miter Join</source>
      <translation>Kolmý spoj</translation>
    </message>
    <message>
      <source>Bevel Join</source>
      <translation>Zkosený spoj</translation>
    </message>
    <message>
      <source>Round Join</source>
      <translation>Oblý spoj</translation>
    </message>
    <message>
      <source>Line Width:</source>
      <translation>Šířka čáry:</translation>
    </message>
    <message>
      <source> pt</source>
      <translation> pt</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source> pt </source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Solid Line</source>
      <translation>Plná čára</translation>
    </message>
    <message>
      <source>Dashed Line</source>
      <translation>Čárkovaná čára</translation>
    </message>
    <message>
      <source>Dotted Line</source>
      <translation>Tečkovaná čára</translation>
    </message>
    <message>
      <source>Dash Dot Line</source>
      <translation>Čerchovaná čára</translation>
    </message>
    <message>
      <source>Dash Dot Dot Line</source>
      <translation>Dvojitě čerchovaná čára</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name &quot;%1&quot; isn't unique.
Please choose another.</source>
      <translation>Název &quot;%1&quot; není jedinečný.
Vyberte, prosím, jiný.</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>MusterSeiten</name>
    <message>
      <source>Edit Templates</source>
      <translation>Upravit šablony</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Copy of %1</source>
      <translation>Kopie %1</translation>
    </message>
    <message>
      <source>New Template</source>
      <translation>Nová šablona</translation>
    </message>
    <message>
      <source>Copy #%1 of </source>
      <translation>Kopie č. %1 z</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Name:</source>
      <translation>Název:</translation>
    </message>
    <message>
      <source>&amp;Append</source>
      <translation>Připoji&amp;t</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>D&amp;uplicate</source>
      <translation>&amp;Duplikovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <source>&amp;Yes</source>
      <translation>&amp;Ano</translation>
    </message>
    <message>
      <source>&amp;Name:</source>
      <translation>&amp;Jméno:</translation>
    </message>
    <message>
      <source>Do you really want to delete this Template?</source>
      <translation>Opravdu chcete smazat tuto šablonu?</translation>
    </message>
  </context>
  <context>
    <name>NewDoc</name>
    <message>
      <source>New Document</source>
      <translation>Nový dokument</translation>
    </message>
    <message>
      <source>Page Size</source>
      <translation>Velikost strany</translation>
    </message>
    <message>
      <source>Custom</source>
      <translation>Vlastní</translation>
    </message>
    <message>
      <source>Portrait</source>
      <translation>Na výšku</translation>
    </message>
    <message>
      <source>Landscape</source>
      <translation>Na šířku</translation>
    </message>
    <message>
      <source>Margin Guides</source>
      <translation>Vodítka okrajů</translation>
    </message>
    <message>
      <source>Options</source>
      <translation>Možnosti</translation>
    </message>
    <message>
      <source>Points (pts)</source>
      <translation>Body (pts)</translation>
    </message>
    <message>
      <source>Inches (in)</source>
      <translation>Palce (in)</translation>
    </message>
    <message>
      <source>Picas (p)</source>
      <translation>Pika (p)</translation>
    </message>
    <message>
      <source>Column Guides</source>
      <translation>Vodítka sloupců</translation>
    </message>
    <message>
      <source>Millimetres (mm)</source>
      <translation>Milimetry (mm)</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>Document page size, either a standard size or a custom size</source>
      <translation>Velikost strany dokumentu - buď standardní nebo volitelný rozměr</translation>
    </message>
    <message>
      <source>Orientation of the document's pages</source>
      <translation>Orientace stran dokumentu</translation>
    </message>
    <message>
      <source>Width of the document's pages, editable if you have chosen a custom page size</source>
      <translation>Šířka stran dokumentu - upravitelná, jestliže je vybrán volitelný rozměr</translation>
    </message>
    <message>
      <source>Height of the document's pages, editable if you have chosen a custom page size</source>
      <translation>Výška stran dokumentu - upravitelná, jestliže je vybrán volitelný rozměr</translation>
    </message>
    <message>
      <source>Enable single or spread based layout</source>
      <translation>Povolit rozložení po jedné nebo po více stranách</translation>
    </message>
    <message>
      <source>Make the first page the left page of the document</source>
      <translation>První strana je levou stranou dokumentu</translation>
    </message>
    <message>
      <source>Distance between the top margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi horním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the bottom margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi dolním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the left margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi levým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source>Distance between the right margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi pravým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source>First page number of the document</source>
      <translation>Číslo první strany dokumentu</translation>
    </message>
    <message>
      <source>Default unit of measurement for document editing</source>
      <translation>Implicitní měrná jednotka dokumentu</translation>
    </message>
    <message>
      <source>Create text frames automatically when new pages are added</source>
      <translation>Vytvářet automaticky textové rámce, jsou-li přidány nové strany</translation>
    </message>
    <message>
      <source>Number of columns to create in automatically created text frames</source>
      <translation>Počet sloupců v automaticky vytvořených textových rámcích</translation>
    </message>
    <message>
      <source>Distance between automatically created columns</source>
      <translation>Vzdálenost mezi automaticky vytvořenými textovými rámci</translation>
    </message>
    <message>
      <source>Legal</source>
      <translation>Legal</translation>
    </message>
    <message>
      <source>Letter</source>
      <translation>Letter</translation>
    </message>
    <message>
      <source>Tabloid</source>
      <translation>Tabloid</translation>
    </message>
    <message>
      <source>&amp;Size:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <source>Orie&amp;ntation:</source>
      <translation>&amp;Orientace:</translation>
    </message>
    <message>
      <source>&amp;Width:</source>
      <translation>Šíř&amp;ka:</translation>
    </message>
    <message>
      <source>&amp;Height:</source>
      <translation>&amp;Výška:</translation>
    </message>
    <message>
      <source>&amp;Facing Pages</source>
      <translation>P&amp;rotilehlé stránky (Dvoustrany)</translation>
    </message>
    <message>
      <source>Left &amp;Page First</source>
      <translation>Prv&amp;ní strana vlevo</translation>
    </message>
    <message>
      <source>&amp;Left:</source>
      <translation>&amp;Levý:</translation>
    </message>
    <message>
      <source>&amp;Right:</source>
      <translation>&amp;Pravý:</translation>
    </message>
    <message>
      <source>&amp;Top:</source>
      <translation>&amp;Horní:</translation>
    </message>
    <message>
      <source>&amp;Bottom:</source>
      <translation>&amp;Dolní:</translation>
    </message>
    <message>
      <source>F&amp;irst Page Number:</source>
      <translation>Čí&amp;slo první strany:</translation>
    </message>
    <message>
      <source>&amp;Default Unit:</source>
      <translation>&amp;Implicitní jednotka:</translation>
    </message>
    <message>
      <source>&amp;Automatic Text Frames</source>
      <translation>&amp;Automatické  textové rámce</translation>
    </message>
    <message>
      <source>&amp;Gap:</source>
      <translation>&amp;Odstup:</translation>
    </message>
    <message>
      <source>Colu&amp;mns:</source>
      <translation>S&amp;loupce:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Inside:</source>
      <translation>&amp;Uvnitř:</translation>
    </message>
    <message>
      <source>O&amp;utside:</source>
      <translation>&amp;Vnější:</translation>
    </message>
    <message>
      <source>Executive</source>
      <translation>Executive</translation>
    </message>
    <message>
      <source>Folio</source>
      <translation>Folio</translation>
    </message>
    <message>
      <source>Ledger</source>
      <translation>Ledger</translation>
    </message>
  </context>
  <context>
    <name>NewTm</name>
    <message>
      <source>Left Page</source>
      <translation>Levá strana</translation>
    </message>
    <message>
      <source>Right Page</source>
      <translation>Pravá strana</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>NodePalette</name>
    <message>
      <source>Nodes</source>
      <translation>Uzly</translation>
    </message>
    <message>
      <source>Move Nodes</source>
      <translation>Přesunout uzly</translation>
    </message>
    <message>
      <source>Move Control Points</source>
      <translation>Přesunout řídící body</translation>
    </message>
    <message>
      <source>Add Nodes</source>
      <translation>Přidat uzly</translation>
    </message>
    <message>
      <source>Delete Nodes</source>
      <translation>Smazat uzly</translation>
    </message>
    <message>
      <source>Reset Control Points</source>
      <translation>Vynulovat řídící body</translation>
    </message>
    <message>
      <source>Reset this Control Point</source>
      <translation>Vynulovat tento řídící bod</translation>
    </message>
    <message>
      <source>When checked use Coordinates relative to the Page,
otherwise Coordinates are relative to the Object.</source>
      <translation>Je-li zatrženo, jsou souřadnice relativní vzhledem
ke straně, v opačném případě k objektu.</translation>
    </message>
    <message>
      <source>&amp;Absolute Coordinates</source>
      <translation>&amp;Absolutní souřadnice</translation>
    </message>
    <message>
      <source>&amp;X-Pos:</source>
      <translation>&amp;X-Poz:</translation>
    </message>
    <message>
      <source>&amp;Y-Pos:</source>
      <translation>&amp;Y-Poz:</translation>
    </message>
    <message>
      <source>Edit &amp;Contour Line</source>
      <translation>Upravit &amp;konturu</translation>
    </message>
    <message>
      <source>&amp;Reset Contour Line</source>
      <translation>Vy&amp;nulovat konturu</translation>
    </message>
    <message>
      <source>&amp;End Editing</source>
      <translation>&amp;Konec úprav</translation>
    </message>
    <message>
      <source>Move Control Points Independently</source>
      <translation>Nezávisle přesouvat řídící body</translation>
    </message>
    <message>
      <source>Move Control Points Symmetrical</source>
      <translation>Symetricky přesouvat řídící body</translation>
    </message>
    <message>
      <source>Open a Polygon or Cuts a Bezier Curve</source>
      <translation>Otevře polygon nebo ořeže Bézierovou křivku</translation>
    </message>
    <message>
      <source>Close this Bezier Curve</source>
      <translation>Zavřít tuto Bźierovou křivku</translation>
    </message>
    <message>
      <source>Mirror the Path Horizontally</source>
      <translation>Zrcadlit horizontálně</translation>
    </message>
    <message>
      <source>Mirror the Path Vertically</source>
      <translation>Zrcadlit vertikálně</translation>
    </message>
    <message>
      <source>Shear the Path Horizontally to the Left</source>
      <translation>Uvolnit horizontálu doleva</translation>
    </message>
    <message>
      <source>Shear the Path Vertically Up</source>
      <translation>Uvolnit vertikálu nahoru</translation>
    </message>
    <message>
      <source>Shear the Path Vertically Down</source>
      <translation>Uvolnit vertikálu dolů</translation>
    </message>
    <message>
      <source>Rotate the Path Counter-Clockwise</source>
      <translation>Rotace proti směru hodinových ručiček</translation>
    </message>
    <message>
      <source>Rotate the Path Clockwise</source>
      <translation>Rotace po směru hodinových ručiček</translation>
    </message>
    <message>
      <source>Reduce the Size of the Path by shown %</source>
      <translation>Zmenšit o uvedené %</translation>
    </message>
    <message>
      <source>Enlarge the Size of the Path by shown %</source>
      <translation>Zvětšit o uvedené %</translation>
    </message>
    <message>
      <source>Angle of Rotation</source>
      <translation>Úhel rotace</translation>
    </message>
    <message>
      <source>% to Enlarge or Reduce By</source>
      <translation>% o které se bude zvětšovat nebo zmenšovat</translation>
    </message>
    <message>
      <source>Activate Contour Line Editing Mode</source>
      <translation>Aktivace úprav kontury</translation>
    </message>
    <message>
      <source>Reset the Contour Line to the Original Shape of the Frame</source>
      <translation>Nastavit konturu na obrys rámu</translation>
    </message>
    <message>
      <source>Shear the Path Horizontally to the Right</source>
      <translation>Uvolnit horizontálu doprava</translation>
    </message>
  </context>
  <context>
    <name>PConsole</name>
    <message>
      <source>Script Console</source>
      <translation>Konzole skriptů</translation>
    </message>
  </context>
  <context>
    <name>PDF_Opts</name>
    <message>
      <source>Export Range</source>
      <translation>Exportovat rozsah</translation>
    </message>
    <message>
      <source>File Options</source>
      <translation>Nastavení souboru</translation>
    </message>
    <message>
      <source>Left Margin</source>
      <translation>Levý okraj</translation>
    </message>
    <message>
      <source>Right Margin</source>
      <translation>Pravý okraj</translation>
    </message>
    <message>
      <source> dpi</source>
      <translation>dpi</translation>
    </message>
    <message>
      <source>General</source>
      <translation>Všeobecné</translation>
    </message>
    <message>
      <source>Embedding</source>
      <translation>Vkládání</translation>
    </message>
    <message>
      <source>Available Fonts:</source>
      <translation>Dostupná písma:</translation>
    </message>
    <message>
      <source>Fonts to embed:</source>
      <translation>Písma k vložení:</translation>
    </message>
    <message>
      <source>Page</source>
      <translation>Strana</translation>
    </message>
    <message>
      <source>Effects</source>
      <translation>Efekty</translation>
    </message>
    <message>
      <source> sec</source>
      <translation>s</translation>
    </message>
    <message>
      <source>No Effect</source>
      <translation>Bez efektu</translation>
    </message>
    <message>
      <source>Blinds</source>
      <translation>Pruhy</translation>
    </message>
    <message>
      <source>Box</source>
      <translation>Rám</translation>
    </message>
    <message>
      <source>Dissolve</source>
      <translation>Rozpuštění</translation>
    </message>
    <message>
      <source>Glitter</source>
      <translation>Lesk</translation>
    </message>
    <message>
      <source>Split</source>
      <translation>Rozdělit</translation>
    </message>
    <message>
      <source>Wipe</source>
      <translation>Setřít</translation>
    </message>
    <message>
      <source>Horizontal</source>
      <translation>Vodorovně</translation>
    </message>
    <message>
      <source>Vertical</source>
      <translation>Svisle</translation>
    </message>
    <message>
      <source>Inside</source>
      <translation>Zevnitř</translation>
    </message>
    <message>
      <source>Outside</source>
      <translation>Zvenku</translation>
    </message>
    <message>
      <source>Left to Right</source>
      <translation>Zleva doprava</translation>
    </message>
    <message>
      <source>Top to Bottom</source>
      <translation>Shora dolů</translation>
    </message>
    <message>
      <source>Bottom to Top</source>
      <translation>Zdola nahoru</translation>
    </message>
    <message>
      <source>Right to Left</source>
      <translation>Zprava doleva</translation>
    </message>
    <message>
      <source>Passwords</source>
      <translation>Hesla</translation>
    </message>
    <message>
      <source>Settings</source>
      <translation>Nastavení</translation>
    </message>
    <message>
      <source>Printer</source>
      <translation>Tiskárna</translation>
    </message>
    <message>
      <source>Solid Colors:</source>
      <translation>Plné barvy (Solid colors):</translation>
    </message>
    <message>
      <source>Profile:</source>
      <translation>Profil:</translation>
    </message>
    <message>
      <source>Rendering-Intent:</source>
      <translation>Účel generování:</translation>
    </message>
    <message>
      <source>Perceptual</source>
      <translation>Perceptuální (fotografická) transformace</translation>
    </message>
    <message>
      <source>Relative Colorimetric</source>
      <translation>Relativní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Saturation</source>
      <translation>Sytost</translation>
    </message>
    <message>
      <source>Absolute Colorimetric</source>
      <translation>Absolutní kolorimetrická transformace</translation>
    </message>
    <message>
      <source>Images:</source>
      <translation>Obrázky:</translation>
    </message>
    <message>
      <source>Don't use embedded ICC profiles</source>
      <translation>Nepoužívat vložené ICC profily</translation>
    </message>
    <message>
      <source>PDF/X-3 Output Intent</source>
      <translation>Výstup do PDF/X-3</translation>
    </message>
    <message>
      <source>Trim Box</source>
      <translation>Vlastní formát stránky</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>Screen / Web</source>
      <translation>Monitor / Web</translation>
    </message>
    <message>
      <source>Top-left to Bottom-Right</source>
      <translation>Zleva nahoře doprava dolů</translation>
    </message>
    <message>
      <source>Image Settings</source>
      <translation>Nastavení obrázků</translation>
    </message>
    <message>
      <source>Automatic</source>
      <translation>Automaticky</translation>
    </message>
    <message>
      <source>JPEG</source>
      <translation>JPEG</translation>
    </message>
    <message>
      <source>Zip</source>
      <translation>Zip</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Maximum</source>
      <translation>Maximální</translation>
    </message>
    <message>
      <source>High</source>
      <translation>Vysoká</translation>
    </message>
    <message>
      <source>Medium</source>
      <translation>Střední</translation>
    </message>
    <message>
      <source>Low</source>
      <translation>Nízká</translation>
    </message>
    <message>
      <source>Minimum</source>
      <translation>Minimální</translation>
    </message>
    <message>
      <source>&amp;General</source>
      <translation>&amp;Všeobecné</translation>
    </message>
    <message>
      <source>&amp;Fonts</source>
      <translation>&amp;Písma</translation>
    </message>
    <message>
      <source>Export all pages to PDF</source>
      <translation>Export všech stran do PDF</translation>
    </message>
    <message>
      <source>Export a range of pages to PDF</source>
      <translation>Export rozsahu stránek do PDF</translation>
    </message>
    <message>
      <source>Determines the PDF compatibility. The default is Acrobat 4.0 which gives the widest compatibility.
Choose Acrobat 5.0 if your file has PDF 1.4 features such as transparency or you require 128 bit encryption.
PDF/X-3 is for exporting the PDF for commercial printing and is selectable when you have activated color management.</source>
      <translation>Určuje kompatibilitu PDF. Implicitně Acrobat 4.0, který poskytuje kompatibilitu nejširší.
Vyberte Acrobat 5.0, jestliže dokument používá vlastnosti PDF 1.4, jako je např. průhlednost nebo 128 bitové šifrování.
Export do PDF/X-3 použijte při komerčním tisku. Je dostupně při fungující správě barev.</translation>
    </message>
    <message>
      <source>Determines the binding of pages in the PDF. Unless you know
you need to change it leave the default choice - Left.</source>
      <translation>Určuje vazbu stran v PDF. Jestliže nepotřebujete speciální
nastavení, nechte implicitní volbu.</translation>
    </message>
    <message>
      <source>Generates thumbnails of each page in the PDF.
Some viewers can use the thumbnails for navigation.</source>
      <translation>Vytvoří náhledy všech stran v PDF.
Některé prohlížeče náhledy použijí k navigaci.</translation>
    </message>
    <message>
      <source>Generate PDF Articles, which is useful for navigating linked articles in a PDF.</source>
      <translation>Vytvořit PDF články, což umožňuje navigaci odkazy v PDF.</translation>
    </message>
    <message>
      <source>Embed the bookmarks you created in your document.
These are useful for navigating long PDF documents.</source>
      <translation>Vložit záložky obsažené v dokumentu.
Ty jsou užitečné k navigaci v obsáhlých PDF dokumentech.</translation>
    </message>
    <message>
      <source>Export resolution of text and vector graphics.
This does not affect the resolution of bitmap images like photos.</source>
      <translation>Rozlišení textu a vektorové grafiky při exportu. Neovlivňuje 
rozlišení bitmapových obrázků, jako jsou např. fotografie.</translation>
    </message>
    <message>
      <source>Compression of text and graphics.
Unless you have a reason, leave this checked. This reduces PDF size.</source>
      <translation>Komprese textu a grafiky.
Pokud nemáte pádný důvod, nechte povolenu. Redukuje velikost PDF souboru.</translation>
    </message>
    <message>
      <source>Version of compression for images.
Automatic allows Scribus to choose the best method.
ZIP is good for images with solid colors.
JPEG is better at creating smaller PDF files which have many photos (with slight image loss possible).
Leave it set to automatic, unless you have a need for special compression options.</source>
      <translation>Způsob komprese obrázků.
Automaticky - Scribus sám vybere vhodnou metodu.
ZIP - vhodné na obrázky s plnými barvami.
JPEG - vytvoří menší PDF, je-li použito mnoho fotografií (drobná ztráta kvality).
Pokud nepotřebujete speciální kompresi, nechte nastaveno na Automaticky.
</translation>
    </message>
    <message>
      <source>Downsample your bitmap images to the selected DPI.
Leaving this unchecked will render them at their native resolution.</source>
      <translation>Snížit kvalitu bitmapových obrázků na zvolené DPI.
Jestliže volbu nepovolíte, bude jim ponecháno jejich původní rozlišení.</translation>
    </message>
    <message>
      <source>DPI (Dots Per Inch) for image export.</source>
      <translation>DPI (Body na palec) exportu obrázků.</translation>
    </message>
    <message>
      <source>Embed fonts into the PDF. Embedding the fonts
will preserve the layout and appearance of your document.</source>
      <translation>Vložit písma do PDF. Vložením písem zajistíte
stejný vzhled dokumentu v jiných prohlížečích.</translation>
    </message>
    <message>
      <source>Enables presentation effects when using Acrobat Reader in full screen mode.</source>
      <translation>Povolit prezentační efekty v celoobrazovkovém režimu Acrobat Readeru.</translation>
    </message>
    <message>
      <source>Show page previews of each page listed above.</source>
      <translation>Ukázat náhled každé strany uvedené v seznamu nahoře.</translation>
    </message>
    <message>
      <source>Length of time the page is shown before the presentation starts on the selected page.</source>
      <translation>Jak dlouho je strana zobrazena, než je spuštěn přechod na dalsší.</translation>
    </message>
    <message>
      <source>Length of time the effect runs.
A shorter time will speed up the effect, a longer one will slow it down.</source>
      <translation>Jak dlouho běží prezentační efekt.
Menší hodnota efekt zrychlí, větší zpomalí.</translation>
    </message>
    <message>
      <source>Type of the display effect.</source>
      <translation>Typ efektu.</translation>
    </message>
    <message>
      <source>Direction of the effect of moving lines for the split and blind effects.</source>
      <translation>Směr efektu Přesouvání řádků nebo Rozdělit.</translation>
    </message>
    <message>
      <source>Starting position for the box and split effects.</source>
      <translation>Startovní pozice efektu Rám nebo Rozdělit.</translation>
    </message>
    <message>
      <source>Direction of the glitter or wipe effects.</source>
      <translation>Směr efektu Lesk nebo Setřít.</translation>
    </message>
    <message>
      <source>Apply the selected effect to all pages.</source>
      <translation>Použít vybraný efekt na všechny strany.</translation>
    </message>
    <message>
      <source>Enable the security features in your exported PDF.
If you selected Acrobat 4.0, the PDF will be protected by 40 bit encryption.
If you selected Acrobat 5.0, the PDF will be protected by 128 bit encryption.
Disclaimer: PDF encryption is not as reliable as GPG or PGP encryption and does have some limitations.</source>
      <translation>Povolit bezpečnostní vlastnosti exportovaného PDF.
Jestliže máte zvolen Acrobat 4.0, bude použito šifrování 40 bity.
Jestliže máte zvolen Acrobat 5.0, použiji 128 bitů.
Poznámka: PDF šifrování není tak spolehlivé jako GPG nebo PGP a má svá omezení.</translation>
    </message>
    <message>
      <source>Choose a master password which enables or disables all the
security features in your exported PDF</source>
      <translation>Zvolte heslo, které povolí nebo zakáže všechny
bezpečnostní vlastnosti exportovaného PDF</translation>
    </message>
    <message>
      <source>Color model for the output of your PDF.
Choose Screen/Web for PDFs which are used for screen display and for printing on typical inkjets.
Choose Printer when printing to a true 4 color CMYK printer.</source>
      <translation>Barevný model výstupu PDF.
Zvolte Monitor/Web na PDF, které je publikováno na monitoru nebo na typické kancelářské tiskárně.
Zvolte Tiskárna, bude-li PDF tištěno na CMYK tiskárně.</translation>
    </message>
    <message>
      <source>Embed a color profile for solid colors</source>
      <translation>Vložit barevný profil plných barev</translation>
    </message>
    <message>
      <source>Color profile for solid colors</source>
      <translation>Barevný profil plných barev</translation>
    </message>
    <message>
      <source>Rendering intent for solid colors</source>
      <translation>Účel reprodukce plných barev</translation>
    </message>
    <message>
      <source>Embed a color profile for images</source>
      <translation>Vložit barevný profil obrázků</translation>
    </message>
    <message>
      <source>Do not use color profiles that are embedded in source images</source>
      <translation>Nepoužívat barevný profil vložený ve zdrojových obrázcích</translation>
    </message>
    <message>
      <source>Color profile for images</source>
      <translation>Barevný profil obrázků</translation>
    </message>
    <message>
      <source>Rendering intent for images</source>
      <translation>Účel reprodukce obrázků</translation>
    </message>
    <message>
      <source>Output profile for printing. If possible, get some guidance from your printer on profile selection.</source>
      <translation>Výstupní profil tisku.</translation>
    </message>
    <message>
      <source>Mandatory string for PDF/X-3 or the PDF will fail
PDF/X-3 conformance. We recommend you use the title of the document.</source>
      <translation>Volitelný text, jehož vyplněním bude PDF nebo PDF/X-3 splňovat
specifikaci. Doporučujeme použít titul dokumentu.</translation>
    </message>
    <message>
      <source>Distance for bleed from the top of the physical page</source>
      <translation>Vzdálenost ořezu od horního okraje fyzické strany</translation>
    </message>
    <message>
      <source>Distance for bleed from the bottom of the physical page</source>
      <translation>Vzdálenost ořezu od dolního okraje fyzické strany</translation>
    </message>
    <message>
      <source>Distance for bleed from the left of the physical page</source>
      <translation>Vzdálenost ořezu od levého okraje fyzické strany</translation>
    </message>
    <message>
      <source>Distance for bleed from the right of the physical page</source>
      <translation>Vzdálenost ořezu od pravého okraje fyzické strany</translation>
    </message>
    <message>
      <source>Compression levels: Minimum (25%), Low (50%), Medium (75%), High (85%), Maximum (95%)</source>
      <translation>Úrovňe komprese: Minimální (25%), Nízká (50%), Střední (75%), Vysoká (85%), Maximální (95%)</translation>
    </message>
    <message>
      <source>Choose a password for users to be able to read your PDF.</source>
      <translation>Zvolit heslo, které musí použít čtenář PDF.</translation>
    </message>
    <message>
      <source>Allow printing of the PDF. If un-checked, printing is prevented. </source>
      <translation>Povolit tisk PDF. Jestliže není zatrženo, tisk není povolen.</translation>
    </message>
    <message>
      <source>Allow modifying of the PDF. If un-checked, modifying the PDF is prevented.</source>
      <translation>Povolit modifikaci PDF. Jestliže není zatrženo, modifikace jsou zakázány.</translation>
    </message>
    <message>
      <source>Allow copying of text or graphics from the PDF. 
If un-checked, text and graphics cannot be copied.</source>
      <translation>Povolit kopírování textu a grafiky z PDF.
Jestliže není zatrženo, text a grafika nelze kopírovat.</translation>
    </message>
    <message>
      <source>Allow adding annotations and fields to the PDF. 
If un-checked, editing annotations and fileds is prevented.</source>
      <translation>Povolit přidávání poznámek a polí formulářů do PDF.
Jestliže není zatrženo, přidávání je zakázáno.</translation>
    </message>
    <message>
      <source>Create PDF File</source>
      <translation>Vytvořit PDF soubor</translation>
    </message>
    <message>
      <source>O&amp;utput to File:</source>
      <translation>&amp;Výstup do souboru:</translation>
    </message>
    <message>
      <source>Cha&amp;nge...</source>
      <translation>&amp;Změnit...</translation>
    </message>
    <message>
      <source>&amp;All Pages</source>
      <translation>Všechny str&amp;any</translation>
    </message>
    <message>
      <source>C&amp;hoose Pages</source>
      <translation>&amp;Vybrat strany</translation>
    </message>
    <message>
      <source>Compatibilit&amp;y:</source>
      <translation>&amp;Kompatibilita:</translation>
    </message>
    <message>
      <source>&amp;Binding:</source>
      <translation>Vaz&amp;ba:</translation>
    </message>
    <message>
      <source>Generate &amp;Thumbnails</source>
      <translation>Vytvořit &amp;náhledy</translation>
    </message>
    <message>
      <source>Save &amp;Linked Text Frames as PDF Articles</source>
      <translation>Uložit &amp;propojené textové rámy jako PDF články</translation>
    </message>
    <message>
      <source>&amp;Include Bookmarks</source>
      <translation>Vče&amp;tně záložek</translation>
    </message>
    <message>
      <source>&amp;Resolution:</source>
      <translation>&amp;Rozlišení:</translation>
    </message>
    <message>
      <source>&amp;Method:</source>
      <translation>Z&amp;působ:</translation>
    </message>
    <message>
      <source>&amp;Quality:</source>
      <translation>K&amp;valita:</translation>
    </message>
    <message>
      <source>&amp;Downsample Images to:</source>
      <translation>Převzorkov&amp;at obrázky na:</translation>
    </message>
    <message>
      <source>&amp;Embed all Fonts</source>
      <translation>V&amp;ložit všechna písma</translation>
    </message>
    <message>
      <source>&amp;>></source>
      <translation>&amp;>></translation>
    </message>
    <message>
      <source>&amp;&lt;&lt;</source>
      <translation>&amp;&lt;&lt;</translation>
    </message>
    <message>
      <source>Show Page Pre&amp;views</source>
      <translation>Zobrazit &amp;náhledy stran</translation>
    </message>
    <message>
      <source>&amp;Display Duration:</source>
      <translation>&amp;Doba zobrazení:</translation>
    </message>
    <message>
      <source>Effec&amp;t Duration:</source>
      <translation>Tr&amp;vání efektu:</translation>
    </message>
    <message>
      <source>Effect T&amp;ype:</source>
      <translation>&amp;Typ efektu:</translation>
    </message>
    <message>
      <source>&amp;Moving Lines:</source>
      <translation>&amp;Přesouvání řádků:</translation>
    </message>
    <message>
      <source>F&amp;rom the:</source>
      <translation>O&amp;d:</translation>
    </message>
    <message>
      <source>D&amp;irection:</source>
      <translation>&amp;Směr:</translation>
    </message>
    <message>
      <source>&amp;Apply Effect on all Pages</source>
      <translation>Po&amp;užít efekt na všechny strany</translation>
    </message>
    <message>
      <source>&amp;Use Encryption</source>
      <translation>Použít ši&amp;frování</translation>
    </message>
    <message>
      <source>&amp;User:</source>
      <translation>&amp;Uživatel:</translation>
    </message>
    <message>
      <source>&amp;Owner:</source>
      <translation>&amp;Vlastník:</translation>
    </message>
    <message>
      <source>Allow &amp;Printing the Document</source>
      <translation>&amp;Povolit tisk dokumentu</translation>
    </message>
    <message>
      <source>Allow &amp;Changing the Document</source>
      <translation>Povolit z&amp;měny dokumentu</translation>
    </message>
    <message>
      <source>Allow Cop&amp;ying Text and Graphics</source>
      <translation>Povolit &amp;kopírování textu a grafiky</translation>
    </message>
    <message>
      <source>Allow Adding &amp;Annotations and Fields</source>
      <translation>Povolit přidávání &amp;anotací a polí formulářů</translation>
    </message>
    <message>
      <source>S&amp;ecurity</source>
      <translation>&amp;Bezpečnost</translation>
    </message>
    <message>
      <source>Output &amp;Intended For:</source>
      <translation>&amp;Plánovaný výstup na:</translation>
    </message>
    <message>
      <source>&amp;Use Custom Rendering Settings</source>
      <translation>&amp;Použít vlastní nastavení reprodukce</translation>
    </message>
    <message>
      <source>Rendering Settings</source>
      <translation>Nastavení reprodukce</translation>
    </message>
    <message>
      <source>Fre&amp;quency:</source>
      <translation>&amp;Frekvence:</translation>
    </message>
    <message>
      <source>&amp;Angle:</source>
      <translation>Úhe&amp;l:</translation>
    </message>
    <message>
      <source>S&amp;pot Function:</source>
      <translation>Funkce &amp;bodu:</translation>
    </message>
    <message>
      <source>Simple Dot</source>
      <translation>Prostá tečka</translation>
    </message>
    <message>
      <source>Line</source>
      <translation>Čára</translation>
    </message>
    <message>
      <source>Round</source>
      <translation>Kruh</translation>
    </message>
    <message>
      <source>Ellipse</source>
      <translation>Elipsa</translation>
    </message>
    <message>
      <source>Use ICC Profile</source>
      <translation>Použít ICC profil</translation>
    </message>
    <message>
      <source>C&amp;olor</source>
      <translation>&amp;Barva</translation>
    </message>
    <message>
      <source>&amp;Info String:</source>
      <translation>&amp;Info text:</translation>
    </message>
    <message>
      <source>Output &amp;Profile:</source>
      <translation>&amp;Výstupní profil:</translation>
    </message>
    <message>
      <source>PDF/X-&amp;3</source>
      <translation>PDF/X-&amp;3</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
      <translation>Vložte čárkou oddělený seznam položek, kde
položka může být *, t.j. všechny strany, 1-5,
t.j. interval, nebo jediné číslo strany.</translation>
    </message>
    <message>
      <source>PDF Files (*.pdf);;All Files (*)</source>
      <translation>PDF soubory (*.pdf);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>This is an advanced setting which is not enabled by default. This should only be enabled
when specifically requested by your printer and they have given you the exact details needed.
Otherwise, your exported PDF may not print properly and is truly not portable across systems.</source>
      <translation>Pokročilá volba, která není implicitně povolena. Může být použita, jestliže to vyžaduje vaše tiskárna.
Pozor. vámi exportované PDF soubory se nemusí korektně tisknout na jiné tiskárně
a nebudou plně přenositelné mezi systémy.</translation>
    </message>
    <message>
      <source>Compress Text and &amp;Vector Graphics</source>
      <translation>Komprimovat text a &amp;vektorovou grafiku</translation>
    </message>
    <message>
      <source>En&amp;able Presentation Effects</source>
      <translation>Povolit prezentační &amp;efekty</translation>
    </message>
    <message>
      <source>&amp;Presentation</source>
      <translation>&amp;Prezentace</translation>
    </message>
    <message>
      <source>&amp;Rotation:</source>
      <translation>&amp;Rotace:</translation>
    </message>
    <message>
      <source>&amp;Subset all Fonts</source>
      <translation>Čá&amp;stečné zařazení písem (subset)</translation>
    </message>
    <message>
      <source>Fonts to subset:</source>
      <translation>Částečně zařazená písma (subset):</translation>
    </message>
    <message>
      <source>Mirror Page(s) horizontally</source>
      <translation>Zrcadlit stranu(y) horizontálně</translation>
    </message>
    <message>
      <source>Mirror Page(s) vertically</source>
      <translation>Zrcadlit stranu(y) vertikálně</translation>
    </message>
  </context>
  <context>
    <name>PPreview</name>
    <message>
      <source>Print Preview</source>
      <translation>Ukázka před tiskem</translation>
    </message>
    <message>
      <source>All</source>
      <translation>Všechny</translation>
    </message>
    <message>
      <source>Provides a more pleasant view of text items in the viewer, at the expense
of a slight slowdown in previewing. This only affects Type 1 fonts</source>
      <translation>Zajistí hezčí vzhled textu v náhledu, ale zpomalí jeho vytváření.
Týká se Type 1 písem</translation>
    </message>
    <message>
      <source>Shows transparency and transparent items in your document. Requires Ghostscript 7.07 or later</source>
      <translation>Zobrazí práhlednost a průhledné objekty dokumentu. Vyžaduje Ghostscript 7.07 nebo novější</translation>
    </message>
    <message>
      <source>Gives a print preview using simulations of generic CMYK inks, instead of RGB colors</source>
      <translation>Vytvoří náhled tisku simulací CMYK inkoustů místo RGB barev</translation>
    </message>
    <message>
      <source>Enable/disable the C (Cyan) ink plate</source>
      <translation>Povolí/zakáže C (Cyan) složku</translation>
    </message>
    <message>
      <source>Enable/disable the M (Magenta) ink plate</source>
      <translation>Povolí/zakáže M (Magenta) složku</translation>
    </message>
    <message>
      <source>Enable/disable the Y (Yellow) ink plate</source>
      <translation>Povolí/zakáže Y (Yellow) složku</translation>
    </message>
    <message>
      <source>Enable/disable the K (Black) ink plate</source>
      <translation>Povolí/zakáže B (Black) složku</translation>
    </message>
    <message>
      <source>Anti-alias &amp;Text</source>
      <translation>Vyhlazený &amp;text</translation>
    </message>
    <message>
      <source>Anti-alias &amp;Graphics</source>
      <translation>Vyhlazená &amp;grafika</translation>
    </message>
    <message>
      <source>Display Trans&amp;parency</source>
      <translation>Zobrait &amp;průhlednost</translation>
    </message>
    <message>
      <source>&amp;Display CMYK</source>
      <translation>&amp;Zobrazit CMYK</translation>
    </message>
    <message>
      <source>&amp;C</source>
      <translation>&amp;C</translation>
    </message>
    <message>
      <source>&amp;M</source>
      <translation>&amp;M</translation>
    </message>
    <message>
      <source>&amp;Y</source>
      <translation>&amp;Y</translation>
    </message>
    <message>
      <source>&amp;K</source>
      <translation>&amp;K</translation>
    </message>
    <message>
      <source>&amp;Under Color Removal</source>
      <translation>&amp;Under Color Removal</translation>
    </message>
    <message>
      <source>A way of switching off some of the gray shades which are composed
of cyan, yellow and magenta and using black instead.
UCR most affects parts of images which are neutral and/or dark tones
which are close to the gray. Use of this may improve printing some images
and some experimentation and testing is need on a case by case basis.
UCR reduces the possibility of over saturation with CMY inks.</source>
      <translation>UCR - under color removal - odstranění přebytečné barvy, která by 
způsobila rozpíjení (při přílišné saturaci papíru barvou) nebo trhání 
barvy při několika vrstvém (např. barevném) laserovém tisku.
Viz. např. http://www.typo.cz/_pismo/pis-tech-post.html
a jiné.</translation>
    </message>
    <message>
      <source>Provides a more pleasant view of TrueType Fonts, OpenType Fonts, EPS, PDF and
vector graphics in the preview, at the expense of a slight slowdown in previewing</source>
      <translation>Zajistí hezčí vzhled TrueType a OpenType písem, EPS, PDF a vektorové grafiky
v náhledu, ale zpomalí se jeho vytváření</translation>
    </message>
  </context>
  <context>
    <name>Page</name>
    <message>
      <source>Copy Here</source>
      <translation>Kopírovat sem</translation>
    </message>
    <message>
      <source>Move Here</source>
      <translation>Přesunout sem</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Picture</source>
      <translation>Obrázek</translation>
    </message>
    <message>
      <source>File: </source>
      <translation>Soubor:</translation>
    </message>
    <message>
      <source>Text Frame</source>
      <translation>Textový rám</translation>
    </message>
    <message>
      <source>Text on a Path</source>
      <translation>Text na křivky</translation>
    </message>
    <message>
      <source>Paragraphs: </source>
      <translation>Odstavce:</translation>
    </message>
    <message>
      <source>Words: </source>
      <translation>Slova:</translation>
    </message>
    <message>
      <source>Chars: </source>
      <translation>Znaky:</translation>
    </message>
    <message>
      <source>Edit Text...</source>
      <translation>Editovat text...</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Linked Text</source>
      <translation>Řeťezený text</translation>
    </message>
    <message>
      <source>Print: </source>
      <translation>Tisk:</translation>
    </message>
    <message>
      <source>Enabled</source>
      <translation>Povoleno</translation>
    </message>
    <message>
      <source>Disabled</source>
      <translation>Zakázáno</translation>
    </message>
    <message>
      <source>The Program</source>
      <translation>Program</translation>
    </message>
    <message>
      <source>is missing!</source>
      <translation>chybí!</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Copy of</source>
      <translation>Kopie</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
    <message>
      <source>Show &amp;Margins</source>
      <translation>Zobrazit o&amp;kraje</translation>
    </message>
    <message>
      <source>Show &amp;Frames</source>
      <translation>Zobrazit &amp;rámy</translation>
    </message>
    <message>
      <source>Show &amp;Images</source>
      <translation>Zobrazit &amp;obrázky</translation>
    </message>
    <message>
      <source>Show &amp;Grid</source>
      <translation>Ukázat &amp;mřížku</translation>
    </message>
    <message>
      <source>Show G&amp;uides</source>
      <translation>Zobrazit &amp;vodítka</translation>
    </message>
    <message>
      <source>Show &amp;Baseline Grid</source>
      <translation>&amp;Zobrazit pomocnou mřížku</translation>
    </message>
    <message>
      <source>Sn&amp;ap to Grid</source>
      <translation>M&amp;agnetická mřížka</translation>
    </message>
    <message>
      <source>Sna&amp;p to Guides</source>
      <translation>Ma&amp;gnetická vodítka</translation>
    </message>
    <message>
      <source>Original PPI: </source>
      <translation>Původní PPI:</translation>
    </message>
    <message>
      <source>Actual PPI: </source>
      <translation>Aktuální PPI:</translation>
    </message>
    <message>
      <source>In&amp;fo</source>
      <translation>In&amp;fo</translation>
    </message>
    <message>
      <source>&amp;Get Picture...</source>
      <translation>&amp;Vložit obrázek...</translation>
    </message>
    <message>
      <source>I&amp;mage Visible</source>
      <translation>Vi&amp;ditelný obrázek</translation>
    </message>
    <message>
      <source>&amp;Update Picture</source>
      <translation>&amp;Aktualizovat obrázek</translation>
    </message>
    <message>
      <source>&amp;Edit Picture</source>
      <translation>&amp;Upravit obrázek</translation>
    </message>
    <message>
      <source>&amp;Adjust Frame to Picture</source>
      <translation>&amp;Přizpůsobit rámec obrázku</translation>
    </message>
    <message>
      <source>&amp;Get Text...</source>
      <translation>&amp;Vložit text...</translation>
    </message>
    <message>
      <source>&amp;Append Text...</source>
      <translation>Připo&amp;jit text...</translation>
    </message>
    <message>
      <source>&amp;Edit Text...</source>
      <translation>&amp;Editovat text...</translation>
    </message>
    <message>
      <source>&amp;Insert Sample Text</source>
      <translation>Vložit ukázkový &amp;text (Lorem Ipsum)</translation>
    </message>
    <message>
      <source>Is PDF &amp;Bookmark</source>
      <translation>Je PDF &amp;záložkou</translation>
    </message>
    <message>
      <source>Is PDF A&amp;nnotation</source>
      <translation>Je PDF &amp;anotací</translation>
    </message>
    <message>
      <source>Annotation P&amp;roperties</source>
      <translation>Vlast&amp;nosti anotace</translation>
    </message>
    <message>
      <source>Field P&amp;roperties</source>
      <translation>Vlastnosti &amp;pole</translation>
    </message>
    <message>
      <source>&amp;PDF Options</source>
      <translation>&amp;Možnosti PDF</translation>
    </message>
    <message>
      <source>&amp;Lock</source>
      <translation>&amp;Zamknout</translation>
    </message>
    <message>
      <source>Un&amp;lock</source>
      <translation>O&amp;demknout</translation>
    </message>
    <message>
      <source>Lock Object &amp;Size</source>
      <translation>Zamknout &amp;rozměry objektu</translation>
    </message>
    <message>
      <source>Unlock Object &amp;Size</source>
      <translation>Odemknout &amp;rozměry objektu</translation>
    </message>
    <message>
      <source>Send to S&amp;crapbook</source>
      <translation>&amp;Poslat do zápisníku</translation>
    </message>
    <message>
      <source>Send to La&amp;yer</source>
      <translation>Přesu&amp;nout do hladiny</translation>
    </message>
    <message>
      <source>&amp;Group</source>
      <translation>&amp;Seskupit</translation>
    </message>
    <message>
      <source>Un&amp;group</source>
      <translation>Zrušit &amp;seskupení</translation>
    </message>
    <message>
      <source>Le&amp;vel</source>
      <translation>&amp;Hladina</translation>
    </message>
    <message>
      <source>Send to &amp;Back</source>
      <translation>&amp;Dát zcela dospodu</translation>
    </message>
    <message>
      <source>Bring to &amp;Front</source>
      <translation>Dát zcela &amp;navrch</translation>
    </message>
    <message>
      <source>&amp;Lower</source>
      <translation>Dát o &amp;vrstvu níž</translation>
    </message>
    <message>
      <source>&amp;Raise</source>
      <translation>Dát o v&amp;rstvu výš</translation>
    </message>
    <message>
      <source>&amp;Picture Frame</source>
      <translation>Rám &amp;obrázku</translation>
    </message>
    <message>
      <source>Pol&amp;ygon</source>
      <translation>&amp;Mnohoúhelník</translation>
    </message>
    <message>
      <source>&amp;Outlines</source>
      <translation>O&amp;brysy</translation>
    </message>
    <message>
      <source>&amp;Text Frame</source>
      <translation>&amp;Textový rám</translation>
    </message>
    <message>
      <source>&amp;Bezier Curve</source>
      <translation>&amp;Beziérova křivka</translation>
    </message>
    <message>
      <source>Conve&amp;rt to</source>
      <translation>K&amp;onverze na</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>C&amp;lear Contents</source>
      <translation>V&amp;ymazat obsah</translation>
    </message>
    <message>
      <source>Show P&amp;roperties...</source>
      <translation>Ukázat v&amp;lastnosti...</translation>
    </message>
    <message>
      <source>Hide P&amp;roperties...</source>
      <translation>Skrýt v&amp;lastnosti...</translation>
    </message>
    <message>
      <source>Do you really want to clear all your Text?</source>
      <translation>Opravdu chcete smazat veškerý text?</translation>
    </message>
  </context>
  <context>
    <name>PageItem</name>
    <message>
      <source>Image</source>
      <translation>Obrázek</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Line</source>
      <translation>Čára</translation>
    </message>
    <message>
      <source>Polygon</source>
      <translation>Mnohoúhelník</translation>
    </message>
    <message>
      <source>Polyline</source>
      <translation>Lomená čára</translation>
    </message>
    <message>
      <source>PathText</source>
      <translation>Text na křivky</translation>
    </message>
  </context>
  <context>
    <name>PageSelector</name>
    <message>
      <source>Page </source>
      <translation>Strana</translation>
    </message>
    <message>
      <source> of %1</source>
      <translation>z %1</translation>
    </message>
  </context>
  <context>
    <name>PicSearch</name>
    <message>
      <source>Result</source>
      <translation>Výsledek</translation>
    </message>
    <message>
      <source>Search Results for: </source>
      <translation>Hledat výsledek pro:</translation>
    </message>
    <message>
      <source>Preview</source>
      <translation>Náhled</translation>
    </message>
    <message>
      <source>Select</source>
      <translation>Výběr</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
  </context>
  <context>
    <name>PicStatus</name>
    <message>
      <source>Pictures</source>
      <translation>Obrázky</translation>
    </message>
    <message>
      <source>Name</source>
      <translation>Jméno</translation>
    </message>
    <message>
      <source>Path</source>
      <translation>Cesta</translation>
    </message>
    <message>
      <source>Page</source>
      <translation>Strana</translation>
    </message>
    <message>
      <source>Print</source>
      <translation>Tisk</translation>
    </message>
    <message>
      <source>Status</source>
      <translation>Stav</translation>
    </message>
    <message>
      <source>Goto</source>
      <translation>Jít na</translation>
    </message>
    <message>
      <source>Yes</source>
      <translation>Ano</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Missing</source>
      <translation>Chybí</translation>
    </message>
    <message>
      <source>Search</source>
      <translation>Hledat</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
  </context>
  <context>
    <name>PolygonProps</name>
    <message>
      <source>Polygon Properties</source>
      <translation>Vlastnosti mnohoúhelníků</translation>
    </message>
    <message>
      <source> %</source>
      <translation> %</translation>
    </message>
    <message>
      <source>Corn&amp;ers:</source>
      <translation>Ro&amp;hy:</translation>
    </message>
    <message>
      <source>&amp;Rotation:</source>
      <translation>&amp;Rotace:</translation>
    </message>
    <message>
      <source>&amp;Factor:</source>
      <translation>&amp;Faktor:</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Number of corners for polygons</source>
      <translation>Počet rohů mnohoúhelníků</translation>
    </message>
    <message>
      <source>Degrees of rotation for polygons</source>
      <translation>Stupně rotace mnohoúhelníků</translation>
    </message>
    <message>
      <source>Sample Polygon</source>
      <translation>Ukázkový mnohoúhelník</translation>
    </message>
    <message>
      <source>Apply &amp;Factor</source>
      <translation>Použít &amp;faktor</translation>
    </message>
    <message>
      <source>Apply Convex/Concave Factor to change shape of Polygons</source>
      <translation>Aplikovat konvexnost/konkávnost na mnohoúhelník</translation>
    </message>
    <message>
      <source>A negative value will make the polygon concave (or star shaped),
 a positive value will make it convex</source>
      <translation>Záporná hodnota nastaví mnohoúhelník jako 
konkávní (nebo s hranami do hvězdy), kladná konvexní</translation>
    </message>
  </context>
  <context>
    <name>Preferences</name>
    <message>
      <source>Preferences</source>
      <translation>Nastavení</translation>
    </message>
    <message>
      <source>General</source>
      <translation>Všeobecné</translation>
    </message>
    <message>
      <source>Document</source>
      <translation>Dokument</translation>
    </message>
    <message>
      <source>Guides</source>
      <translation>Vodítka</translation>
    </message>
    <message>
      <source>Typography</source>
      <translation>Typografie</translation>
    </message>
    <message>
      <source>Tools</source>
      <translation>Nástroje</translation>
    </message>
    <message>
      <source>Scrapbook</source>
      <translation>Zápisník</translation>
    </message>
    <message>
      <source>Display</source>
      <translation>Zobrazit</translation>
    </message>
    <message>
      <source>GUI</source>
      <translation>GUI</translation>
    </message>
    <message>
      <source>Units</source>
      <translation>Jednotky</translation>
    </message>
    <message>
      <source>Points (pt)</source>
      <translation>Body (pt)</translation>
    </message>
    <message>
      <source>Millimetres (mm)</source>
      <translation>Milimetry (mm)</translation>
    </message>
    <message>
      <source>Inches (in)</source>
      <translation>Palce (in)</translation>
    </message>
    <message>
      <source>Picas (p)</source>
      <translation>Pika (p)</translation>
    </message>
    <message>
      <source>Menus</source>
      <translation>Nabídky</translation>
    </message>
    <message>
      <source>Paths</source>
      <translation>Cesty</translation>
    </message>
    <message>
      <source>Page Size</source>
      <translation>Velikost strany</translation>
    </message>
    <message>
      <source>Custom</source>
      <translation>Vlastní</translation>
    </message>
    <message>
      <source>Portrait</source>
      <translation>Na výšku</translation>
    </message>
    <message>
      <source>Landscape</source>
      <translation>Na šířku</translation>
    </message>
    <message>
      <source>Margin Guides</source>
      <translation>Vodítka okrajů</translation>
    </message>
    <message>
      <source>Autosave</source>
      <translation>Automatické uložení</translation>
    </message>
    <message>
      <source>min</source>
      <translation>min</translation>
    </message>
    <message>
      <source>Grid Layout</source>
      <translation>Rozložení mřížky</translation>
    </message>
    <message>
      <source>Grid Colors</source>
      <translation>Barvy mřížky</translation>
    </message>
    <message>
      <source>Placing</source>
      <translation>Umístění</translation>
    </message>
    <message>
      <source>Subscript</source>
      <translation>Dolní index</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Superscript</source>
      <translation>Horní index</translation>
    </message>
    <message>
      <source>Small Caps</source>
      <translation>Kapitálky</translation>
    </message>
    <message>
      <source>Other</source>
      <translation>Jiné</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Woven silk pyjamas exchanged for blue quartz</source>
      <translation>Příliš žluťoučký kůň úpěl ďábelské Ódy</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Other Options</source>
      <translation>Ostatní nastavení</translation>
    </message>
    <message>
      <source>Preview</source>
      <translation>Náhled</translation>
    </message>
    <message>
      <source>Small</source>
      <translation>Malá</translation>
    </message>
    <message>
      <source>Medium</source>
      <translation>Střední</translation>
    </message>
    <message>
      <source>To adjust the display drag the ruler below with the Slider.</source>
      <translation>Obrazovku přizpůsobíte posuem jezdce na spodním pravítku.</translation>
    </message>
    <message>
      <source>Choose a Directory</source>
      <translation>Vybrat adresář</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>External Tools</source>
      <translation>Externí nástroje</translation>
    </message>
    <message>
      <source>Misc.</source>
      <translation>Různé</translation>
    </message>
    <message>
      <source>Postscript Interpreter</source>
      <translation>Interpret postsriptu</translation>
    </message>
    <message>
      <source>Image Processing Tool</source>
      <translation>Nástroj na úpravu obrázků</translation>
    </message>
    <message>
      <source>Printing</source>
      <translation>Tisk</translation>
    </message>
    <message>
      <source>Choose the default window decoration and looks.
Scribus inherits any available KDE or Qt themes</source>
      <translation>Vyberte implicitní vzhled a dekoraci oken.
Scribus používá jakékoli téma z Qt nemo KDE</translation>
    </message>
    <message>
      <source>Default font size for the menus and windows</source>
      <translation>Velikost písma v menu a oknech</translation>
    </message>
    <message>
      <source>Default unit of measurement for document editing</source>
      <translation>Implicitní měrná jednotka dokumentu</translation>
    </message>
    <message>
      <source>Number of lines Scribus will scroll for each move of the mouse wheel</source>
      <translation>Počet řádek, o které Scribus posune text při pohybu kolečka myši</translation>
    </message>
    <message>
      <source>Radius of the area where Scribus will allow you to grab an objects handles</source>
      <translation>Poloměr oblasti, kterou Scribus považuje za oblast daného objektu</translation>
    </message>
    <message>
      <source>Number of recently edited documents to show in the File menu</source>
      <translation>Počet současně otevřených dokumentů, které jsou vidět v Soubor menu</translation>
    </message>
    <message>
      <source>Default documents directory</source>
      <translation>Implicitní adresář na dokumenty</translation>
    </message>
    <message>
      <source>Default ICC profiles directory</source>
      <translation>Implicitní adresář na ICC profily</translation>
    </message>
    <message>
      <source>Default Scripter scripts directory</source>
      <translation>Implicitní adresář na skripty</translation>
    </message>
    <message>
      <source>Default page size, either a standard size or a custom size</source>
      <translation>Implicitní velikost strany, standardní nebo vlastní rozměr</translation>
    </message>
    <message>
      <source>Default orientation of document pages</source>
      <translation>Implicitní orientace stran dokumentu</translation>
    </message>
    <message>
      <source>Width of document pages, editable if you have chosen a custom page size</source>
      <translation>Šířka stran dokumentu - upravitelná, jestliže je vybrán volitelný rozměr</translation>
    </message>
    <message>
      <source>Height of document pages, editable if you have chosen a custom page size</source>
      <translation>Šířka stran dokumentu - upravitelná, jestliže je vybrán volitelný rozměr</translation>
    </message>
    <message>
      <source>Enable single or spread based layout</source>
      <translation>Povolit rozložení po jedné nebo po více stranách</translation>
    </message>
    <message>
      <source>Make the first page the left page of a document</source>
      <translation>První strana je levou stranou dokumentu</translation>
    </message>
    <message>
      <source>Distance between the top margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi horním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the bottom margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi dolním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the left margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi levým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source>Distance between the right margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi pravým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source>When enabled, Scribus saves a backup copy of your file with the .bak extension
each time the time period elapses</source>
      <translation>Je-li povoleno, Scribus uloží záložní kopii dokumentu do souboru s .bak příponou
po každém automatickém uložení</translation>
    </message>
    <message>
      <source>Time period between saving automatically</source>
      <translation>Časový interval automatického ukládání</translation>
    </message>
    <message>
      <source>Distance between the minor grid lines</source>
      <translation>Vzdálenost mezi čarami vedlejší mřížky</translation>
    </message>
    <message>
      <source>Distance between the major grid lines</source>
      <translation>Vzdálenost mezi čarami hlavní mřížky</translation>
    </message>
    <message>
      <source>Distance within which an object will snap to your placed guides</source>
      <translation>Vzdálenost, ve které se čára mřížky chová vůči objektu jako magnet</translation>
    </message>
    <message>
      <source>Color of the minor grid lines</source>
      <translation>Barva čar vedlejší mřížky</translation>
    </message>
    <message>
      <source>Color of the major grid lines</source>
      <translation>Barva čar hlavní mřížky</translation>
    </message>
    <message>
      <source>Color of the guide lines you insert</source>
      <translation>Barva vodítek, které vkládáte manuálně</translation>
    </message>
    <message>
      <source>Place the grid behind your page objects</source>
      <translation>Umístit mřížku za objekty</translation>
    </message>
    <message>
      <source>Place the grid in front of your page objects</source>
      <translation>Umístit mřížku před objekty</translation>
    </message>
    <message>
      <source>Displacement above the baseline of the font on a line</source>
      <translation>Posunutí nad účaří</translation>
    </message>
    <message>
      <source>Relative size of the superscript compared to the normal font</source>
      <translation>Relativní velikost horního indexu vůči normální velikosti písma</translation>
    </message>
    <message>
      <source>Displacement below the baseline of the normal font on a line</source>
      <translation>Posunutí pod účaří</translation>
    </message>
    <message>
      <source>Relative size of the subscript compared to the normal font</source>
      <translation>Relativní velikost dolního indexu vůči normální velikosti písma</translation>
    </message>
    <message>
      <source>Relative size of the small caps font compared to the normal font</source>
      <translation>Relativní velikost kapitálek vůči normální velikosti písma</translation>
    </message>
    <message>
      <source>Percentage increase over the font size for the line spacing</source>
      <translation>Procentuální zvětšení řádkování podle velikosti písma</translation>
    </message>
    <message>
      <source>Text Frame Properties</source>
      <translation>Vlastnosti textových rámců</translation>
    </message>
    <message>
      <source>Picture Frame Properties</source>
      <translation>Vlastnosti obrázkových rámců</translation>
    </message>
    <message>
      <source>Shape Drawing Properties</source>
      <translation>Vlastnosti kreslení obrysů</translation>
    </message>
    <message>
      <source>Magnification Level Defaults</source>
      <translation>Vlastnosti úrovně zvětšení</translation>
    </message>
    <message>
      <source>Line Drawing Properties</source>
      <translation>Vlastnosti čar</translation>
    </message>
    <message>
      <source>Polygon Drawing Properties</source>
      <translation>Vlastnosti mnohoúhelníků</translation>
    </message>
    <message>
      <source>Font for new text frames</source>
      <translation>Písmo nového textového rámu</translation>
    </message>
    <message>
      <source>Size of font for new text frames</source>
      <translation>Velikost písma nového textového rámu</translation>
    </message>
    <message>
      <source>Color of font</source>
      <translation>Barva písma</translation>
    </message>
    <message>
      <source>Number of columns in a text frame</source>
      <translation>Počet sloupců v textovém rámu</translation>
    </message>
    <message>
      <source>Gap between text frame columns</source>
      <translation>Mezera mezi sloupci textového rámu</translation>
    </message>
    <message>
      <source>Sample of your font</source>
      <translation>Ukázka písma</translation>
    </message>
    <message>
      <source>Picture frames allow pictures to scale to any size</source>
      <translation>Obrázkové rámy mohou libovolně měnit rozměry obrázku</translation>
    </message>
    <message>
      <source>Horizontal scaling of images</source>
      <translation>Horizontální zvětšení obrázků</translation>
    </message>
    <message>
      <source>Vertical scaling of images</source>
      <translation>Vertikální zvětšení obrázků</translation>
    </message>
    <message>
      <source>Keep horizontal and vertical scaling the same</source>
      <translation>Držet stejné horizontální a vertikální zvětšení</translation>
    </message>
    <message>
      <source>Pictures in picture frames are scaled to the size of the frame</source>
      <translation>Obrázky budou deformovány podle rozměrů rámu</translation>
    </message>
    <message>
      <source>Automatically scaled pictures keep their original proportions</source>
      <translation>Automaticky nastavovaná velikost obrázků dodržuje originální proporce</translation>
    </message>
    <message>
      <source>Fill color of picture frames</source>
      <translation>Barva výplně obrázkových rámů</translation>
    </message>
    <message>
      <source>Saturation of color of fill</source>
      <translation>Sytost barvy výplně</translation>
    </message>
    <message>
      <source>Line color of shapes</source>
      <translation>Barva čar obrysů</translation>
    </message>
    <message>
      <source>Saturation of color of lines</source>
      <translation>Sytost barvy čar</translation>
    </message>
    <message>
      <source>Fill color of shapes</source>
      <translation>Barva výplně obrysů</translation>
    </message>
    <message>
      <source>Line style of shapes</source>
      <translation>Styl čar obrysů</translation>
    </message>
    <message>
      <source>Line width of shapes</source>
      <translation>Tloušťka čar obrysů</translation>
    </message>
    <message>
      <source>Minimum magnification allowed</source>
      <translation>Minimální povolené zvětšení (zmenšení)</translation>
    </message>
    <message>
      <source>Maximum magnification allowed</source>
      <translation>Maximální povolené zvětšení</translation>
    </message>
    <message>
      <source>Change in magnification for each zoom operation</source>
      <translation>Změna zvětšení - krok operace lupou</translation>
    </message>
    <message>
      <source>Color of lines</source>
      <translation>Barva čar</translation>
    </message>
    <message>
      <source>Saturation of color</source>
      <translation>Sytost barvy</translation>
    </message>
    <message>
      <source>Style of lines</source>
      <translation>Styl čar</translation>
    </message>
    <message>
      <source>Width of lines</source>
      <translation>Šířka čár</translation>
    </message>
    <message>
      <source>Number of corners for polygons</source>
      <translation>Počet rohů mnohoúhelníků</translation>
    </message>
    <message>
      <source>Degrees of rotation for polygons</source>
      <translation>Stupně rotace mnohoúhelníků</translation>
    </message>
    <message>
      <source>Sample Polygon</source>
      <translation>Ukázkový mnohoúhelník</translation>
    </message>
    <message>
      <source>Choose the size of the preview in the scrapbook palette</source>
      <translation>Zvolit velikost náhledu v zápisníku</translation>
    </message>
    <message>
      <source>Save the scrapbook contents everytime after a change</source>
      <translation>Uložit obsah zápisníku po každé jeho změně</translation>
    </message>
    <message>
      <source>When using facing pages, show the two pages side by side</source>
      <translation>Ukazovat strany vedle sebe, jsou-li nastaveny protilehlé strany</translation>
    </message>
    <message>
      <source>Color for paper</source>
      <translation>Barva papíru</translation>
    </message>
    <message>
      <source>Color for the margin lines</source>
      <translation>Barva okrajových čar</translation>
    </message>
    <message>
      <source>Mask the area outside the margins in the margin color</source>
      <translation>Vyplnit plochu za hranicemi strany barvou okrajů</translation>
    </message>
    <message>
      <source>Enable transparency features within PDF 1.4 export</source>
      <translation>Povolit transparentnost v exportu PDF 1.4</translation>
    </message>
    <message>
      <source>Set the default zoom level</source>
      <translation>Nastavení implicitní úrovně zvětšení</translation>
    </message>
    <message>
      <source>Filesystem location for the Ghostscript interpreter</source>
      <translation>Umístění Ghostscript interpreteru na disku</translation>
    </message>
    <message>
      <source>Antialias text for EPS and PDF onscreen rendering</source>
      <translation>Vyhlazovat text při vykreslování EPS a PDF na monitoru</translation>
    </message>
    <message>
      <source>Antialias graphics for EPS and PDF onscreen rendering</source>
      <translation>Vyhlazovat grafiku při vykreslování EPS a PDF na monitoru</translation>
    </message>
    <message>
      <source>Filesystem location for graphics editor</source>
      <translation>Umístění grafického editoru na disku</translation>
    </message>
    <message>
      <source>Do not show objects outside the margins on the printed page or exported file</source>
      <translation>Neukazovat objekty mimo hranice tisknutelné strany nebo exportovaného souboru</translation>
    </message>
    <message>
      <source>Baseline Grid</source>
      <translation>Pomocná mřížka</translation>
    </message>
    <message>
      <source>Turns on the basegrid</source>
      <translation>Zapnout pomocnou mřížku</translation>
    </message>
    <message>
      <source>Turns off the basegrid</source>
      <translation>Vypnout pomocnou mřížku</translation>
    </message>
    <message>
      <source> px</source>
      <translation>px</translation>
    </message>
    <message>
      <source>&amp;Theme:</source>
      <translation>&amp;Téma:</translation>
    </message>
    <message>
      <source>&amp;Font Size:</source>
      <translation>&amp;Velikost písma:</translation>
    </message>
    <message>
      <source>Mouse Settings</source>
      <translation>Nastavení myši</translation>
    </message>
    <message>
      <source>&amp;Wheel Jump:</source>
      <translation>&amp;Skok kolečka myši:</translation>
    </message>
    <message>
      <source>&amp;Grab Radius:</source>
      <translation>&amp;Poloměr oblasti patřící objektu:</translation>
    </message>
    <message>
      <source>&amp;Recent Documents:</source>
      <translation>&amp;Nedávné dokumenty:</translation>
    </message>
    <message>
      <source>&amp;Documents:</source>
      <translation>&amp;Dokumenty:</translation>
    </message>
    <message>
      <source>&amp;Change...</source>
      <translation>Z&amp;měnit...</translation>
    </message>
    <message>
      <source>&amp;ICC Profiles:</source>
      <translation>&amp;ICC profily:</translation>
    </message>
    <message>
      <source>C&amp;hange...</source>
      <translation>Změn&amp;it...</translation>
    </message>
    <message>
      <source>&amp;Scripts:</source>
      <translation>S&amp;kripty:</translation>
    </message>
    <message>
      <source>Ch&amp;ange...</source>
      <translation>Změni&amp;t...</translation>
    </message>
    <message>
      <source>&amp;Size:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <source>Orie&amp;ntation:</source>
      <translation>&amp;Orientace:</translation>
    </message>
    <message>
      <source>&amp;Width:</source>
      <translation>Šíř&amp;ka:</translation>
    </message>
    <message>
      <source>&amp;Height:</source>
      <translation>&amp;Výška:</translation>
    </message>
    <message>
      <source>&amp;Facing Pages</source>
      <translation>P&amp;rotilehlé stránky (Dvoustrany)</translation>
    </message>
    <message>
      <source>Left &amp;Page First</source>
      <translation>Prv&amp;ní strana vlevo</translation>
    </message>
    <message>
      <source>&amp;Bottom:</source>
      <translation>&amp;Dolní:</translation>
    </message>
    <message>
      <source>&amp;Top:</source>
      <translation>&amp;Horní:</translation>
    </message>
    <message>
      <source>&amp;Right:</source>
      <translation>&amp;Pravý:</translation>
    </message>
    <message>
      <source>&amp;Left:</source>
      <translation>&amp;Levý:</translation>
    </message>
    <message>
      <source>&amp;Enabled</source>
      <translation>Povo&amp;leno</translation>
    </message>
    <message>
      <source>&amp;Interval:</source>
      <translation>&amp;Interval:</translation>
    </message>
    <message>
      <source>M&amp;inor Grid Spacing:</source>
      <translation>Mezery &amp;vedlejší mřížky:</translation>
    </message>
    <message>
      <source>Ma&amp;jor Grid Spacing:</source>
      <translation>Mezery &amp;hlavní mřížky:</translation>
    </message>
    <message>
      <source>Guide &amp;Snap Distance:</source>
      <translation>&amp;Dosah magnetických vodítek:</translation>
    </message>
    <message>
      <source>Min&amp;or Grid Color:</source>
      <translation>B&amp;arva vedlejší mřížky:</translation>
    </message>
    <message>
      <source>Majo&amp;r Grid Color:</source>
      <translation>&amp;Barva hlavní mřížky:</translation>
    </message>
    <message>
      <source>&amp;User Guides Color:</source>
      <translation>Barva v&amp;lastních vodítek:</translation>
    </message>
    <message>
      <source>Base&amp;line Grid Color:</source>
      <translation>Barva po&amp;mocné mřížky:</translation>
    </message>
    <message>
      <source>In the &amp;Background</source>
      <translation>V &amp;pozadí</translation>
    </message>
    <message>
      <source>In the Fore&amp;ground</source>
      <translation>V p&amp;opředí</translation>
    </message>
    <message>
      <source>O&amp;n</source>
      <translation>Zapnou&amp;t</translation>
    </message>
    <message>
      <source>O&amp;ff</source>
      <translation>Vypno&amp;ut</translation>
    </message>
    <message>
      <source>&amp;Displacement:</source>
      <translation>&amp;Posunutí:</translation>
    </message>
    <message>
      <source>&amp;Scaling:</source>
      <translation>Z&amp;většení:</translation>
    </message>
    <message>
      <source>D&amp;isplacement:</source>
      <translation>Po&amp;sunutí:</translation>
    </message>
    <message>
      <source>S&amp;caling:</source>
      <translation>Zvě&amp;tšení:</translation>
    </message>
    <message>
      <source>Sc&amp;aling:</source>
      <translation>Zvětše&amp;ní:</translation>
    </message>
    <message>
      <source>Baseline &amp;Grid:</source>
      <translation>Pomocná &amp;mřížka:</translation>
    </message>
    <message>
      <source>Baseline &amp;Offset:</source>
      <translation>&amp;Odstup pomocné mřížky:</translation>
    </message>
    <message>
      <source>Automatic &amp;Line Spacing:</source>
      <translation>&amp;Automatické řádkování:</translation>
    </message>
    <message>
      <source>Default &amp;Font:</source>
      <translation>Implicitní &amp;písmo:</translation>
    </message>
    <message>
      <source>Default &amp;Size:</source>
      <translation>Implicitní &amp;velikost:</translation>
    </message>
    <message>
      <source>&amp;Text Color:</source>
      <translation>&amp;Bava textu:</translation>
    </message>
    <message>
      <source>Colu&amp;mns:</source>
      <translation>&amp;Sloupce:</translation>
    </message>
    <message>
      <source>&amp;Gap:</source>
      <translation>O&amp;dstup:</translation>
    </message>
    <message>
      <source>&amp;Line Color:</source>
      <translation>Ba&amp;rva čáry:</translation>
    </message>
    <message>
      <source>&amp;Shading:</source>
      <translation>&amp;Stín:</translation>
    </message>
    <message>
      <source>&amp;Fill Color:</source>
      <translation>&amp;Barva výplně:</translation>
    </message>
    <message>
      <source>S&amp;hading:</source>
      <translation>Stí&amp;n:</translation>
    </message>
    <message>
      <source>&amp;Type of Line:</source>
      <translation>&amp;Typ čáry:</translation>
    </message>
    <message>
      <source>Line &amp;Width:</source>
      <translation>Šíř&amp;ka čáry:</translation>
    </message>
    <message>
      <source>Mi&amp;nimum:</source>
      <translation>Mi&amp;nimum:</translation>
    </message>
    <message>
      <source>Ma&amp;ximum:</source>
      <translation>&amp;Maximum:</translation>
    </message>
    <message>
      <source>&amp;Stepping:</source>
      <translation>&amp;Krokování:</translation>
    </message>
    <message>
      <source>&amp;Free Scaling</source>
      <translation>Vo&amp;lná změna velikosti</translation>
    </message>
    <message>
      <source>&amp;Horizontal Scaling:</source>
      <translation>&amp;Vodorovné zvětšení:</translation>
    </message>
    <message>
      <source>&amp;Vertical Scaling:</source>
      <translation>V&amp;ertikální zvětšení:</translation>
    </message>
    <message>
      <source>&amp;Scale Picture to Frame Size</source>
      <translation>Změnit velikost &amp;obrázku na rozměr rámu</translation>
    </message>
    <message>
      <source>Keep Aspect &amp;Ratio</source>
      <translation>Dod&amp;ržet poměr stran</translation>
    </message>
    <message>
      <source>F&amp;ill Color:</source>
      <translation>&amp;Barva výplně:</translation>
    </message>
    <message>
      <source>Corn&amp;ers:</source>
      <translation>Ro&amp;hy:</translation>
    </message>
    <message>
      <source>&amp;Rotation:</source>
      <translation>&amp;Rotace:</translation>
    </message>
    <message>
      <source>&amp;Factor:</source>
      <translation>&amp;Faktor:</translation>
    </message>
    <message>
      <source>Sa&amp;ve Contents on Changes</source>
      <translation>Při změně &amp;uložit obsah</translation>
    </message>
    <message>
      <source>Large</source>
      <translation>Velký</translation>
    </message>
    <message>
      <source>Display Pages &amp;Side by Side</source>
      <translation>Zobrazovat &amp;stranu za stranou</translation>
    </message>
    <message>
      <source>Page Colors</source>
      <translation>Barvy strany</translation>
    </message>
    <message>
      <source>&amp;Background:</source>
      <translation>&amp;Pozadí:</translation>
    </message>
    <message>
      <source>&amp;Margins:</source>
      <translation>&amp;Okraje:</translation>
    </message>
    <message>
      <source>Display &amp;Unprintable Area in Margin Color</source>
      <translation>Zo&amp;brazit netisknutelnou oblast barvou okrajů</translation>
    </message>
    <message>
      <source>Use PDF 1.4 &amp;Transparency Features</source>
      <translation>Použí&amp;t vlastnosti průsvitnosti PDF-1.4</translation>
    </message>
    <message>
      <source>&amp;Adjust Display Size</source>
      <translation>Přizpůsobení &amp;velikosti obrazovky</translation>
    </message>
    <message>
      <source>&amp;Name of Executable:</source>
      <translation>Jmé&amp;no spustitelného souboru (programu):</translation>
    </message>
    <message>
      <source>Antialias &amp;Text</source>
      <translation>Vyhlazený &amp;text</translation>
    </message>
    <message>
      <source>Antialias &amp;Graphics</source>
      <translation>Vyhlazená &amp;grafika</translation>
    </message>
    <message>
      <source>Name of &amp;Executable:</source>
      <translation>Jméno &amp;spustitelného souboru (programu):</translation>
    </message>
    <message>
      <source>Clip to Page &amp;Margins</source>
      <translation>Připnout k okrajů&amp;m strany</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Inside:</source>
      <translation>&amp;Uvnitř:</translation>
    </message>
    <message>
      <source>O&amp;utside:</source>
      <translation>&amp;Vnější:</translation>
    </message>
    <message>
      <source>Apply &amp;Under Color Removal</source>
      <translation>Aplikovat tzv. &amp;Under Color Removal</translation>
    </message>
    <message>
      <source>T&amp;emplates:</source>
      <translation>Š&amp;ablony:</translation>
    </message>
    <message>
      <source>Cha&amp;nge...</source>
      <translation>&amp;Změnit...</translation>
    </message>
    <message>
      <source>Additional Directory for Document Templates</source>
      <translation>Uživatelem definovaný adresář šablon</translation>
    </message>
    <message>
      <source>Apply &amp;Factor</source>
      <translation>Použít &amp;faktor</translation>
    </message>
    <message>
      <source>Apply Convex/Concave Factor to change shape of Polygons</source>
      <translation>Aplikovat konvexnost/konkávnost na mnohoúhelník</translation>
    </message>
    <message>
      <source>A negative value will make the polygon concave (or star shaped),
 a positive value will make it convex</source>
      <translation>Záporná hodnota nastaví mnohoúhelník jako 
konkávní (nebo s hranami do hvězdy), kladná konvexní</translation>
    </message>
    <message>
      <source>A way of switching off some of the gray shades which are composed
of cyan, yellow and magenta and using black instead.
UCR most affects parts of images which are neutral and/or dark tones
which are close to the gray. Use of this may improve printing some images
and some experimentation and testing is need on a case by case basis.
UCR reduces the possibility of over saturation with CMY inks.</source>
      <translation>UCR - under color removal - odstranění přebytečné barvy, která by 
způsobila rozpíjení (při přílišné saturaci papíru barvou) nebo trhání 
barvy při několika vrstvém (např. barevném) laserovém tisku.
Viz. např. http://www.typo.cz/_pismo/pis-tech-post.html
a jiné.</translation>
    </message>
    <message>
      <source>Executive</source>
      <translation>Executive</translation>
    </message>
    <message>
      <source>Folio</source>
      <translation>Folio</translation>
    </message>
    <message>
      <source>Ledger</source>
      <translation>Ledger</translation>
    </message>
    <message>
      <source>Legal</source>
      <translation>Legal</translation>
    </message>
    <message>
      <source>Letter</source>
      <translation>Letter</translation>
    </message>
    <message>
      <source>Tabloid</source>
      <translation>Tabloid</translation>
    </message>
  </context>
  <context>
    <name>QColorDialog</name>
    <message>
      <source>Hu&amp;e:</source>
      <translation>&amp;Odstín:</translation>
    </message>
    <message>
      <source>&amp;Sat:</source>
      <translation>&amp;Sytost:</translation>
    </message>
    <message>
      <source>&amp;Val:</source>
      <translation>&amp;Hod:</translation>
    </message>
    <message>
      <source>&amp;Red:</source>
      <translation>Če&amp;rvená:</translation>
    </message>
    <message>
      <source>&amp;Green:</source>
      <translation>Ze&amp;lená:</translation>
    </message>
    <message>
      <source>Bl&amp;ue:</source>
      <translation>Mo&amp;drá:</translation>
    </message>
    <message>
      <source>A&amp;lpha channel:</source>
      <translation>&amp;Alfa kanál:</translation>
    </message>
    <message>
      <source>&amp;Basic colors</source>
      <translation>&amp;Základní barvy</translation>
    </message>
    <message>
      <source>&amp;Custom colors</source>
      <translation>&amp;Vlastní barvy</translation>
    </message>
    <message>
      <source>&amp;Define Custom Colors >></source>
      <translation>&amp;Definovat vlastní barvy >></translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>&amp;Add to Custom Colors</source>
      <translation>&amp;Přidat k vlastním barvám</translation>
    </message>
    <message>
      <source>Select color</source>
      <translation>Výběr barvy</translation>
    </message>
  </context>
  <context>
    <name>QFileDialog</name>
    <message>
      <source>Copy or Move a File</source>
      <translation>Kopírovat nebo přesunout soubor</translation>
    </message>
    <message>
      <source>Read: %1</source>
      <translation>Číst: %1</translation>
    </message>
    <message>
      <source>Write: %1</source>
      <translation>Zapsat: %1</translation>
    </message>
    <message>
      <source>File &amp;name:</source>
      <translation>Jmé&amp;no souboru:</translation>
    </message>
    <message>
      <source>File &amp;type:</source>
      <translation>&amp;Typ souboru:</translation>
    </message>
    <message>
      <source>One directory up</source>
      <translation>O adresář výš</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>All Files (*)</source>
      <translation>Včechny soubory (*)</translation>
    </message>
    <message>
      <source>Name</source>
      <translation>Jméno</translation>
    </message>
    <message>
      <source>Size</source>
      <translation>Velikost</translation>
    </message>
    <message>
      <source>Type</source>
      <translation>Typ</translation>
    </message>
    <message>
      <source>Date</source>
      <translation>Datum</translation>
    </message>
    <message>
      <source>Attributes</source>
      <translation>Atributy</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Look &amp;in:</source>
      <translation>Nahlédn&amp;i do:</translation>
    </message>
    <message>
      <source>Back</source>
      <translation>Zpět</translation>
    </message>
    <message>
      <source>Create New Folder</source>
      <translation>Vytvořit nový adresář</translation>
    </message>
    <message>
      <source>List View</source>
      <translation>Pohled seznam</translation>
    </message>
    <message>
      <source>Detail View</source>
      <translation>Podrobný pohled</translation>
    </message>
    <message>
      <source>Preview File Info</source>
      <translation>Ukázat informace o souboru</translation>
    </message>
    <message>
      <source>Preview File Contents</source>
      <translation>Ukázat obsah souboru</translation>
    </message>
    <message>
      <source>Read-write</source>
      <translation>Číst-psát</translation>
    </message>
    <message>
      <source>Read-only</source>
      <translation>Jen číst</translation>
    </message>
    <message>
      <source>Write-only</source>
      <translation>Jen psát</translation>
    </message>
    <message>
      <source>Inaccessible</source>
      <translation>Nepřístupný</translation>
    </message>
    <message>
      <source>Symlink to File</source>
      <translation>Symbolický odkaz na soubor</translation>
    </message>
    <message>
      <source>Symlink to Directory</source>
      <translation>Symbolický odkaz na adresář</translation>
    </message>
    <message>
      <source>Symlink to Special</source>
      <translation>Symbolický odkaz na speciální</translation>
    </message>
    <message>
      <source>File</source>
      <translation>Soubor</translation>
    </message>
    <message>
      <source>Dir</source>
      <translation>Adresář</translation>
    </message>
    <message>
      <source>Special</source>
      <translation>Speciální</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Save As</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>&amp;Open</source>
      <translation>&amp;Otevřít</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>&amp;Rename</source>
      <translation>&amp;Přejmenovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>R&amp;eload</source>
      <translation>&amp;Obnovit</translation>
    </message>
    <message>
      <source>Sort by &amp;Name</source>
      <translation>Seřadit podle &amp;jména</translation>
    </message>
    <message>
      <source>Sort by &amp;Size</source>
      <translation>Seřadit podle &amp;velikosti</translation>
    </message>
    <message>
      <source>Sort by &amp;Date</source>
      <translation>Seřadit podle &amp;data</translation>
    </message>
    <message>
      <source>&amp;Unsorted</source>
      <translation>&amp;Nesetříděno</translation>
    </message>
    <message>
      <source>Sort</source>
      <translation>Řazení</translation>
    </message>
    <message>
      <source>Show &amp;hidden files</source>
      <translation>Zobrazit s&amp;kryté soubory</translation>
    </message>
    <message>
      <source>the file</source>
      <translation>soubor</translation>
    </message>
    <message>
      <source>the directory</source>
      <translation>adresář</translation>
    </message>
    <message>
      <source>the symlink</source>
      <translation>symbolický odkaz</translation>
    </message>
    <message>
      <source>Delete %1</source>
      <translation>Smazat %1</translation>
    </message>
    <message>
      <source>&lt;qt>Are you sure you wish to delete %1 &quot;%2&quot;?&lt;/qt></source>
      <translation>&lt;qt>Opravdu chcete smazat %1 &quot;%2&quot;?&lt;/qt></translation>
    </message>
    <message>
      <source>&amp;Yes</source>
      <translation>&amp;Ano</translation>
    </message>
    <message>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <source>New Folder 1</source>
      <translation>Nový adresář 1</translation>
    </message>
    <message>
      <source>New Folder</source>
      <translation>Nový adresář</translation>
    </message>
    <message>
      <source>New Folder %1</source>
      <translation>Nový adresář %1</translation>
    </message>
    <message>
      <source>Find Directory</source>
      <translation>Najít adresář</translation>
    </message>
    <message>
      <source>Directories</source>
      <translation>Adresáře</translation>
    </message>
    <message>
      <source>Save</source>
      <translation>Uložit</translation>
    </message>
    <message>
      <source>Error</source>
      <translation>Chyba</translation>
    </message>
    <message>
      <source>%1
File not found.
Check path and filename.</source>
      <translation>%1(new line)
Soubor nenalezen.(new line)
Zkontrolujte cestu a název souboru.</translation>
    </message>
    <message>
      <source>All Files (*.*)</source>
      <translation>Včechny soubory (*.*)</translation>
    </message>
    <message>
      <source>Select a Directory</source>
      <translation>Vybrat adresář</translation>
    </message>
    <message>
      <source>Directory:</source>
      <translation>Adresář:</translation>
    </message>
  </context>
  <context>
    <name>QFontDialog</name>
    <message>
      <source>&amp;Font</source>
      <translation>&amp;Písmo</translation>
    </message>
    <message>
      <source>Font st&amp;yle</source>
      <translation>S&amp;tyl písma</translation>
    </message>
    <message>
      <source>&amp;Size</source>
      <translation>&amp;Velikost</translation>
    </message>
    <message>
      <source>Effects</source>
      <translation>Efekty</translation>
    </message>
    <message>
      <source>Stri&amp;keout</source>
      <translation>Přešk&amp;rtnuté</translation>
    </message>
    <message>
      <source>&amp;Underline</source>
      <translation>Po&amp;dtržené</translation>
    </message>
    <message>
      <source>&amp;Color</source>
      <translation>&amp;Barva</translation>
    </message>
    <message>
      <source>Sample</source>
      <translation>Příklad</translation>
    </message>
    <message>
      <source>Scr&amp;ipt</source>
      <translation>Skr&amp;ipt</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Apply</source>
      <translation>Použít</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Close</source>
      <translation>Zavřít</translation>
    </message>
    <message>
      <source>Select Font</source>
      <translation>Vybrat písmo</translation>
    </message>
  </context>
  <context>
    <name>QLineEdit</name>
    <message>
      <source>Clear</source>
      <translation>Vymazat</translation>
    </message>
    <message>
      <source>Select All</source>
      <translation>Vybrat vše</translation>
    </message>
    <message>
      <source>&amp;Undo</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <source>&amp;Redo</source>
      <translation>&amp;Vpřed</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
  </context>
  <context>
    <name>QMainWindow</name>
    <message>
      <source>Line up</source>
      <translation>Vyrovnat</translation>
    </message>
    <message>
      <source>Customize...</source>
      <translation>Upravit...</translation>
    </message>
  </context>
  <context>
    <name>QMessageBox</name>
    <message>
      <source>&lt;h3>About Qt&lt;/h3>&lt;p>This program uses Qt version %1.&lt;/p>&lt;p>Qt is a C++ toolkit for multiplatform GUI &amp;amp; application development.&lt;/p>&lt;p>Qt provides single-source portability across MS&amp;nbsp;Windows, Mac&amp;nbsp;OS&amp;nbsp;X, Linux, and all major commercial Unix variants.&lt;br>Qt is also available for embedded devices.&lt;/p>&lt;p>Qt is a Trolltech product. See &lt;tt>http://www.trolltech.com/qt/&lt;/tt> for more information.&lt;/p></source>
      <translation>&lt;h3>O Qt&lt;/h3>&lt;p>Tento program používá Qt verze %1.&lt;/p>&lt;p>Qt je C++ knihovna určená pro vývoj multiplatformních nejen GUI aplikací.&lt;/p>&lt;p>Qt zajišťuje přenositelnost jediného zdrojového kódu na MS&amp;nbsp;Windows, Mac&amp;nbsp;OS&amp;nbsp;X, Linux, a všechny hlavní varianty komerčních Unixů.&lt;br>Qt je také k dispozici pro jednoúčelová zařízení (embedded devices).&lt;/p>&lt;p>Qt je produktem firmy Trolltech. Více informací získáte na &lt;tt>http://www.trolltech.com/qt/&lt;/tt>.&lt;/p></translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Do you really want to overwrite the File:
%1 ?</source>
      <translation>Opravdu chcete přepsat soubor:
%1 ?</translation>
    </message>
    <message>
      <source>Initializing...</source>
      <translation>Inicializace...</translation>
    </message>
    <message>
      <source>Document</source>
      <translation>Dokument</translation>
    </message>
    <message>
      <source>Background</source>
      <translation>Pozadí</translation>
    </message>
    <message>
      <source>Print Preview</source>
      <translation>Ukázka před tiskem</translation>
    </message>
    <message>
      <source>Online Reference</source>
      <translation>On-line reference</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Python Scripts (*.py);; All Files (*)</source>
      <translation>Python skripty (*.py);; All Files (*)</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>SVG-Images (*.svg *.svgz);;All Files (*)</source>
      <translation>SVG-obrázky (*.svg *.svgz);;All Files (*)</translation>
    </message>
    <message>
      <source>SVG-Images (*.svg);;All Files (*)</source>
      <translation>SVG-obrázky (*.svg);;All Files (*)</translation>
    </message>
    <message>
      <source>Yes</source>
      <translation>Ano</translation>
    </message>
    <message>
      <source>No</source>
      <translation>Ne</translation>
    </message>
    <message>
      <source>S&amp;cript</source>
      <translation>S&amp;kript</translation>
    </message>
    <message>
      <source>Save as Image</source>
      <translation>Uložit jako obrázek</translation>
    </message>
    <message>
      <source>Error writting the output file(s).</source>
      <translation>Chyba při zápisu souboru.</translation>
    </message>
    <message>
      <source>Error writing the output file(s).</source>
      <translation>Chyba při zápisu souboru.</translation>
    </message>
    <message>
      <source>Export successful.</source>
      <translation>Úspěšný export.</translation>
    </message>
    <message>
      <source>File exists. Overwrite?</source>
      <translation>Soubor existuje. Přepsat?</translation>
    </message>
    <message>
      <source>exists already. Overwrite?</source>
      <translation>už existuje. Přepsat?</translation>
    </message>
    <message>
      <source>Yes all</source>
      <translation>Ano všem</translation>
    </message>
    <message>
      <source>&amp;Fonts Preview</source>
      <translation>&amp;Náhled písem</translation>
    </message>
    <message>
      <source>&amp;Insert Special</source>
      <translation>&amp;Vložit speciální</translation>
    </message>
    <message>
      <source>New &amp;from Template...</source>
      <translation>No&amp;vé ze šablony...</translation>
    </message>
    <message>
      <source>Newsletters</source>
      <translation>Věstníky</translation>
    </message>
    <message>
      <source>Brochures</source>
      <translation>Brožury</translation>
    </message>
    <message>
      <source>Catalogs</source>
      <translation>Katalogy</translation>
    </message>
    <message>
      <source>Flyers</source>
      <translation>Letáky</translation>
    </message>
    <message>
      <source>Signs</source>
      <translation>Pokyny</translation>
    </message>
    <message>
      <source>Cards</source>
      <translation>Karty</translation>
    </message>
    <message>
      <source>Letterheads</source>
      <translation>Dopisy</translation>
    </message>
    <message>
      <source>Envelopes</source>
      <translation>Obálky</translation>
    </message>
    <message>
      <source>Business Cards</source>
      <translation>Vizitky</translation>
    </message>
    <message>
      <source>Calendars</source>
      <translation>Kalendáře</translation>
    </message>
    <message>
      <source>Advertisements</source>
      <translation>Inzeráty</translation>
    </message>
    <message>
      <source>Labels</source>
      <translation>Štítky</translation>
    </message>
    <message>
      <source>Menus</source>
      <translation>Nabídky (Menu)</translation>
    </message>
    <message>
      <source>Programs</source>
      <translation>Programy</translation>
    </message>
    <message>
      <source>PDF Forms</source>
      <translation>PDF formuláře</translation>
    </message>
    <message>
      <source>PDF Presentations</source>
      <translation>PDF prezentace</translation>
    </message>
    <message>
      <source>Magazines</source>
      <translation>Časopisy</translation>
    </message>
    <message>
      <source>Posters</source>
      <translation>Plakáty</translation>
    </message>
    <message>
      <source>Announcements</source>
      <translation>Oznámení</translation>
    </message>
    <message>
      <source>Text Documents</source>
      <translation>Textové dokumenty</translation>
    </message>
    <message>
      <source>Folds</source>
      <translation>Složky</translation>
    </message>
    <message>
      <source>Own Templates</source>
      <translation>Vlastní šablony</translation>
    </message>
    <message>
      <source>Save as &amp;Image...</source>
      <translation>Uložit jako &amp;obrázek...</translation>
    </message>
    <message>
      <source>Print Previe&amp;w</source>
      <translation>Ukázka pře&amp;d tiskem</translation>
    </message>
    <message>
      <source>Import &amp;EPS/PS...</source>
      <translation>Import &amp;EPS/PS...</translation>
    </message>
    <message>
      <source>All Supported Formats (*.eps *.EPS *.ps *.PS);;</source>
      <translation>Všechny podporované formáty (*.eps *.EPS *.ps *.PS);;</translation>
    </message>
    <message>
      <source>All Files (*)</source>
      <translation>Včechny soubory (*)</translation>
    </message>
    <message>
      <source>Save as &amp;Template...</source>
      <translation>Uložit jako ša&amp;blonu...</translation>
    </message>
    <message>
      <source>S&amp;cripter Manual...</source>
      <translation>Manuál &amp;Scripteru...</translation>
    </message>
    <message>
      <source>&amp;Scribus Scripts</source>
      <translation>&amp;Scribus skripty</translation>
    </message>
    <message>
      <source>&amp;Execute Script...</source>
      <translation>&amp;Vykonat skript...</translation>
    </message>
    <message>
      <source>&amp;Recent Scripts</source>
      <translation>&amp;Použité skripty</translation>
    </message>
    <message>
      <source>Show &amp;Console</source>
      <translation>Ukázat &amp;konzoli</translation>
    </message>
    <message>
      <source>Save Page as &amp;SVG...</source>
      <translation>Uložit stranu jako &amp;SVG...</translation>
    </message>
    <message>
      <source>Import &amp;SVG...</source>
      <translation>Import &amp;SVG...</translation>
    </message>
    <message>
      <source>Importing text</source>
      <translation>Importovat text</translation>
    </message>
    <message>
      <source>All Supported Formats</source>
      <translation>Všechny podporované formáty</translation>
    </message>
    <message>
      <source>HTML Files</source>
      <translation>HTML soubory</translation>
    </message>
    <message>
      <source>html</source>
      <translation>html</translation>
    </message>
    <message>
      <source>Text Files</source>
      <translation>Textové soubory</translation>
    </message>
    <message>
      <source>Comma Separated Value Files</source>
      <translation>Soubory CSV (čárkou oddělěné hodnoty)</translation>
    </message>
    <message>
      <source>CSV_data</source>
      <translation>CSV_data</translation>
    </message>
    <message>
      <source>CSV_header</source>
      <translation>CSV_hlavička</translation>
    </message>
    <message>
      <source>Font %1 is broken, discarding it</source>
      <translation>Písmo %1 je poškozené. Bude vyřazeno</translation>
    </message>
    <message>
      <source>Template: </source>
      <translation>Šablona:</translation>
    </message>
    <message>
      <source>
External Links
</source>
      <translation>
Odkazy ven
</translation>
    </message>
    <message>
      <source>Text Filters</source>
      <translation>Textové filtry</translation>
    </message>
    <message>
      <source>Media Cases</source>
      <translation>Obaly médií</translation>
    </message>
    <message>
      <source>Albanian</source>
      <translation>Albánština</translation>
    </message>
    <message>
      <source>Basque</source>
      <translation>Baskitština</translation>
    </message>
    <message>
      <source>Bulgarian</source>
      <translation>Bulharština</translation>
    </message>
    <message>
      <source>Brazilian</source>
      <translation>Brazilština</translation>
    </message>
    <message>
      <source>Catalan</source>
      <translation>Katalánština</translation>
    </message>
    <message>
      <source>Chinese</source>
      <translation>Čínština</translation>
    </message>
    <message>
      <source>Czech</source>
      <translation>Čeština</translation>
    </message>
    <message>
      <source>Danish</source>
      <translation>Dánština</translation>
    </message>
    <message>
      <source>Dutch</source>
      <translation>Holandština</translation>
    </message>
    <message>
      <source>English</source>
      <translation>Angličtina</translation>
    </message>
    <message>
      <source>English (British)</source>
      <translation>Angličtina (Britská)</translation>
    </message>
    <message>
      <source>Esperanto</source>
      <translation>Esperanto</translation>
    </message>
    <message>
      <source>German</source>
      <translation>Němčina</translation>
    </message>
    <message>
      <source>Finnish</source>
      <translation>Finština</translation>
    </message>
    <message>
      <source>French</source>
      <translation>Francouzština</translation>
    </message>
    <message>
      <source>Galician</source>
      <translation>Galština</translation>
    </message>
    <message>
      <source>Greek</source>
      <translation>Řečtina</translation>
    </message>
    <message>
      <source>Hungarian</source>
      <translation>Maďarština</translation>
    </message>
    <message>
      <source>Indonesian</source>
      <translation>Indonéský</translation>
    </message>
    <message>
      <source>Italian</source>
      <translation>Italština</translation>
    </message>
    <message>
      <source>Korean</source>
      <translation>Korejština</translation>
    </message>
    <message>
      <source>Lithuanian</source>
      <translation>Litevština</translation>
    </message>
    <message>
      <source>Norwegian (Bokmaal)</source>
      <translation>Norština (Bokmaal)</translation>
    </message>
    <message>
      <source>Norwegian (Nnyorsk)</source>
      <translation>Norština (Nnyorsk)</translation>
    </message>
    <message>
      <source>Norwegian</source>
      <translation>Norština</translation>
    </message>
    <message>
      <source>Polish</source>
      <translation>Polština</translation>
    </message>
    <message>
      <source>Russian</source>
      <translation>Ruština</translation>
    </message>
    <message>
      <source>Swedish</source>
      <translation>Švédština</translation>
    </message>
    <message>
      <source>Spanish</source>
      <translation>Španělština</translation>
    </message>
    <message>
      <source>Spanish (Latin)</source>
      <translation>Španělština (Latin)</translation>
    </message>
    <message>
      <source>Slovak</source>
      <translation>Slovenština</translation>
    </message>
    <message>
      <source>Slovenian</source>
      <translation>Slovinština</translation>
    </message>
    <message>
      <source>Serbian</source>
      <translation>Srbština</translation>
    </message>
    <message>
      <source>Tried to set progress > maximum progress</source>
      <translation>Nelze nastavit větší progres než je maximální</translation>
    </message>
    <message>
      <source>&amp;About Script...</source>
      <translation>&amp;O skriptu...</translation>
    </message>
    <message>
      <source>About Script</source>
      <translation>O skriptu</translation>
    </message>
    <message>
      <source>Cannot get font size of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat velikost písma z netextového rámce.</translation>
    </message>
    <message>
      <source>Cannot get font of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat písmo z netextového rámce.</translation>
    </message>
    <message>
      <source>Cannot get text size of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat velikost textu z netextového rámce.</translation>
    </message>
    <message>
      <source>Cannot get column count of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat počet sloupců z netextového rámce.</translation>
    </message>
    <message>
      <source>Cannot get line space of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat řádkování z netextového rámu.</translation>
    </message>
    <message>
      <source>Cannot get column gap of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat odstup sloupců z netextového rámu.</translation>
    </message>
    <message>
      <source>Cannot get text of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze získat text z netextového rámu.</translation>
    </message>
    <message>
      <source>Cannot set text of non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze vložit text do netextového rámu.</translation>
    </message>
    <message>
      <source>Cannot insert text into non-text frame.</source>
      <comment>python error</comment>
      <translation>Nelze vložit text do netextového rámu.</translation>
    </message>
    <message>
      <source>Insert index out of bounds</source>
      <comment>python error</comment>
      <translation>Pozice je mimo povolené hranice</translation>
    </message>
    <message>
      <source>Alignment out of range. Use one of the scribus.ALIGN* constants.</source>
      <comment>python error</comment>
      <translation>Hodnota zarovnání je mimo povolený rozsah. Použijte jednu z předdefinovaných konstant scribus.ALIGN*.</translation>
    </message>
    <message>
      <source>Can't set text alignment on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit typ zarovnání netextového rámce</translation>
    </message>
    <message>
      <source>Font size out of bounds - must be 1 &lt;= size &lt;= 512</source>
      <comment>python error</comment>
      <translation>Velikost písma mimo povolený rozsah. Musí být mezi 1 a 512</translation>
    </message>
    <message>
      <source>Can't set font size on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nasatvit velikost písma netextového rámu</translation>
    </message>
    <message>
      <source>Can't set font on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit písmo netextového rámu</translation>
    </message>
    <message>
      <source>Font not found</source>
      <comment>python error</comment>
      <translation>Písmo nenalezeno</translation>
    </message>
    <message>
      <source>Line space out of bounds, must be >= 0.1</source>
      <comment>python error</comment>
      <translation>Velikost řádkování je mimo povolený rozsah. Musí být větší než 0</translation>
    </message>
    <message>
      <source>Can't line spacing on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit řádkovéní netextového rámce</translation>
    </message>
    <message>
      <source>Column gap out of bounds, must be positive</source>
      <comment>python error</comment>
      <translation>Mezisloupcová mezera nesmí být negativní</translation>
    </message>
    <message>
      <source>Can't column gap on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit mezisloupcovou mezeru netextového rámu</translation>
    </message>
    <message>
      <source>Column count out of bounds, must be > 1</source>
      <comment>python error</comment>
      <translation>Počet slupců je mimo povolený rozsah. Musí být větší než 1</translation>
    </message>
    <message>
      <source>Can't number of columns on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit počet sloupců netextového rámce</translation>
    </message>
    <message>
      <source>Selection index out of bounds</source>
      <comment>python error</comment>
      <translation>Pozice výběru mimo povolené hranice</translation>
    </message>
    <message>
      <source>Can't select text in a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze vybrat text v netextovém rámce</translation>
    </message>
    <message>
      <source>Can't delete text from a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze smazat text z netextového rámce</translation>
    </message>
    <message>
      <source>Can't set text fill on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit výplň textu netextového rámce</translation>
    </message>
    <message>
      <source>Can't set text stroke on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit obrys netextového rámce</translation>
    </message>
    <message>
      <source>Can't set text shade on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit stín netextového rámce</translation>
    </message>
    <message>
      <source>Can only link text frames</source>
      <comment>python error</comment>
      <translation>Pouze textové rámce se mohou zřetězit</translation>
    </message>
    <message>
      <source>Target frame must be empty</source>
      <comment>python error</comment>
      <translation>Cílový rámec musí být prázdný</translation>
    </message>
    <message>
      <source>Target frame links to another frame</source>
      <comment>python error</comment>
      <translation>Text cilového rámce už poračuje v rámci jiném</translation>
    </message>
    <message>
      <source>Target frame is linked to by another frame</source>
      <comment>python error</comment>
      <translation>Cílový rámec už je zřetězený</translation>
    </message>
    <message>
      <source>Source and target are the same object</source>
      <comment>python error</comment>
      <translation>Oba rámce jsou stejný objekt</translation>
    </message>
    <message>
      <source>Can't unlink a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze zrušit zřetězení netextového rámce</translation>
    </message>
    <message>
      <source>Object is not a linked text frame, can't unlink.</source>
      <comment>python error</comment>
      <translation>Objekt není zřetězený textový rámec, proto nelze řetězeí zrušit.</translation>
    </message>
    <message>
      <source>Object the last frame in a series, can't unlink. Unlink the previous frame instead.</source>
      <comment>python error</comment>
      <translation>Objektu na posledním místě nelze zrušit zřetězení. Použijte místo něj předchozí rámec.</translation>
    </message>
    <message>
      <source>Can't convert a non-text frame to outlines</source>
      <comment>python error</comment>
      <translation>Nelze převést netextový rámec na křivky</translation>
    </message>
    <message>
      <source>Failed to open document</source>
      <comment>python error</comment>
      <translation>Chyba při otvírání dokumentu</translation>
    </message>
    <message>
      <source>Failed to save document</source>
      <comment>python error</comment>
      <translation>Chyba při ukládání dokumentu</translation>
    </message>
    <message>
      <source>Unit out of range. Use one of the scribus.UNIT_* constants.</source>
      <comment>python error</comment>
      <translation>Jednotka mimo povolený rozsah. Použijte jednu z předdefinovanýcj konstant scribus.UNIT*.</translation>
    </message>
    <message>
      <source>Target is not an image frame.</source>
      <comment>python error</comment>
      <translation>Cíl není obrázkový rámec.</translation>
    </message>
    <message>
      <source>Can't scale by 0%</source>
      <comment>python error</comment>
      <translation>Nelze měnit velikost pomocí 0%</translation>
    </message>
    <message>
      <source>Can't render an empty sample</source>
      <comment>python error</comment>
      <translation>Nelze vytvořit prázdný náhled</translation>
    </message>
    <message>
      <source>Can't save to a blank filename</source>
      <comment>python error</comment>
      <translation>Nelze ukládat bez názvu souboru</translation>
    </message>
    <message>
      <source>Can't have an empty layer name</source>
      <comment>python error</comment>
      <translation>Nelze vytvořit vrstvu s prázdným jménem</translation>
    </message>
    <message>
      <source>Layer not found</source>
      <comment>python error</comment>
      <translation>Vrstva nenalezena</translation>
    </message>
    <message>
      <source>Can't remove the last layer</source>
      <comment>python error</comment>
      <translation>Nelze odstranit poslední vrstvu</translation>
    </message>
    <message>
      <source>Can't create layer without a name</source>
      <comment>python error</comment>
      <translation>Nelze vytvořit vrstvu beze jména</translation>
    </message>
    <message>
      <source>An object with the requested name already exists</source>
      <comment>python error</comment>
      <translation>Objekt se zadaným názvem už existuje</translation>
    </message>
    <message>
      <source>Point list must contain at least two points (four values)</source>
      <comment>python error</comment>
      <translation>Seznam musí obsahovat alespoň dva body (čtyři hodnoty)</translation>
    </message>
    <message>
      <source>Point list must contain an even number of values</source>
      <comment>python error</comment>
      <translation>Seznam musí obsahovat sudý počet hodnot</translation>
    </message>
    <message>
      <source>Point list must contain at least three points (six values)</source>
      <comment>python error</comment>
      <translation>Seznam musí obsahovat alespoň tři body (šest hodnot)</translation>
    </message>
    <message>
      <source>Point list must contain at least four points (eight values)</source>
      <comment>python error</comment>
      <translation>SeSeznam musí obsahovat alespoň čtyři body (osm hodnot)</translation>
    </message>
    <message>
      <source>Point list must have a multiple of six values</source>
      <comment>python error</comment>
      <translation>Seznam musí obsahovat násobek šesti položek</translation>
    </message>
    <message>
      <source>Object not found</source>
      <comment>python error</comment>
      <translation>Objekt nenalezen</translation>
    </message>
    <message>
      <source>Style not found</source>
      <comment>python error</comment>
      <translation>Styl nenalezen</translation>
    </message>
    <message>
      <source>Can't set style on a non-text frame</source>
      <comment>python error</comment>
      <translation>Nelze nastavit styl netextového rámce</translation>
    </message>
    <message>
      <source>Failed to save EPS</source>
      <comment>python error</comment>
      <translation>Chyba při ukládání EPS</translation>
    </message>
    <message>
      <source>Page number out of range</source>
      <comment>python error</comment>
      <translation>Číslo strany je mimo povolený rozsah</translation>
    </message>
    <message>
      <source>argument is not list: must be list of float values</source>
      <comment>python error</comment>
      <translation>parametr není seznam: musí být seznam s float hodnotami</translation>
    </message>
    <message>
      <source>argument contains non-numeric values: must be list of float values</source>
      <comment>python error</comment>
      <translation>parametr obsahuje nečíselné hodnoty: musí být seznam s float hodnotami</translation>
    </message>
    <message>
      <source>Line width out of bounds, must be 0 &lt;= line_width &lt;= 12</source>
      <comment>python error</comment>
      <translation>Šířka čáry mimo povolený rozsah: &lt;0; 12></translation>
    </message>
    <message>
      <source>Line shade out of bounds, must be 0 &lt;= shade &lt;= 100</source>
      <comment>python error</comment>
      <translation>Stín čáry mimo povolený rozsah: &lt;0; 100></translation>
    </message>
    <message>
      <source>Fill shade out of bounds, must be 0 &lt;= shade &lt;= 100</source>
      <comment>python error</comment>
      <translation>Stín mimo povolený rozsah: &lt;0; 100></translation>
    </message>
    <message>
      <source>Corner radius must be a positive number.</source>
      <comment>python error</comment>
      <translation>Úhel rohu nesmí být negativní číslo.</translation>
    </message>
    <message>
      <source>Line style not found</source>
      <comment>python error</comment>
      <translation>Styl čáry nenalezen</translation>
    </message>
    <message>
      <source>Cannot get a color with an empty name.</source>
      <comment>python error</comment>
      <translation>Nelze získat barvu s prázdným jménem.</translation>
    </message>
    <message>
      <source>Color not found</source>
      <comment>python error</comment>
      <translation>Barva nenalezena</translation>
    </message>
    <message>
      <source>Cannot change a color with an empty name.</source>
      <comment>python error</comment>
      <translation>Nelze změnit barvu s prázdným jménem.</translation>
    </message>
    <message>
      <source>Color not found in document</source>
      <comment>python error</comment>
      <translation>Barva není v dokumentu nalezena</translation>
    </message>
    <message>
      <source>Color not found in default colors</source>
      <comment>python error</comment>
      <translation>Barva není nalezena v implicitních barvách</translation>
    </message>
    <message>
      <source>Cannot create a color with an empty name.</source>
      <comment>python error</comment>
      <translation>Nelze vytvořit barvu s prázdným jménem.</translation>
    </message>
    <message>
      <source>Cannot delete a color with an empty name.</source>
      <comment>python error</comment>
      <translation>Nelze smazat barvu s prázdným jménem.</translation>
    </message>
    <message>
      <source>Cannot replace a color with an empty name.</source>
      <comment>python error</comment>
      <translation>Nelze nahradit barvu s prázdným jménem.</translation>
    </message>
    <message>
      <source>Import &amp;OpenOffice.org Draw...</source>
      <translation>Import OpenOffice.org &amp;Draw...</translation>
    </message>
    <message>
      <source>OpenOffice.org Draw (*.sxd);;All Files (*)</source>
      <translation>OpenOffice.org Draw (*.sxd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>OpenOffice.org Writer Documents</source>
      <translation>OpenOffice.o Writer dokumenty</translation>
    </message>
    <message>
      <source>Scribus Python interface module
This module is the Python interface for Scribus. It provides functions
to control scribus and to manipulate objects on the canvas. Each
function is documented individually below.
A few things are common across most of the interface.
Most functions operate on frames. Frames are identified by their name,
a string - they are not real Python objects. Many functions take an
optional (non-keyword) parameter, a frame name.
Many exceptions are also common across most functions. These are
not currently documented in the docstring for each function.
    - Many functions will raise a NoDocOpenError if you try to use them
      without a document to operate on.
    - If you do not pass a frame name to a function that requires one,
      the function will use the currently selected frame, if any, or
      raise a NoValidObjectError if it can't find anything to operate
      on.
    - Many functions will raise WrongFrameTypeError if you try to use them
      on a frame type that they do not make sense with. For example, setting
      the text colour on a graphics frame doesn't make sense, and will result
      in this exception being raised.
    - Errors resulting from calls to the underlying Python API will be
      passed through unaltered. As such, the list of exceptions thrown by
      any function as provided here and in its docstring is incomplete.
Details of what exceptions each function may throw are provided on the
function's documentation.
</source>
      <translation>Scripter - Python modul programu Scribus
Scripter je rozhraní jazyka Python programu Scribus. Umožňuje ovládat Scribus a manipulovat
s objekty v dokumentu. Všechny dostupné třídy, procedury, funkce a konstanty jsou popsány dále.
Několik věci platí v celém Scripteru. Většina funkčnosti pracuje s rámy. Rámce jsou identifikovány
svým jménem - textovým řetězcem (není Python objektem). Některé funkce akceptují volitelný
parametr, t.j. jméno rámce. Některé obecnější výjimky mohou být vyvolány v různých funkcích,
ale zatím nejsou dokumentovány v nápovědě jednotlivých funkcí.
    - Mnoho funkcí vyvolá NoDocOpenError, jestliže je zavoláte a nemáte otevřený žádný dokument.
    - Jestliže nepoužijete jméno rámce jako parametr, funkce zkusí nejít vybraný objekt. Pokud
      nenalezne, vyvolá NoValidObjectError.
    - Funkce vyvolá WrongFrameTypeError, jestliže bude zpracovávat rámec, se kterým operace
      nebude dávat smysl. Např. nastavení barvy textu obrázkovému rámci smysl nedává, takže je
      výjimka vyvolána.
    - Chyby a výjimky, které vzniknou v ostatních Python modulech, budou předány interpreteru
      beze změny, takže vyjmenované výjimky v dokumentaci Scripteru nejsou ani zdaleka kompletní.
Detaily a výjimky Scripteru jsou popsány v dokumentaci jednotlivých funkcí.</translation>
    </message>
  </context>
  <context>
    <name>QTextEdit</name>
    <message>
      <source>Clear</source>
      <translation>Vymazat</translation>
    </message>
    <message>
      <source>Select All</source>
      <translation>Vybrat vše</translation>
    </message>
    <message>
      <source>&amp;Undo</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <source>&amp;Redo</source>
      <translation>&amp;Vpřed</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
  </context>
  <context>
    <name>QTitleBar</name>
    <message>
      <source>System Menu</source>
      <translation>Systémová nabídka</translation>
    </message>
    <message>
      <source>Shade</source>
      <translation>Schovat</translation>
    </message>
    <message>
      <source>Unshade</source>
      <translation>Zobrazit</translation>
    </message>
    <message>
      <source>Normalize</source>
      <translation>Normalizovat</translation>
    </message>
    <message>
      <source>Minimize</source>
      <translation>Minimalizovat</translation>
    </message>
    <message>
      <source>Maximize</source>
      <translation>Maximalizovat</translation>
    </message>
    <message>
      <source>Close</source>
      <translation>Zavřít</translation>
    </message>
  </context>
  <context>
    <name>QWorkspace</name>
    <message>
      <source>&amp;Restore</source>
      <translation>&amp;Obnovit</translation>
    </message>
    <message>
      <source>&amp;Move</source>
      <translation>&amp;Přesunout</translation>
    </message>
    <message>
      <source>&amp;Size</source>
      <translation>&amp;Velikost</translation>
    </message>
    <message>
      <source>Mi&amp;nimize</source>
      <translation>Mi&amp;nimalizovat</translation>
    </message>
    <message>
      <source>Ma&amp;ximize</source>
      <translation>Ma&amp;ximalizovat</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>Stay on &amp;Top</source>
      <translation>Zůs&amp;tat navrchu</translation>
    </message>
    <message>
      <source>Minimize</source>
      <translation>Minimalizovat</translation>
    </message>
    <message>
      <source>Restore Down</source>
      <translation>Obnovit původní</translation>
    </message>
    <message>
      <source>Close</source>
      <translation>Zavřít</translation>
    </message>
    <message>
      <source>Sh&amp;ade</source>
      <translation>&amp;Schovat</translation>
    </message>
    <message>
      <source>%1 - [%2]</source>
      <translation>%1 - [%2]</translation>
    </message>
    <message>
      <source>&amp;Unshade</source>
      <translation>Z&amp;obrazit</translation>
    </message>
  </context>
  <context>
    <name>Query</name>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>ReformDoc</name>
    <message>
      <source>Document Setup</source>
      <translation>Nastavení dokumentu</translation>
    </message>
    <message>
      <source>Margin Guides</source>
      <translation>Vodítka okrajů</translation>
    </message>
    <message>
      <source>Enable single or spread based layout</source>
      <translation>Povolit rozložení po jedné nebo po více stranách</translation>
    </message>
    <message>
      <source>Make the first page the left page of the document</source>
      <translation>První strana je levou stranou dokumentu</translation>
    </message>
    <message>
      <source>Distance between the top margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi horním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the bottom margin guide and the edge of the page</source>
      <translation>Vzdálenost mezi dolním vodítkem okraje a okrajem strany</translation>
    </message>
    <message>
      <source>Distance between the left margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi levým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source>Distance between the right margin guide and the edge of the page.
If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
      <translation>Vzdálenost mezi pravým vodítkem okraje a okrajem strany
Jestliže jsou použity protilehlé strany, může tento okraj očetřit vazbu</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>&amp;Top:</source>
      <translation>&amp;Horní:</translation>
    </message>
    <message>
      <source>&amp;Left:</source>
      <translation>&amp;Levý:</translation>
    </message>
    <message>
      <source>&amp;Bottom:</source>
      <translation>&amp;Dolní:</translation>
    </message>
    <message>
      <source>&amp;Right:</source>
      <translation>&amp;Pravý:</translation>
    </message>
    <message>
      <source>&amp;Facing Pages</source>
      <translation>P&amp;rotilehlé stránky (Dvoustrany)</translation>
    </message>
    <message>
      <source>Left &amp;Page First</source>
      <translation>Prv&amp;ní strana vlevo</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>&amp;Inside:</source>
      <translation>&amp;Uvnitř:</translation>
    </message>
    <message>
      <source>&amp;Outside:</source>
      <translation>&amp;Vnější:</translation>
    </message>
    <message>
      <source>Page Size</source>
      <translation>Velikost strany</translation>
    </message>
    <message>
      <source>Size:</source>
      <translation>Velikost:</translation>
    </message>
    <message>
      <source>Custom</source>
      <translation>Vlastní</translation>
    </message>
    <message>
      <source>Orientation:</source>
      <translation>Orientace:</translation>
    </message>
    <message>
      <source>Portrait</source>
      <translation>Na výšku</translation>
    </message>
    <message>
      <source>Landscape</source>
      <translation>Na šířku</translation>
    </message>
    <message>
      <source>Width:</source>
      <translation>Šířka:</translation>
    </message>
    <message>
      <source>Height:</source>
      <translation>Výška:</translation>
    </message>
    <message>
      <source>F&amp;irst Page Number:</source>
      <translation>Čí&amp;slo první strany:</translation>
    </message>
  </context>
  <context>
    <name>SToolBAlign</name>
    <message>
      <source>Style of current paragraph</source>
      <translation>Styl aktuálního odstavce</translation>
    </message>
    <message>
      <source>Style Settings</source>
      <translation>Nastavení stylu</translation>
    </message>
  </context>
  <context>
    <name>SToolBColorF</name>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Color of text fill</source>
      <translation>Barva výplně písma</translation>
    </message>
    <message>
      <source>Saturation of color of text fill</source>
      <translation>Sytost barvy výplně písma</translation>
    </message>
    <message>
      <source>Fill Color Settings</source>
      <translation>Nastavení výplně</translation>
    </message>
  </context>
  <context>
    <name>SToolBColorS</name>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Color of text stroke</source>
      <translation>Barva obrysu písma</translation>
    </message>
    <message>
      <source>Saturation of color of text stroke</source>
      <translation>Sytost barvy obrysu písma</translation>
    </message>
    <message>
      <source>Stroke Color Settings</source>
      <translation>Nastavení barvy obrysu</translation>
    </message>
  </context>
  <context>
    <name>SToolBFont</name>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Font of selected text</source>
      <translation>Písmo vybraného textu</translation>
    </message>
    <message>
      <source>Font Size</source>
      <translation>Velikost písma</translation>
    </message>
    <message>
      <source>Scaling width of characters</source>
      <translation>Změna šířky znaků písma</translation>
    </message>
    <message>
      <source>Font Settings</source>
      <translation>Nastavení písma</translation>
    </message>
  </context>
  <context>
    <name>SToolBStyle</name>
    <message>
      <source>Kerning:</source>
      <translation>Vyrovnání znaků (kerning):</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>Manual Kerning</source>
      <translation>Ruční vyrovnání znaků (Kerning)</translation>
    </message>
    <message>
      <source>Character Settings</source>
      <translation>Nastavení znaků</translation>
    </message>
  </context>
  <context>
    <name>ScriXmlDoc</name>
    <message>
      <source>Copy #%1 of </source>
      <translation>Kopie č. %1 z</translation>
    </message>
    <message>
      <source>Background</source>
      <translation>Pozadí</translation>
    </message>
  </context>
  <context>
    <name>ScribusApp</name>
    <message>
      <source>File</source>
      <translation>Soubor</translation>
    </message>
    <message>
      <source>Searching for Fonts</source>
      <translation>Hledám písma</translation>
    </message>
    <message>
      <source>There are no Postscript-Fonts on your System</source>
      <translation>Váš systém neobsahuje žádná Postscriptová písma</translation>
    </message>
    <message>
      <source>Exiting now</source>
      <translation>Končím</translation>
    </message>
    <message>
      <source>Fatal Error</source>
      <translation>Kritická chyba</translation>
    </message>
    <message>
      <source>Smart Hyphen</source>
      <translation>Inteligentní spojovník</translation>
    </message>
    <message>
      <source>Align Left</source>
      <translation>Zarovnat vlevo</translation>
    </message>
    <message>
      <source>Align Right</source>
      <translation>Zarovnat vpravo</translation>
    </message>
    <message>
      <source>Align Center</source>
      <translation>Zarovnat na střed</translation>
    </message>
    <message>
      <source>Insert Page Number</source>
      <translation>Vložit číslo strany</translation>
    </message>
    <message>
      <source>Attach Text to Path</source>
      <translation>Připojit text ke křivce</translation>
    </message>
    <message>
      <source>Show Layers</source>
      <translation>Zobrazit vrstvy</translation>
    </message>
    <message>
      <source>Javascripts...</source>
      <translation>Java skripty...</translation>
    </message>
    <message>
      <source>Undo</source>
      <translation>Předchozí stav (undo)</translation>
    </message>
    <message>
      <source>Show Page Palette</source>
      <translation>Zobrazit paletu strany</translation>
    </message>
    <message>
      <source>Lock/Unlock</source>
      <translation>Zamknout/Odemknout</translation>
    </message>
    <message>
      <source>Non Breaking Space</source>
      <translation>Nedělitelná mezera</translation>
    </message>
    <message>
      <source>Reading Preferences</source>
      <translation>Načítám nastavení</translation>
    </message>
    <message>
      <source>Init Hyphenator</source>
      <translation>Inicializace dělení slov</translation>
    </message>
    <message>
      <source>Setting up Shortcuts</source>
      <translation>Nastavení zkratek</translation>
    </message>
    <message>
      <source>Reading Scrapbook</source>
      <translation>Načítám zápisník</translation>
    </message>
    <message>
      <source>Initializing Plugins</source>
      <translation>Inicializace zásuvných modulů</translation>
    </message>
    <message>
      <source>New</source>
      <translation>Nový</translation>
    </message>
    <message>
      <source>Open...</source>
      <translation>Otevřít...</translation>
    </message>
    <message>
      <source>Close</source>
      <translation>Zavřít</translation>
    </message>
    <message>
      <source>Save</source>
      <translation>Uložit</translation>
    </message>
    <message>
      <source>Save as...</source>
      <translation>Uložit jako...</translation>
    </message>
    <message>
      <source>Get Text/Picture...</source>
      <translation>Vložit text/obrázek...</translation>
    </message>
    <message>
      <source>Document Info...</source>
      <translation>Informace o dokumentu...</translation>
    </message>
    <message>
      <source>Document Setup...</source>
      <translation>Nastavení dokumentu...</translation>
    </message>
    <message>
      <source>Print...</source>
      <translation>Tisk...</translation>
    </message>
    <message>
      <source>Quit</source>
      <translation>Konec</translation>
    </message>
    <message>
      <source>Cut</source>
      <translation>Vyjmout</translation>
    </message>
    <message>
      <source>Copy</source>
      <translation>Kopírovat</translation>
    </message>
    <message>
      <source>Paste</source>
      <translation>Vložit</translation>
    </message>
    <message>
      <source>Clear</source>
      <translation>Vymazat</translation>
    </message>
    <message>
      <source>Select all</source>
      <translation>Vybrat vše</translation>
    </message>
    <message>
      <source>Colors...</source>
      <translation>Barvy...</translation>
    </message>
    <message>
      <source>Styles...</source>
      <translation>Styly...</translation>
    </message>
    <message>
      <source>Templates...</source>
      <translation>Šablony...</translation>
    </message>
    <message>
      <source>Fonts...</source>
      <translation>Písma...</translation>
    </message>
    <message>
      <source>Select New Font</source>
      <translation>Vyberte nové písmo</translation>
    </message>
    <message>
      <source>Duplicate</source>
      <translation>Duplikovat</translation>
    </message>
    <message>
      <source>Multiple Duplicate</source>
      <translation>Vícenásobné duplikování</translation>
    </message>
    <message>
      <source>Delete</source>
      <translation>Smazat</translation>
    </message>
    <message>
      <source>Group</source>
      <translation>Seskupit</translation>
    </message>
    <message>
      <source>Un-group</source>
      <translation>Zrušit seskupení</translation>
    </message>
    <message>
      <source>Lock</source>
      <translation>Zamknout</translation>
    </message>
    <message>
      <source>Send to Back</source>
      <translation>Dát zcela dospodu</translation>
    </message>
    <message>
      <source>Bring to Front</source>
      <translation>Dát zcela navrch</translation>
    </message>
    <message>
      <source>Lower</source>
      <translation>Dát o vrstvu níž</translation>
    </message>
    <message>
      <source>Raise</source>
      <translation>Dát o vrstvu výš</translation>
    </message>
    <message>
      <source>Distribute/Align...</source>
      <translation>Umístit/zarovnat...</translation>
    </message>
    <message>
      <source>Insert...</source>
      <translation>Vložit...</translation>
    </message>
    <message>
      <source>Delete...</source>
      <translation>Smazat...</translation>
    </message>
    <message>
      <source>Move...</source>
      <translation>Přesunout...</translation>
    </message>
    <message>
      <source>Apply Template...</source>
      <translation>Použít šablonu...</translation>
    </message>
    <message>
      <source>Manage Guides...</source>
      <translation>Ovládání vodítek...</translation>
    </message>
    <message>
      <source>Fit in Window</source>
      <translation>Přizpůsobit oknu</translation>
    </message>
    <message>
      <source>50%</source>
      <translation>50%</translation>
    </message>
    <message>
      <source>75%</source>
      <translation>75%</translation>
    </message>
    <message>
      <source>200%</source>
      <translation>200%</translation>
    </message>
    <message>
      <source>Thumbnails</source>
      <translation>Miniatury</translation>
    </message>
    <message>
      <source>Hide Margins</source>
      <translation>Skrýt okraje</translation>
    </message>
    <message>
      <source>Hide Frames</source>
      <translation>Skrýt rámy</translation>
    </message>
    <message>
      <source>Hide Images</source>
      <translation>Skrýt obrázky</translation>
    </message>
    <message>
      <source>Show Grid</source>
      <translation>Ukázat mřížku</translation>
    </message>
    <message>
      <source>Snap to Grid</source>
      <translation>Magnetická mřížka</translation>
    </message>
    <message>
      <source>Tools</source>
      <translation>Nástroje</translation>
    </message>
    <message>
      <source>Properties</source>
      <translation>Vlastnosti</translation>
    </message>
    <message>
      <source>Outline</source>
      <translation>Obrys</translation>
    </message>
    <message>
      <source>Scrapbook</source>
      <translation>Zápisník</translation>
    </message>
    <message>
      <source>Manage Pictures</source>
      <translation>Správa obrázků</translation>
    </message>
    <message>
      <source>Hyphenate Text</source>
      <translation>Dělení slov v textu</translation>
    </message>
    <message>
      <source>About Scribus</source>
      <translation>O Scribusu</translation>
    </message>
    <message>
      <source>About Qt</source>
      <translation>O Qt</translation>
    </message>
    <message>
      <source>Online-Help...</source>
      <translation>Online nápověda...</translation>
    </message>
    <message>
      <source>Style</source>
      <translation>Styl</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Underline</source>
      <translation>Podtržené</translation>
    </message>
    <message>
      <source>Strikethru</source>
      <translation>Přeškrtnuté výš</translation>
    </message>
    <message>
      <source>Small Caps</source>
      <translation>Kapitálky</translation>
    </message>
    <message>
      <source>Superscript</source>
      <translation>Horní index</translation>
    </message>
    <message>
      <source>Subscript</source>
      <translation>Dolní index</translation>
    </message>
    <message>
      <source>Outlined</source>
      <translation>Obkreslené</translation>
    </message>
    <message>
      <source>X-Pos:</source>
      <translation>X-Poz:</translation>
    </message>
    <message>
      <source>Y-Pos:</source>
      <translation>Y-Poz:</translation>
    </message>
    <message>
      <source>Ready</source>
      <translation>Připravený</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Get Picture...</source>
      <translation>Vložit obrázek...</translation>
    </message>
    <message>
      <source>Color</source>
      <translation>Barva</translation>
    </message>
    <message>
      <source>Invert</source>
      <translation>Invertovat</translation>
    </message>
    <message>
      <source>Get Text...</source>
      <translation>Vložit text...</translation>
    </message>
    <message>
      <source>Font</source>
      <translation>Písmo</translation>
    </message>
    <message>
      <source>Size</source>
      <translation>Velikost</translation>
    </message>
    <message>
      <source>Shade</source>
      <translation>Stín</translation>
    </message>
    <message>
      <source>Unlock</source>
      <translation>Odemknout</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Documents (*.sla *.scd);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Loading...</source>
      <translation>Načítám...</translation>
    </message>
    <message>
      <source>Text Files (*.txt);;All Files(*)</source>
      <translation>Textové soubory (*.txt);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Can't write the File: 
%1</source>
      <translation>Nelze zapsat soubor: 
%1</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Saving...</source>
      <translation>Ukládám...</translation>
    </message>
    <message>
      <source>Printing...</source>
      <translation>Tisknu...</translation>
    </message>
    <message>
      <source>Document</source>
      <translation>Dokument</translation>
    </message>
    <message>
      <source>Printing failed!</source>
      <translation>Tisk se nepodařil!</translation>
    </message>
    <message>
      <source>Scribus Manual</source>
      <translation>Scribus manuál</translation>
    </message>
    <message>
      <source>The following Programs are missing:</source>
      <translation>Chybí tyto programy:</translation>
    </message>
    <message>
      <source>All</source>
      <translation>Všechny</translation>
    </message>
    <message>
      <source>EPS-Files (*.eps);;All Files (*)</source>
      <translation>EPS soubory (*.eps);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Loading:</source>
      <translation>Načítám:</translation>
    </message>
    <message>
      <source>Adjusting Colors</source>
      <translation>Přizpůsobení barev</translation>
    </message>
    <message>
      <source>English</source>
      <translation>Anglicky</translation>
    </message>
    <message>
      <source>German</source>
      <translation>Německy</translation>
    </message>
    <message>
      <source>Spanish</source>
      <translation>Španělsky</translation>
    </message>
    <message>
      <source>Italian</source>
      <translation>Italsky</translation>
    </message>
    <message>
      <source>French</source>
      <translation>Francouzsky</translation>
    </message>
    <message>
      <source>Russian</source>
      <translation>Rusky</translation>
    </message>
    <message>
      <source>Danish</source>
      <translation>Dánsky</translation>
    </message>
    <message>
      <source>Slovak</source>
      <translation>Slovensky</translation>
    </message>
    <message>
      <source>Hungarian</source>
      <translation>Maďarsky</translation>
    </message>
    <message>
      <source>Czech</source>
      <translation>Česky</translation>
    </message>
    <message>
      <source>Dutch</source>
      <translation>Dánsky</translation>
    </message>
    <message>
      <source>Portuguese</source>
      <translation>Portugalsky</translation>
    </message>
    <message>
      <source>Ukrainian</source>
      <translation>Ukrajinsky</translation>
    </message>
    <message>
      <source>Polish</source>
      <translation>Polsky</translation>
    </message>
    <message>
      <source>Greek</source>
      <translation>Řecky</translation>
    </message>
    <message>
      <source>Catalan</source>
      <translation>Katalánsky</translation>
    </message>
    <message>
      <source>Choose a Directory</source>
      <translation>Vybrat adresář</translation>
    </message>
    <message>
      <source>Scribus Crash</source>
      <translation>Zhroucení Scribusu</translation>
    </message>
    <message>
      <source>Scribus crashes due to Signal #%1</source>
      <translation>Scribus spadl díky signálu č. %1</translation>
    </message>
    <message>
      <source>All Files (*)</source>
      <translation>Včechny soubory (*)</translation>
    </message>
    <message>
      <source>Finnish</source>
      <translation>Finsky</translation>
    </message>
    <message>
      <source>Irish</source>
      <translation>Irsky</translation>
    </message>
    <message>
      <source>All Supported Formats</source>
      <translation>Všechny podporované formáty</translation>
    </message>
    <message>
      <source>Create a new Document</source>
      <translation>Vytvořit nový dokument</translation>
    </message>
    <message>
      <source>Open a Document</source>
      <translation>Otevřít dokument</translation>
    </message>
    <message>
      <source>Save the current Document</source>
      <translation>Uložit aktuální dokument</translation>
    </message>
    <message>
      <source>Close the current Document</source>
      <translation>Zavřít aktuální dokument</translation>
    </message>
    <message>
      <source>Print the current Document</source>
      <translation>Tisknout aktuální dokument</translation>
    </message>
    <message>
      <source>Save the current Document as PDF</source>
      <translation>Uložit aktuální dokument jako PDF</translation>
    </message>
    <message>
      <source>Show Baseline Grid</source>
      <translation>Zobrazit pomocnou mřížku</translation>
    </message>
    <message>
      <source>&amp;File</source>
      <translation>&amp;Soubor</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
    <message>
      <source>&amp;Item</source>
      <translation>O&amp;bjekt</translation>
    </message>
    <message>
      <source>&amp;Page</source>
      <translation>Str&amp;ana</translation>
    </message>
    <message>
      <source>&amp;View</source>
      <translation>Ná&amp;hled</translation>
    </message>
    <message>
      <source>&amp;Tools</source>
      <translation>&amp;Nástroje</translation>
    </message>
    <message>
      <source>E&amp;xtras</source>
      <translation>E&amp;xtra</translation>
    </message>
    <message>
      <source>&amp;Windows</source>
      <translation>&amp;Okna</translation>
    </message>
    <message>
      <source>&amp;Help</source>
      <translation>Nápo&amp;věda</translation>
    </message>
    <message>
      <source>Hide Baseline Grid</source>
      <translation>Skrýt pomocnou mřížku</translation>
    </message>
    <message>
      <source>Some Objects are locked.</source>
      <translation>Některé objekty jsou zamčené.</translation>
    </message>
    <message>
      <source>Cancel</source>
      <translation>Zrušit</translation>
    </message>
    <message>
      <source>Lock all</source>
      <translation>Zamknout vše</translation>
    </message>
    <message>
      <source>Unlock all</source>
      <translation>Odemknout vše</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source>in</source>
      <translation>in</translation>
    </message>
    <message>
      <source>p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>Lithuanian</source>
      <translation>Litevsky</translation>
    </message>
    <message>
      <source>Swedish</source>
      <translation>Švédsky</translation>
    </message>
    <message>
      <source>Slovenian</source>
      <translation>Slovinsky</translation>
    </message>
    <message>
      <source>&amp;Settings</source>
      <translation>Nas&amp;tavení</translation>
    </message>
    <message>
      <source>&amp;Color Management...</source>
      <translation>Správa &amp;barev...</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Open...</source>
      <translation>&amp;Otevřít...</translation>
    </message>
    <message>
      <source>Open &amp;Recent</source>
      <translation>Otevřít &amp;předchozí</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>Save &amp;As...</source>
      <translation>Uložit j&amp;ako...</translation>
    </message>
    <message>
      <source>Re&amp;vert to Saved</source>
      <translation>Návrat k u&amp;loženému</translation>
    </message>
    <message>
      <source>Collect for O&amp;utput...</source>
      <translation>Ad&amp;resář pro výstup...</translation>
    </message>
    <message>
      <source>&amp;Get Text/Picture...</source>
      <translation>Vložit &amp;text/obrázek...</translation>
    </message>
    <message>
      <source>Append &amp;Text...</source>
      <translation>&amp;Připojit text...</translation>
    </message>
    <message>
      <source>&amp;Import</source>
      <translation>&amp;Import</translation>
    </message>
    <message>
      <source>Save &amp;Text...</source>
      <translation>Uložit &amp;text...</translation>
    </message>
    <message>
      <source>Save Page as &amp;EPS...</source>
      <translation>Uložit stranu jako &amp;EPS...</translation>
    </message>
    <message>
      <source>Save as P&amp;DF...</source>
      <translation>Uložit jako P&amp;DF...</translation>
    </message>
    <message>
      <source>&amp;Export</source>
      <translation>&amp;Export</translation>
    </message>
    <message>
      <source>Document &amp;Setup...</source>
      <translation>Na&amp;stavení dokumentu...</translation>
    </message>
    <message>
      <source>&amp;Print...</source>
      <translation>&amp;Tisk...</translation>
    </message>
    <message>
      <source>&amp;Quit</source>
      <translation>&amp;Konec</translation>
    </message>
    <message>
      <source>&amp;Undo</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>Vy&amp;mazat</translation>
    </message>
    <message>
      <source>Select &amp;All</source>
      <translation>Vybr&amp;at vše</translation>
    </message>
    <message>
      <source>&amp;Search/Replace...</source>
      <translation>&amp;Hledat/Nahradit...</translation>
    </message>
    <message>
      <source>C&amp;olors...</source>
      <translation>&amp;Barvy...</translation>
    </message>
    <message>
      <source>&amp;Paragraph Styles...</source>
      <translation>&amp;Styly odstavce...</translation>
    </message>
    <message>
      <source>&amp;Line Styles...</source>
      <translation>Styly ča&amp;r...</translation>
    </message>
    <message>
      <source>&amp;Templates...</source>
      <translation>Ša&amp;blony...</translation>
    </message>
    <message>
      <source>&amp;Javascripts...</source>
      <translation>&amp;Java skripty...</translation>
    </message>
    <message>
      <source>D&amp;uplicate</source>
      <translation>&amp;Duplikovat</translation>
    </message>
    <message>
      <source>&amp;Multiple Duplicate</source>
      <translation>&amp;Vícenásobné duplikování</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Group</source>
      <translation>&amp;Seskupit</translation>
    </message>
    <message>
      <source>&amp;Ungroup</source>
      <translation>&amp;Zrušit seskupení</translation>
    </message>
    <message>
      <source>&amp;Lock</source>
      <translation>Zam&amp;knout</translation>
    </message>
    <message>
      <source>Send to &amp;Back</source>
      <translation>&amp;Dát zcela dospodu</translation>
    </message>
    <message>
      <source>Bring to &amp;Front</source>
      <translation>Dát zcela &amp;navrch</translation>
    </message>
    <message>
      <source>&amp;Lower</source>
      <translation>Dát o &amp;vrstvu níž</translation>
    </message>
    <message>
      <source>&amp;Raise</source>
      <translation>Dát o v&amp;rstvu výš</translation>
    </message>
    <message>
      <source>Distribute/&amp;Align...</source>
      <translation>Umístit/z&amp;arovnat...</translation>
    </message>
    <message>
      <source>&amp;Shape</source>
      <translation>&amp;Tvar</translation>
    </message>
    <message>
      <source>&amp;Attach Text to Path</source>
      <translation>Připojit &amp;text ke křivce</translation>
    </message>
    <message>
      <source>&amp;Detach Text from Path</source>
      <translation>&amp;Odpojit text od křivky</translation>
    </message>
    <message>
      <source>&amp;Combine Polygons</source>
      <translation>&amp;Kombinovat mnohoúhelníky</translation>
    </message>
    <message>
      <source>Split &amp;Polygons</source>
      <translation>&amp;Rozdělit mnohoúhelníky</translation>
    </message>
    <message>
      <source>C&amp;onvert to Outlines</source>
      <translation>&amp;Převést na křivky</translation>
    </message>
    <message>
      <source>&amp;Insert...</source>
      <translation>&amp;Vložit...</translation>
    </message>
    <message>
      <source>&amp;Delete...</source>
      <translation>&amp;Smazat...</translation>
    </message>
    <message>
      <source>&amp;Move...</source>
      <translation>&amp;Přesunout...</translation>
    </message>
    <message>
      <source>&amp;Apply Template...</source>
      <translation>Použí&amp;t šablonu...</translation>
    </message>
    <message>
      <source>&amp;Fit in Window</source>
      <translation>&amp;Přizpůsobit oknu</translation>
    </message>
    <message>
      <source>&amp;100%</source>
      <translation>&amp;100%</translation>
    </message>
    <message>
      <source>&amp;Thumbnails</source>
      <translation>M&amp;iniatury</translation>
    </message>
    <message>
      <source>Show &amp;Grid</source>
      <translation>Ukázat &amp;mřížku</translation>
    </message>
    <message>
      <source>Sna&amp;p to Guides</source>
      <translation>&amp;Magnetická vodítka</translation>
    </message>
    <message>
      <source>Show &amp;Baseline Grid</source>
      <translation>&amp;Zobrazit pomocnou mřížku</translation>
    </message>
    <message>
      <source>&amp;Properties</source>
      <translation>&amp;Vlastnosti</translation>
    </message>
    <message>
      <source>&amp;Outline</source>
      <translation>&amp;Obrysy</translation>
    </message>
    <message>
      <source>&amp;Scrapbook</source>
      <translation>&amp;Zápisník</translation>
    </message>
    <message>
      <source>&amp;Layers</source>
      <translation>V&amp;rstvy</translation>
    </message>
    <message>
      <source>P&amp;age Palette</source>
      <translation>&amp;Paleta strany</translation>
    </message>
    <message>
      <source>&amp;Bookmarks</source>
      <translation>&amp;Záložky</translation>
    </message>
    <message>
      <source>&amp;Manage Pictures</source>
      <translation>Správa &amp;obrázků</translation>
    </message>
    <message>
      <source>&amp;Hyphenate Text</source>
      <translation>&amp;Dělení slov v textu</translation>
    </message>
    <message>
      <source>Toolti&amp;ps</source>
      <translation>&amp;Tipy pro nástroje</translation>
    </message>
    <message>
      <source>P&amp;DF Tools</source>
      <translation>P&amp;DF nástroje</translation>
    </message>
    <message>
      <source>Tooltips</source>
      <translation>Tipy pro nástroje</translation>
    </message>
    <message>
      <source>&amp;Fonts...</source>
      <translation>&amp;Písma...</translation>
    </message>
    <message>
      <source>&amp;Hyphenator...</source>
      <translation>Děl&amp;ení slov v textu...</translation>
    </message>
    <message>
      <source>&amp;Keyboard Shortcuts...</source>
      <translation>Správa &amp;klávesových zkratek...</translation>
    </message>
    <message>
      <source>&amp;About Scribus</source>
      <translation>&amp;O Scribusu</translation>
    </message>
    <message>
      <source>About &amp;Qt</source>
      <translation>O &amp;Qt</translation>
    </message>
    <message>
      <source>Scribus &amp;Manual...</source>
      <translation>Scribus &amp;manuál...</translation>
    </message>
    <message>
      <source>St&amp;yle</source>
      <translation>St&amp;yl</translation>
    </message>
    <message>
      <source>&amp;Left</source>
      <translation>V&amp;levo</translation>
    </message>
    <message>
      <source>&amp;Center</source>
      <translation>Na &amp;střed</translation>
    </message>
    <message>
      <source>&amp;Right</source>
      <translation>V&amp;pravo</translation>
    </message>
    <message>
      <source>&amp;Block</source>
      <translation>Do &amp;bloku</translation>
    </message>
    <message>
      <source>&amp;Forced</source>
      <translation>&amp;Vynucené</translation>
    </message>
    <message>
      <source>&amp;Other...</source>
      <translation>&amp;Jiný...</translation>
    </message>
    <message>
      <source>&amp;Cascade</source>
      <translation>&amp;Kaskáda</translation>
    </message>
    <message>
      <source>&amp;Tile</source>
      <translation>&amp;Dlaždice</translation>
    </message>
    <message>
      <source>&amp;Color</source>
      <translation>&amp;Barva</translation>
    </message>
    <message>
      <source>&amp;Invert</source>
      <translation>&amp;Invertovat</translation>
    </message>
    <message>
      <source>&amp;Get Text...</source>
      <translation>&amp;Vložit text...</translation>
    </message>
    <message>
      <source>&amp;Font</source>
      <translation>&amp;Písmo</translation>
    </message>
    <message>
      <source>&amp;Size</source>
      <translation>&amp;Velikost</translation>
    </message>
    <message>
      <source>&amp;Effects</source>
      <translation>&amp;Efekty</translation>
    </message>
    <message>
      <source>&amp;Alignment</source>
      <translation>&amp;Zarovnání</translation>
    </message>
    <message>
      <source>&amp;Shade</source>
      <translation>&amp;Stín</translation>
    </message>
    <message>
      <source>&amp;Tabulators...</source>
      <translation>&amp;Tabelátory...</translation>
    </message>
    <message>
      <source>Un&amp;lock</source>
      <translation>&amp;Odemknout</translation>
    </message>
    <message>
      <source>Show &amp;Images</source>
      <translation>Zobrazit &amp;obrázky</translation>
    </message>
    <message>
      <source>Show &amp;Margins</source>
      <translation>Zobrazit o&amp;kraje</translation>
    </message>
    <message>
      <source>Show &amp;Frames</source>
      <translation>Zobrazit &amp;rámy</translation>
    </message>
    <message>
      <source>Show G&amp;uides</source>
      <translation>Zobrazit &amp;vodítka</translation>
    </message>
    <message>
      <source>Ghostscript : You cannot use EPS Images</source>
      <translation>Ghostscript: Nemůžete použít EPS obrázky</translation>
    </message>
    <message>
      <source>Import &amp;Page(s)...</source>
      <translation>Im&amp;portovat stranu(y)...</translation>
    </message>
    <message>
      <source>100%</source>
      <translation>100%</translation>
    </message>
    <message>
      <source>Sn&amp;ap to Grid</source>
      <translation>M&amp;agnetická mřížka</translation>
    </message>
    <message>
      <source>P&amp;references...</source>
      <translation>N&amp;astavení...</translation>
    </message>
    <message>
      <source>Importing Pages...</source>
      <translation>Importuji strany...</translation>
    </message>
    <message>
      <source>Import Page(s)</source>
      <translation>Importovat stranu(y)</translation>
    </message>
    <message>
      <source>&lt;p>You are trying to import more pages than there are available in the current document counting from the active page.&lt;/p>Choose one of the following:&lt;br>&lt;ul>&lt;li>&lt;b>Create&lt;/b> missing pages&lt;/li>&lt;li>&lt;b>Import&lt;/b> pages until the last page&lt;/li>&lt;li>&lt;b>Cancel&lt;/b>&lt;/li>&lt;/ul>&lt;br></source>
      <translation>&lt;p>Zkoušíte importovat více stran, než je v dokumentu.&lt;/p>Vyberte správnou činnost:&lt;br>&lt;ul>&lt;li>&lt;b>Vytvořit&lt;/b> chybějící strany&lt;/li>&lt;li>&lt;b>Importovat&lt;/b> strany až do konce&lt;/li>&lt;li>&lt;b>Zrušit&lt;/b>&lt;/li>&lt;/ul>&lt;br></translation>
    </message>
    <message>
      <source>Create</source>
      <translation>Vytvořit</translation>
    </message>
    <message>
      <source>Import</source>
      <translation>Importovat</translation>
    </message>
    <message>
      <source>Import done</source>
      <translation>Import ukončen</translation>
    </message>
    <message>
      <source>Found nothing to import</source>
      <translation>Nenalezeno nic k importu</translation>
    </message>
    <message>
      <source>Getting ICC Profiles</source>
      <translation>Získat ICC profily</translation>
    </message>
    <message>
      <source>Manage &amp;Guides...</source>
      <translation>O&amp;vládání vodítek...</translation>
    </message>
    <message>
      <source>&amp;Size:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <source>&amp;Shade:</source>
      <translation>&amp;Stín:</translation>
    </message>
    <message>
      <source>Document &amp;Information...</source>
      <translation>In&amp;formace o dokumentu...</translation>
    </message>
    <message>
      <source>&amp;Undo Delete Object</source>
      <translation>&amp;Zpět smazání objektu</translation>
    </message>
    <message>
      <source>&amp;Undo Object Move</source>
      <translation>&amp;Zpět přesunutí objektu</translation>
    </message>
    <message>
      <source>&amp;Undo Object Change</source>
      <translation>&amp;Zpět změna objektu</translation>
    </message>
    <message>
      <source>&amp;Edit Shape</source>
      <translation>Upravit &amp;obrys</translation>
    </message>
    <message>
      <source>File %1 is not in Scribus format</source>
      <translation>Soubor %1 není ve Scribus formátu</translation>
    </message>
    <message>
      <source>Afrikaans</source>
      <translation>Afrikánština</translation>
    </message>
    <message>
      <source>Font System Initialized</source>
      <translation>Inicializován systém písem</translation>
    </message>
  </context>
  <context>
    <name>ScribusView</name>
    <message>
      <source> %</source>
      <translation>%</translation>
    </message>
    <message>
      <source>Layer</source>
      <translation>Vrstva</translation>
    </message>
    <message>
      <source>All</source>
      <translation>Všechny</translation>
    </message>
    <message>
      <source>pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source>in</source>
      <translation>in</translation>
    </message>
    <message>
      <source>p</source>
      <translation>p</translation>
    </message>
  </context>
  <context>
    <name>ScribusWin</name>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Document:</source>
      <translation>Dokument:</translation>
    </message>
    <message>
      <source>has been changed since the last save.</source>
      <translation>od posledního uložení byl dokument změněný.</translation>
    </message>
    <message>
      <source>&amp;Leave Anyway</source>
      <translation>Za&amp;hodit</translation>
    </message>
    <message>
      <source>C&amp;lose Anyway</source>
      <translation>Za&amp;vřít</translation>
    </message>
    <message>
      <source>&amp;Save Now</source>
      <translation>&amp;Uložit ihned</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>SeList</name>
    <message>
      <source>Show Page Previews</source>
      <translation>Zobrazit náhledy pro strany</translation>
    </message>
  </context>
  <context>
    <name>SeView</name>
    <message>
      <source>Show Template Names</source>
      <translation>Zobrazit názvy šablon</translation>
    </message>
  </context>
  <context>
    <name>SearchReplace</name>
    <message>
      <source>Search/Replace</source>
      <translation>Hledat/Nahradit</translation>
    </message>
    <message>
      <source>Search for:</source>
      <translation>Hledat:</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Paragraph Style</source>
      <translation>Styl odstavce</translation>
    </message>
    <message>
      <source>Font</source>
      <translation>Písmo</translation>
    </message>
    <message>
      <source>Font Size</source>
      <translation>Velikost písma</translation>
    </message>
    <message>
      <source>Font Effects</source>
      <translation>Efekty písma</translation>
    </message>
    <message>
      <source>Fill Color</source>
      <translation>Barva výplně</translation>
    </message>
    <message>
      <source>Fill Shade</source>
      <translation>Odstín výplně</translation>
    </message>
    <message>
      <source>Stroke Color</source>
      <translation>Barva obrysu</translation>
    </message>
    <message>
      <source>Stroke Shade</source>
      <translation>Odstín obrysu</translation>
    </message>
    <message>
      <source>Left</source>
      <translation>Vlevo</translation>
    </message>
    <message>
      <source>Center</source>
      <translation>Na střed</translation>
    </message>
    <message>
      <source>Right</source>
      <translation>Vpravo</translation>
    </message>
    <message>
      <source>Block</source>
      <translation>Do bloku</translation>
    </message>
    <message>
      <source>Forced</source>
      <translation>Vynucené</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source>None</source>
      <translation>Žádné</translation>
    </message>
    <message>
      <source>Replace with:</source>
      <translation>Nahradit čím:</translation>
    </message>
    <message>
      <source>Search finished</source>
      <translation>Hledání hotovo</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>&amp;Whole Word</source>
      <translation>&amp;Celé slovo</translation>
    </message>
    <message>
      <source>&amp;Ignore Case</source>
      <translation>&amp;Ignorovat velikost znaků</translation>
    </message>
    <message>
      <source>&amp;Search</source>
      <translation>&amp;Hledat</translation>
    </message>
    <message>
      <source>&amp;Replace</source>
      <translation>&amp;Nahradit</translation>
    </message>
    <message>
      <source>Replace &amp;All</source>
      <translation>Nahradit &amp;vše</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>Vy&amp;mazat</translation>
    </message>
  </context>
  <context>
    <name>SeitenPal</name>
    <message>
      <source>Arrange Pages</source>
      <translation>Uspořádat strany</translation>
    </message>
    <message>
      <source>Available Templates:</source>
      <translation>Dostupné šablony:</translation>
    </message>
    <message>
      <source>Document Pages:</source>
      <translation>Strany dokumentu:</translation>
    </message>
    <message>
      <source>Facing Pages</source>
      <translation>Protilehlé stránky (Dvoustrany)</translation>
    </message>
    <message>
      <source>Left Page first</source>
      <translation>První strana vlevo</translation>
    </message>
    <message>
      <source>Drag Pages or Template Pages onto the Trashbin to delete them.</source>
      <translation>Strany nebo šablony smažete přetáhnutím do odpadkového koše.</translation>
    </message>
    <message>
      <source>Here are all your Templates, to create a new Page
drag a Template to the Pageview below.</source>
      <translation>Zde jsou všechny vaše šablony; na vytvoření nové strany
přetáhněte šablonu do náhledu strany.</translation>
    </message>
    <message>
      <source>Normal</source>
      <translation>Normální</translation>
    </message>
    <message>
      <source>Previews all the pages of your document.</source>
      <translation>Náhled všech stran dokumentu.</translation>
    </message>
  </context>
  <context>
    <name>SelectFields</name>
    <message>
      <source>Select Fields</source>
      <translation>Zvolit pole</translation>
    </message>
    <message>
      <source>Available Fields</source>
      <translation>Dostupná pole</translation>
    </message>
    <message>
      <source>Selected Fields</source>
      <translation>Zvolená pole</translation>
    </message>
    <message>
      <source>&amp;>></source>
      <translation>&amp;>></translation>
    </message>
    <message>
      <source>&amp;&lt;&lt;</source>
      <translation>&amp;&lt;&lt;</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>ShadeButton</name>
    <message>
      <source>Other...</source>
      <translation>Jiný...</translation>
    </message>
    <message>
      <source>Shade</source>
      <translation>Stín</translation>
    </message>
    <message>
      <source>&amp;Shade:</source>
      <translation>&amp;Stín:</translation>
    </message>
  </context>
  <context>
    <name>SideBar</name>
    <message>
      <source>No Style</source>
      <translation>Bez stylu</translation>
    </message>
  </context>
  <context>
    <name>Spalette</name>
    <message>
      <source>No Style</source>
      <translation>Bez stylu</translation>
    </message>
  </context>
  <context>
    <name>StilFormate</name>
    <message>
      <source>Edit Styles</source>
      <translation>Upravit styly</translation>
    </message>
    <message>
      <source>Copy of %1</source>
      <translation>Kopie %1</translation>
    </message>
    <message>
      <source>New Style</source>
      <translation>Nový styl</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>No</source>
      <translation>Ne</translation>
    </message>
    <message>
      <source>Yes</source>
      <translation>Ano</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.sla.gz *.scd *.scd.gz);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Documents (*.sla *.scd);;All Files (*)</source>
      <translation>Dokumenty (*.sla *.scd);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>&amp;Append</source>
      <translation>Připoji&amp;t</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
    <message>
      <source>D&amp;uplicate</source>
      <translation>&amp;Duplikovat</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>&amp;Save</source>
      <translation>&amp;Uložit</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Do you really want to delete this Style?</source>
      <translation>Opravdu chcete smazat tento styl?</translation>
    </message>
  </context>
  <context>
    <name>StoryEditor</name>
    <message>
      <source>Story Editor</source>
      <translation>Editor textu</translation>
    </message>
    <message>
      <source>File</source>
      <translation>Soubor</translation>
    </message>
    <message>
      <source>Current Paragraph:</source>
      <translation>Aktuální odstavec:</translation>
    </message>
    <message>
      <source>Words: </source>
      <translation>Slov:</translation>
    </message>
    <message>
      <source>Chars: </source>
      <translation>Znaků:</translation>
    </message>
    <message>
      <source>Totals:</source>
      <translation>Celkem:</translation>
    </message>
    <message>
      <source>Paragraphs: </source>
      <translation>Odstavců:</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Do you really want to lose all your Changes?</source>
      <translation>Opravdu chcete zahodit všechny změny?</translation>
    </message>
    <message>
      <source>Do you really want to clear all your Text?</source>
      <translation>Opravdu chcete smazat veškerý text?</translation>
    </message>
    <message>
      <source>Update Text Frame</source>
      <translation>Aktualizovat textový rám</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Otevřít</translation>
    </message>
    <message>
      <source>Text Files (*.txt);;All Files(*)</source>
      <translation>Textové soubory (*.txt);;Všechny soubory (*)</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Uložit jako</translation>
    </message>
    <message>
      <source>Do you want to save your changes?</source>
      <translation>Opravdu chcete uložit změny?</translation>
    </message>
    <message>
      <source>Update Text Frame and Exit</source>
      <translation>Aktualizovat textový rám a skončit</translation>
    </message>
    <message>
      <source>Exit Without Updating Text Frame</source>
      <translation>Skončit bez aktualizace textového rámu</translation>
    </message>
    <message>
      <source>&amp;New</source>
      <translation>&amp;Nový</translation>
    </message>
    <message>
      <source>&amp;Reload Text from Frame</source>
      <translation>&amp;Znovu nahrát původní text z rámu</translation>
    </message>
    <message>
      <source>&amp;Save to File...</source>
      <translation>Uložit do &amp;souboru...</translation>
    </message>
    <message>
      <source>&amp;Load from File...</source>
      <translation>Nahrá&amp;t ze souboru...</translation>
    </message>
    <message>
      <source>Save &amp;Document</source>
      <translation>Uložit &amp;dokument</translation>
    </message>
    <message>
      <source>&amp;Update Text Frame and Exit</source>
      <translation>&amp;Aktualizovat textový rám a skončit</translation>
    </message>
    <message>
      <source>&amp;Exit Without Updating Text Frame</source>
      <translation>Skončit &amp;bez aktualizace textového rámu</translation>
    </message>
    <message>
      <source>Cu&amp;t</source>
      <translation>Vyjmou&amp;t</translation>
    </message>
    <message>
      <source>&amp;Copy</source>
      <translation>&amp;Kopírovat</translation>
    </message>
    <message>
      <source>&amp;Paste</source>
      <translation>&amp;Vložit</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>Vy&amp;mazat</translation>
    </message>
    <message>
      <source>&amp;Insert Special...</source>
      <translation>Vložit s&amp;peciální...</translation>
    </message>
    <message>
      <source>&amp;Update Text Frame</source>
      <translation>Ak&amp;tualizovat textový rám</translation>
    </message>
    <message>
      <source>&amp;File</source>
      <translation>&amp;Soubor</translation>
    </message>
    <message>
      <source>&amp;Edit</source>
      <translation>Ú&amp;pravy</translation>
    </message>
    <message>
      <source>Select &amp;All</source>
      <translation>Vybr&amp;at vše</translation>
    </message>
    <message>
      <source>&amp;Edit Styles...</source>
      <translation>Upravit &amp;styly...</translation>
    </message>
    <message>
      <source>Load Text from File</source>
      <translation>Nahrát text ze souboru</translation>
    </message>
    <message>
      <source>Save Text to File</source>
      <translation>Uložit text do souboru</translation>
    </message>
    <message>
      <source>Reload Text from Frame</source>
      <translation>Znovu nahrát původní text z rámu</translation>
    </message>
    <message>
      <source>&amp;Search/Replace...</source>
      <translation>&amp;Hledat/Nahradit...</translation>
    </message>
    <message>
      <source>&amp;Fonts Preview...</source>
      <translation>&amp;Náhled písem...</translation>
    </message>
    <message>
      <source>&amp;Background...</source>
      <translation>&amp;Pozadí...</translation>
    </message>
    <message>
      <source>&amp;Display Font...</source>
      <translation>&amp;Zobrazit písmem...</translation>
    </message>
    <message>
      <source>&amp;Settings</source>
      <translation>&amp;Nastavení</translation>
    </message>
    <message>
      <source>Search/Replace</source>
      <translation>Hledat/Nahradit</translation>
    </message>
    <message>
      <source>Clear all Text</source>
      <translation>Smazat veškerý text</translation>
    </message>
    <message>
      <source>&amp;Smart text selection</source>
      <translation>&amp;Chytrý výběr textu</translation>
    </message>
  </context>
  <context>
    <name>StyleSelect</name>
    <message>
      <source>Underline</source>
      <translation>Podtržené</translation>
    </message>
    <message>
      <source>Small Caps</source>
      <translation>Kapitálky</translation>
    </message>
    <message>
      <source>Subscript</source>
      <translation>Dolní index</translation>
    </message>
    <message>
      <source>Superscript</source>
      <translation>Horní index</translation>
    </message>
    <message>
      <source>Outline Text</source>
      <translation>Obrys textu</translation>
    </message>
    <message>
      <source>Strike Out</source>
      <translation>Přeškrtnuté</translation>
    </message>
  </context>
  <context>
    <name>SxwDialog</name>
    <message>
      <source>Update paragraph styles</source>
      <translation>Aktualizovat styly odstavce</translation>
    </message>
    <message>
      <source>Use document name as a prefix for paragraph styles</source>
      <translation>Použít jméno dokumentu jako předponu stylů odstavce</translation>
    </message>
    <message>
      <source>Do not ask again</source>
      <translation>Neptat se znovu</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Should importer add the name of the document
on front of the paragraph style name in Scribus</source>
      <translation>Má importer přidávat jméno dokumentu před
jméno stylu odstavce ve Scribusu</translation>
    </message>
    <message>
      <source>If a paragraph style already exists with the same name as the current
OpenOffice.org document's paragraph, should the style in Scribus be
edited to match the one being imported, or left untouched</source>
      <translation>Má být existující Scribus styl změněn, jestliže v importovaném dokumentu
existuje styl se stejným jménem nebo se nemá změnit</translation>
    </message>
    <message>
      <source>OpenOffice.org Writer Importer Options</source>
      <translation>Nastavení importu OpenOffice.org Writer</translation>
    </message>
    <message>
      <source>Should the importer always use currently
set value when importing OpenOffice.org document and
never ask your confirmation again</source>
      <translation>Má si importer vždy pamatovat nastavenou hodnotu
a nikdy znovu nevyžadovat potvrzení</translation>
    </message>
  </context>
  <context>
    <name>TabManager</name>
    <message>
      <source>Manage Tabulators</source>
      <translation>Správa tabelátorů</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>Tabruler</name>
    <message>
      <source>Left</source>
      <translation>Vlevo</translation>
    </message>
    <message>
      <source>Right</source>
      <translation>Vpravo</translation>
    </message>
    <message>
      <source>Full Stop</source>
      <translation>Tečka</translation>
    </message>
    <message>
      <source>Comma</source>
      <translation>Čárka</translation>
    </message>
    <message>
      <source>Center</source>
      <translation>Na střed</translation>
    </message>
    <message>
      <source>Delete All</source>
      <translation>Smazat vše</translation>
    </message>
    <message>
      <source>Indentation for first line of the paragraph</source>
      <translation>Odsazení první řádky odstavce</translation>
    </message>
    <message>
      <source>Indentation from the left for the whole paragraph</source>
      <translation>Odsazení celého odstavce zleva</translation>
    </message>
    <message>
      <source>Delete all Tabulators</source>
      <translation>Smazat všechny tabelátory</translation>
    </message>
    <message>
      <source> pt</source>
      <translation>pt</translation>
    </message>
    <message>
      <source> mm</source>
      <translation>mm</translation>
    </message>
    <message>
      <source> in</source>
      <translation>in</translation>
    </message>
    <message>
      <source> p</source>
      <translation>p</translation>
    </message>
    <message>
      <source>&amp;Position:</source>
      <translation>&amp;Pozice:</translation>
    </message>
    <message>
      <source>First &amp;Line:</source>
      <translation>P&amp;rvní řádek:</translation>
    </message>
    <message>
      <source>Left Ind&amp;ent:</source>
      <translation>Levé &amp;odsazení:</translation>
    </message>
  </context>
  <context>
    <name>Tree</name>
    <message>
      <source>Outline</source>
      <translation>Přehled</translation>
    </message>
    <message>
      <source>Element</source>
      <translation>Prvek</translation>
    </message>
    <message>
      <source>Type</source>
      <translation>Typ</translation>
    </message>
    <message>
      <source>Information</source>
      <translation>Informace</translation>
    </message>
    <message>
      <source>X:</source>
      <translation>X:</translation>
    </message>
    <message>
      <source>Y:</source>
      <translation>Y:</translation>
    </message>
    <message>
      <source>Font:</source>
      <translation>Písmo:</translation>
    </message>
    <message>
      <source>Image</source>
      <translation>Obrázek</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Line</source>
      <translation>Čára</translation>
    </message>
    <message>
      <source>Polygon</source>
      <translation>Mnohoúhelník</translation>
    </message>
    <message>
      <source>Polyline</source>
      <translation>Lomená čára</translation>
    </message>
    <message>
      <source>PathText</source>
      <translation>Text na křivky</translation>
    </message>
    <message>
      <source>Page</source>
      <translation>Strana</translation>
    </message>
    <message>
      <source>Warning</source>
      <translation>Varování</translation>
    </message>
    <message>
      <source>Name &quot;%1&quot; isn't unique.
Please choose another.</source>
      <translation>Název &quot;%1&quot; není jedinečný.
Vyberte, prosím, jiný.</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Group </source>
      <translation>Seskupit</translation>
    </message>
  </context>
  <context>
    <name>ValueDialog</name>
    <message>
      <source>Insert value</source>
      <translation>Vložte hodnotu</translation>
    </message>
    <message>
      <source>Enter a value then press OK.</source>
      <translation>Vložte hodnotu a potom stiskněte OK.</translation>
    </message>
    <message>
      <source>Enter a value then press OK</source>
      <translation>Vložte hodnotu a potom stiskněte OK</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>Alt+O</source>
      <translation>Alt+O</translation>
    </message>
    <message>
      <source>Send your value to the script</source>
      <translation>Předá vaši hodnotu skriptu</translation>
    </message>
  </context>
  <context>
    <name>WerkToolB</name>
    <message>
      <source>Tools</source>
      <translation>Nástroje</translation>
    </message>
    <message>
      <source>Select Items</source>
      <translation>Vybrat položky</translation>
    </message>
    <message>
      <source>Rotate Item</source>
      <translation>Otočit položku</translation>
    </message>
    <message>
      <source>Insert Text Frame</source>
      <translation>Vložit textový rámec</translation>
    </message>
    <message>
      <source>Edit Contents of Frame</source>
      <translation>Upravit obsah rámu</translation>
    </message>
    <message>
      <source>Insert Picture</source>
      <translation>Vložit obrázek</translation>
    </message>
    <message>
      <source>Properties...</source>
      <translation>Vlastnosti...</translation>
    </message>
    <message>
      <source>Insert Polygons</source>
      <translation>Vložit mnohoúhelníky</translation>
    </message>
    <message>
      <source>Insert Lines</source>
      <translation>Vložit čáry</translation>
    </message>
    <message>
      <source>Insert Bezier Curves</source>
      <translation>Vložit Beziérovy křivky</translation>
    </message>
    <message>
      <source>Insert Freehand Line</source>
      <translation>Vložit čáru kreslenou volnou rukou</translation>
    </message>
    <message>
      <source>Link Text Frames</source>
      <translation>Vytvořit řetězení textu</translation>
    </message>
    <message>
      <source>Unlink Text Frames</source>
      <translation>Přerušit řetězení textu</translation>
    </message>
    <message>
      <source>Insert Table</source>
      <translation>Vložit tabulku</translation>
    </message>
    <message>
      <source>Zoom in or out</source>
      <translation>Zvětšit nebo zmenšit</translation>
    </message>
    <message>
      <source>Edit the text with the Story Editor</source>
      <translation>Editace textu</translation>
    </message>
    <message>
      <source>Draw various Shapes</source>
      <translation>Kreslit různé tvary</translation>
    </message>
    <message>
      <source>Do measurements</source>
      <translation>Měřit</translation>
    </message>
  </context>
  <context>
    <name>WerkToolBP</name>
    <message>
      <source>Button</source>
      <translation>Tlačítko</translation>
    </message>
    <message>
      <source>Text Field</source>
      <translation>Textové pole</translation>
    </message>
    <message>
      <source>Check Box</source>
      <translation>Políčko k zaškrtnuti</translation>
    </message>
    <message>
      <source>Combo Box</source>
      <translation>Výběr</translation>
    </message>
    <message>
      <source>List Box</source>
      <translation>Seznam</translation>
    </message>
    <message>
      <source>Text</source>
      <translation>Text</translation>
    </message>
    <message>
      <source>Link</source>
      <translation>Spojení</translation>
    </message>
    <message>
      <source>PDF Tools</source>
      <translation>PDF nástroje</translation>
    </message>
    <message>
      <source>Insert PDF Fields</source>
      <translation>Vložit PDF pole</translation>
    </message>
    <message>
      <source>Insert PDF Annotations</source>
      <translation>Vložit PDF poznámky</translation>
    </message>
  </context>
  <context>
    <name>ZAuswahl</name>
    <message>
      <source>Select Character:</source>
      <translation>Vybrat znak:</translation>
    </message>
    <message>
      <source>Insert the characters at the cursor in the text</source>
      <translation>Vložit znak na pozici kurzoru v textu</translation>
    </message>
    <message>
      <source>Delete the current selection(s).</source>
      <translation>Smazat aktuální výběr(y).</translation>
    </message>
    <message>
      <source>Close this dialog and return to text editing.</source>
      <translation>Zavřete dialog a vraťte se k editaci textu.</translation>
    </message>
    <message>
      <source>&amp;Insert</source>
      <translation>&amp;Vložit</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>Vy&amp;mazat</translation>
    </message>
    <message>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
  </context>
  <context>
    <name>gtFileDialog</name>
    <message>
      <source>Choose the importer to use</source>
      <translation>Vyberte požadovaný import</translation>
    </message>
    <message>
      <source>Automatic</source>
      <translation>Automaticky</translation>
    </message>
    <message>
      <source>Get text only</source>
      <translation>Pouze text</translation>
    </message>
    <message>
      <source>Import text without any formatting</source>
      <translation>Importovat text bez jakéhokoli formátování</translation>
    </message>
    <message>
      <source>Importer:</source>
      <translation>Importer:</translation>
    </message>
    <message>
      <source>Encoding:</source>
      <translation>Kódování:</translation>
    </message>
  </context>
  <context>
    <name>gtImporterDialog</name>
    <message>
      <source>Choose the importer to use</source>
      <translation>Vyberte požadovaný import</translation>
    </message>
    <message>
      <source></source>
      <translation> </translation>
    </message>
    <message>
      <source>Remember association</source>
      <translation>Zapamatovat si asociaci</translation>
    </message>
    <message>
      <source>Remember the file extension - importer association
and do not ask again to select an importer for
files of this type.</source>
      <translation>Pamatovat si příponu souboru tohoto typu jako asociaci
a neptat se znovu na typ importu.</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
  </context>
  <context>
    <name>nftdialog</name>
    <message>
      <source>New From Template</source>
      <translation>Nový ze šablony</translation>
    </message>
    <message>
      <source>All</source>
      <translation>Všechny</translation>
    </message>
    <message>
      <source>Name</source>
      <translation>Jméno</translation>
    </message>
    <message>
      <source>Page Size</source>
      <translation>Velikost strany</translation>
    </message>
    <message>
      <source>Colors</source>
      <translation>Barvy</translation>
    </message>
    <message>
      <source>Description</source>
      <translation>Popis</translation>
    </message>
    <message>
      <source>Usage</source>
      <translation>Použití</translation>
    </message>
    <message>
      <source>Created with</source>
      <translation>Vytvořeno v</translation>
    </message>
    <message>
      <source>Author</source>
      <translation>Autor</translation>
    </message>
    <message>
      <source>&amp;Remove</source>
      <translation>Odst&amp;ranit</translation>
    </message>
    <message>
      <source>&amp;Open</source>
      <translation>&amp;Otevřít</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
    <message>
      <source>Downloading Templates</source>
      <translation>Získat nové šablony</translation>
    </message>
    <message>
      <source>Installing Templates</source>
      <translation>Instalace šablon</translation>
    </message>
    <message>
      <source>Extract the package to the template directory ~/.scribus/templates for the current user or PREFIX/share/scribus/templates for all users in the system.</source>
      <translation>Rozbalte archiv do adresáře šablon &lt;pre>~/.scribus/templates&lt;/pre> odkud budou přístupné pouze vám nebo do &lt;pre>PREFIX/share/scribus/templates&lt;/pre> odkud je uvidí všichni uživatelé.</translation>
    </message>
    <message>
      <source>Preparing a template</source>
      <translation>Příprava šablony</translation>
    </message>
    <message>
      <source>Removing a template</source>
      <translation>Odstranění šablony</translation>
    </message>
    <message>
      <source>Translating template.xml</source>
      <translation>Překlad template.xml</translation>
    </message>
    <message>
      <source>Date</source>
      <translation>Datum</translation>
    </message>
    <message>
      <source>Document templates can be found at http://www.scribus.net/ in the Downloads section.</source>
      <translation>Šablony získáte na &lt;a href=&quot;http://www.scribus.net/&quot;>www.scribus.net&lt;/a> v sekci Download.</translation>
    </message>
    <message>
      <source>Make sure images and fonts you use can be used freely. If fonts cannot be shared do not collect them when saving as a template.</source>
      <translation>Ujistěte se, že použité obrázky mohou být použity všude. Také písma musí být zkontrolována. Jestliže písma nesmíte distribuovat, nevkládejte je do šablony. </translation>
    </message>
    <message>
      <source>The template creator should also make sure that the Installing Templates section above applies to their templates as well. This means a user should be able to download a template package and be able to extract them to the template directory and start using them.</source>
      <translation>Autor šablony by se měl také ujistit, že se jeho šablona korektně nainstaluje, což mimo jiné znamená, že se správně zachová v cizím systému.</translation>
    </message>
    <message>
      <source>Removing a template from the New From Template dialog will only remove the entry from the template.xml, it will not delete the document files. A popup menu with remove is only shown if you have write access to the template.xml file.</source>
      <translation>Jestliže odstraníte šablonu z aplikace, odstraníte pouze záznam z template.xml. Soubory zůstanou na disku. Menu s mazací položkou se zobrazí pouze tehdy, jestliže máte právo měnit soubor template.xml.</translation>
    </message>
    <message>
      <source>Copy an existing template.xml to a file called template.lang_COUNTRY.xml (use the same lang code that is present in the qm file for your language), for example template.fi.xml for Finnish language template.xml. The copy must be located in the same directory as the original template.xml so Scribus can load it.</source>
      <translation>Zkopírujte existující template.xml a přejmenujte kopii na template.lang.xml (použijte stejný kód, jaký je ve jménu QM souboru jazyka). Např. template.cs.xml bude použito v Českém prostředí. Soubor musí být ve stejném adresáři jako původní.</translation>
    </message>
  </context>
  <context>
    <name>satdialog</name>
    <message>
      <source>Save as Template</source>
      <translation>Uložit jako šablonu</translation>
    </message>
    <message>
      <source>Name</source>
      <translation>Jméno</translation>
    </message>
    <message>
      <source>Category</source>
      <translation>Kategorie</translation>
    </message>
    <message>
      <source>Page Size</source>
      <translation>Velikost strany</translation>
    </message>
    <message>
      <source>Colors</source>
      <translation>Barvy</translation>
    </message>
    <message>
      <source>Description</source>
      <translation>Popis</translation>
    </message>
    <message>
      <source>Usage</source>
      <translation>Použití</translation>
    </message>
    <message>
      <source>Author</source>
      <translation>Autor</translation>
    </message>
    <message>
      <source>Email</source>
      <translation>Email</translation>
    </message>
    <message>
      <source>More Details</source>
      <translation>Více detailů</translation>
    </message>
    <message>
      <source>OK</source>
      <translation>OK</translation>
    </message>
    <message>
      <source>Less Details</source>
      <translation>Méně detailů</translation>
    </message>
    <message>
      <source>Legal</source>
      <translation>Legal</translation>
    </message>
    <message>
      <source>Letter</source>
      <translation>Letter</translation>
    </message>
    <message>
      <source>Tabloid</source>
      <translation>Tabloid</translation>
    </message>
    <message>
      <source>landscape</source>
      <translation>na šířku</translation>
    </message>
    <message>
      <source>portrait</source>
      <translation>na výšku</translation>
    </message>
    <message>
      <source>custom</source>
      <translation>vlastní</translation>
    </message>
  </context>
  <context>
    <name>tfDia</name>
    <message>
      <source>Create filter</source>
      <translation>Vytvořit filtr</translation>
    </message>
    <message>
      <source>C&amp;lear</source>
      <translation>&amp;Vyčistit</translation>
    </message>
    <message>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <source>Choose a previously saved filter</source>
      <translation>Zvolit předchozí uložený filtr</translation>
    </message>
    <message>
      <source>Give a name to this filter for saving</source>
      <translation>Zadejte jméno filtru</translation>
    </message>
    <message>
      <source>Give a name for saving</source>
      <translation>Zadejte jméno filtru</translation>
    </message>
    <message>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
    <message>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušit</translation>
    </message>
  </context>
  <context>
    <name>tfFilter</name>
    <message>
      <source>Disable or enable this filter row</source>
      <translation>Povolit nebo zakázat tuto část filtru</translation>
    </message>
    <message>
      <source>Remove this filter row</source>
      <translation>Odstranit tuto část filtru</translation>
    </message>
    <message>
      <source>Add a new filter row</source>
      <translation>Přidat novou část filtru</translation>
    </message>
    <message>
      <source>to</source>
      <translation>na</translation>
    </message>
    <message>
      <source>and</source>
      <translation>a</translation>
    </message>
    <message>
      <source>remove match</source>
      <translation>odstranit vzor</translation>
    </message>
    <message>
      <source>do not remove match</source>
      <translation>neodstraňovat vzor</translation>
    </message>
    <message>
      <source>words</source>
      <translation>slovy</translation>
    </message>
    <message>
      <source>Remove</source>
      <translation>Odstranit</translation>
    </message>
    <message>
      <source>Replace</source>
      <translation>Nahradit</translation>
    </message>
    <message>
      <source>Apply</source>
      <translation>Použít</translation>
    </message>
    <message>
      <source>Value at the left is a regular expression</source>
      <translation>Hodnota vlevo je regulární výraz</translation>
    </message>
    <message>
      <source>with</source>
      <translation>čím</translation>
    </message>
    <message>
      <source>paragraph style</source>
      <translation>styl odstavce</translation>
    </message>
    <message>
      <source>all instances of</source>
      <translation>všechny výskyty</translation>
    </message>
    <message>
      <source>all paragraphs</source>
      <translation>všechny odstavce</translation>
    </message>
    <message>
      <source>paragraphs starting with</source>
      <translation>odstavec začíná</translation>
    </message>
    <message>
      <source>paragraphs with less than</source>
      <translation>odstavec s méně než</translation>
    </message>
    <message>
      <source>paragraphs with more than</source>
      <translation>odstavec s více než</translation>
    </message>
  </context>
</TS>
