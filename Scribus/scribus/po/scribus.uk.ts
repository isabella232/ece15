<!DOCTYPE TS><TS>
<context>
    <name></name>
    <message>
        <source>getFontSize([&quot;name&quot;]) -&gt; float

Returns the font size in points for the text frame &quot;name&quot;. If this text
frame has some text selected the value assigned to the first character of
the selection is returned.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getFontSize([&quot;name&quot;]) -&gt; float

Повертає розмір шрифта в тчк для текстової рамки з назвою &quot;name&quot;. Якщо в цій
текстовій рамці вибрано частину тексту, то функція повертає значення для
першого знака вибірки. Якщо &quot;name&quot; не вказане, буде використано активний об&apos;єкт.</translation>
    </message>
    <message>
        <source>getColorNames() -&gt; list

Returns a list containing the names of all defined colors in the document.
If no document is open, returns a list of the default document colors.
</source>
        <translation>getColorNames() -&gt; list

Повертає список імен всіх кольорів визначених в документі.
Якщо відкритий документ відсутній, повертає список основних
кольорів.</translation>
    </message>
    <message>
        <source>newDocDialog() -&gt; bool

Displays the &quot;New Document&quot; dialog box. Creates a new document if the user
accepts the settings. Does not create a document if the user presses cancel.
Returns true if a new document was created.
</source>
        <translation>newDocDialog() -&gt; bool

Показує діалогове вікно &quot;Новий Документ&quot;. Створює новий документ, якщо
користувач підтвердить установки. Не створює документ, якщо користувач
вибирає кнопку &quot;Вихід&quot;. Повернене значення дорівнює булевому &quot;так&quot;, якщо 
документ було створено.</translation>
    </message>
    <message>
        <source>getFillColor([&quot;name&quot;]) -&gt; string

Returns the name of the fill color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getFillColor([&quot;name&quot;]) -&gt; string

Повертає ім&apos;я кольору заповнення об&apos;єкту під назвою &apos;name&apos;.
Якщо &quot;name&quot; не дано, то використовується активний об&apos;єкт.</translation>
    </message>
    <message>
        <source>moveObject(dx, dy [, &quot;name&quot;])

Moves the object &quot;name&quot; by dx and dy relative to its current position. The
distances are expressed in the current measurement unit of the document (see
UNIT constants). If &quot;name&quot; is not given the currently selected item is used.
If the object &quot;name&quot; belongs to a group, the whole group is moved.
</source>
        <translation>moveObject(dx, dy [, &quot;name&quot;])

Зсовує об&apos;єкт &quot;name&quot; на dx і dy відносно до його теперішньої позиції. Відстані
визначаються активними одиницями виміру документа (див. константи Юнікс).
Якщо &quot;name&quot; не дано, то використовується активний об&apos;єкт. Якщо об&apos;єкт &quot;name&quot; 
належить до групи, то рухається вся група.
</translation>
    </message>
    <message>
        <source>setRedraw(bool)

Disables page redraw when bool = False, otherwise redrawing is enabled.
This change will persist even after the script exits, so make sure to call
setRedraw(True) in a finally: clause at the top level of your script.
</source>
        <translation>setRedraw(bool)

Відключає обновлення сторінки, якщо bool = False, в протилежному
випадку обновлення ввімкнене. Ця установка залишається в силі 
навіть після закінчення роботи сценарія. Тому в кінці сценарія
необхідно помістити виклик setRedraw(True) в умові finally: в верхньому
рівні сценарія.</translation>
    </message>
    <message>
        <source>createRect(x, y, width, height, [&quot;name&quot;]) -&gt; string

Creates a new rectangle on the current page and returns its name. The
coordinates are given in the current measurement units of the document
(see UNIT constants). &quot;name&quot; should be a unique identifier for the object
because you need this name to reference that object in future. If &quot;name&quot;
is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
</source>
        <translation>createRect(x, y, width, height, [&quot;name&quot;]) -&gt; string

Створює новий прямокутник на активній сторінці і повертаю його ім&apos;я. Координати
задаються в активних одиницях виміру документа (див. константи Юнікс). &quot;name&quot; 
має унікально ідентифікувати об&apos;єкт, тому що воно буде необхідним для звернення
до цього об&apos;єкта в майбутньому. Якщо &quot;name&quot; не вказане, то Scribus вибере його
сам.

Може повернути помилку NameExistsError якщо ви вкажете ім&apos;я, яке вже було використане.
</translation>
    </message>
    <message>
        <source>setGradientFill(type, &quot;color1&quot;, shade1, &quot;color2&quot;, shade2, [&quot;name&quot;])

Sets the gradient fill of the object &quot;name&quot; to type. Color descriptions are
the same as for setFillColor() and setFillShade(). See the constants for
available types (FILL_&lt;type&gt;).
</source>
        <translation>setGradientFill(type, &quot;color1&quot;, shade1, &quot;color2&quot;, shade2, [&quot;name&quot;])

Установлює заповнення градієнтом об&apos;єкта &quot;name&quot; типом type. Описання
кольорів застосовуються так же як і в setFillColor() та setFillShade(). Дивіться
константи для доступних типів (FILL_&lt;type&gt;).
</translation>
    </message>
    <message>
        <source>messagebarText(&quot;string&quot;)

Writes the &quot;string&quot; into the Scribus message bar (status line). The text
must be UTF8 encoded or &apos;unicode&apos; string(recommended).
</source>
        <translation>messagebarText(&quot;string&quot;)

Поміщає строкову величину &quot;string&quot; в панель повідомлень Scribus (полоса статусу). 
Текст має бути в UTF8 кодуванні або строковою величиною &apos;unicode&apos; (рекомендовано).
</translation>
    </message>
    <message>
        <source>newPage(where [,&quot;masterpage&quot;])

Creates a new page. If &quot;where&quot; is -1 the new Page is appended to the
document, otherwise the new page is inserted before &quot;where&quot;. Page numbers are
counted from 1 upwards, no matter what the displayed first page number of your
document is. The optional parameter &quot;masterpage&quot; specifies the name of the
master page for the new page.

May raise IndexError if the page number is out of range
</source>
        <translation>newPage(where [,&quot;masterpage&quot;])

Створює нову сторінку. Якщо &quot;where&quot; дорівнює -1 то нова сторінка добавляється в кінець документа. В іншому випадку вона вставляється в документ перед &quot;where&quot;. Номери сторінок внутрішньо рахуються з 1 вверх незважаючи на показаний номер документа. Необов&apos;язковий параметр &quot;masterpage&quot; вказує на ім&apos;я головної сторінки.

Може повернути помилку IndexError, якщо номер сторінки виходить за можливий діапазон
</translation>
    </message>
    <message>
        <source>importSVG(&quot;string&quot;)

The &quot;string&quot; must be a valid filename for a SVG image. The text
must be UTF8 encoded or &apos;unicode&apos; string(recommended).
</source>
        <translation>importSVG(&quot;string&quot;)

Строкова величина &quot;string&quot; повинна містити ім&quot;я файла з зображенням у форматі SVG. Текст повинет бути у кодуванні UTF8 або в строковій величині &apos;unicode&apos; str (рекоменд.).
</translation>
    </message>
    <message>
        <source>newDocument(size, margins, orientation, firstPageNumber,
                        unit, pagesType, firstPageOrder) -&gt; bool

Creates a new document and returns true if successful. The parameters have the
following meaning:

size = A tuple (width, height) describing the size of the document. You can
use predefined constants named PAPER_&lt;paper_type&gt; e.g. PAPER_A4 etc.

margins = A tuple (left, right, top, bottom) describing the document
margins

orientation = the page orientation - constants PORTRAIT, LANDSCAPE

firstPageNumer = is the number of the first page in the document used for
pagenumbering. While you&apos;ll usually want 1, it&apos;s useful to have higher
numbers if you&apos;re creating a document in several parts.

unit: this value sets the measurement units used by the document. Use a
predefined constant for this, one of: UNIT_INCHES, UNIT_MILLIMETERS,
UNIT_PICAS, UNIT_POINTS.

pagesType = One of the predefined constants PAGE_n. PAGE_1 is single page,
PAGE_2 is for double sided documents, PAGE_3 is for 3 pages fold and
PAGE_4 is 4-fold.

firstPageOrder = What is position of first page in the document.
Indexed from 0 (0 = first).

The values for width, height and the margins are expressed in the given unit
for the document. PAPER_* constants are expressed in points. If your document
is not in points, make sure to account for this.

example: newDocument(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 7, UNIT_POINTS,
PAGE_4, 3)

May raise ScribusError if is firstPageOrder bigger than allowed by pagesType.
</source>
        <translation type="obsolete">newDocument(size, margins, orientation, firstPageNumber,
                        unit, pagesType, firstPageOrder) -&gt; bool

Створює новий документ та повертає true після успішного завершення. 
Параметри мають такі значення:

size (розмір) = Тупль  (ширина, висота), який описує розмір документа. Ви
можете використовувати визначені константи типу PAPER_&lt;paper_type&gt;,
наприклад PAPER_A4 і т.п.

margins (поля) = Тупль (ліве, праве, верхнє, нижнє), який описує поля
документа.

orientation (орієнтація) = Орієнтація сторінки - константи PORTRAIT, LANDSCAPE

firstPageNumer (номер першої сторінки) = Номер першої пронумерованої сторінки 
документа. В більшості випадків рахунок починається з 1, але може бути корисним
і використання більших чисел при створенні документа з кількох частин.

unit (одиниця) = Це значення установлює одиниці виміру, які використувуються
в документі. Використовуйте попередньо визначені константи типу UNIT_INCHES, 
UNIT_MILLIMETERS, UNIT_PICAS, UNIT_POINTS.

pagesType (тип сторінок) = Одна з попередньо визначених констант PAGE_n. 
PAGE_1 - одинарна сторінка,
PAGE_2 - для двохсторонніх документів,
PAGE_3 - для 3-х сторінкових складок та
PAGE_4  - для 4-х сторінкових складок.

firstPageOrder (порядок першої сторінки) = В якій позиції знаходиться перша
пронумерована сторінка в документі. Індекс починається з 0.

Значення ширини, висоти та поля виражаються в одиницях виміру документа. 
Константи PAPER_*  виражаються в точках. Якщо Ваш документ не вимірюється
в точках, Ви маєте прийняти це до уваги.

Приклад: newDocument(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 7, UNIT_POINTS,
PAGE_4, 3)

Може повернути помилку ScribusError, якщо значення firstPageOrder виходить за
дозволений для pagesType діапазон.
</translation>
    </message>
    <message>
        <source>newDocument(size, margins, orientation, firstPageNumber,
                        unit, pagesType, firstPageOrder, numPages) -&gt; bool

Creates a new document and returns true if successful. The parameters have the
following meaning:

size = A tuple (width, height) describing the size of the document. You can
use predefined constants named PAPER_&lt;paper_type&gt; e.g. PAPER_A4 etc.

margins = A tuple (left, right, top, bottom) describing the document
margins

orientation = the page orientation - constants PORTRAIT, LANDSCAPE

firstPageNumer = is the number of the first page in the document used for
pagenumbering. While you&apos;ll usually want 1, it&apos;s useful to have higher
numbers if you&apos;re creating a document in several parts.

unit: this value sets the measurement units used by the document. Use a
predefined constant for this, one of: UNIT_INCHES, UNIT_MILLIMETERS,
UNIT_PICAS, UNIT_POINTS.

pagesType = One of the predefined constants PAGE_n. PAGE_1 is single page,
PAGE_2 is for double sided documents, PAGE_3 is for 3 pages fold and
PAGE_4 is 4-fold.

firstPageOrder = What is position of first page in the document.
Indexed from 0 (0 = first).

numPage = Number of pages to be created.

The values for width, height and the margins are expressed in the given unit
for the document. PAPER_* constants are expressed in points. If your document
is not in points, make sure to account for this.

example: newDocument(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 7, UNIT_POINTS,
PAGE_4, 3, 1)

May raise ScribusError if is firstPageOrder bigger than allowed by pagesType.
</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>@default</name>
    <message>
        <source>getFont([&quot;name&quot;]) -&gt; string

Returns the font name for the text frame &quot;name&quot;. If this text frame
has some text selected the value assigned to the first character
of the selection is returned. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation>getFont([&quot;name&quot;]) -&gt; string

Повертає ім&apos;я шрифта в текстовій рамці &quot;name&quot;. Якщо частина текста
в цій рамці виділена, то повертає значення для першого знака вибірки.
Якщо &quot;name&quot; не вказане - повертає значення для активного об&apos;єкту.</translation>
    </message>
    <message>
        <source>getTextLength([&quot;name&quot;]) -&gt; integer

Returns the length of the text in the text frame &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getTextLength([&quot;name&quot;]) -&gt; integer

Повертає довжину тексту в текстовій рамці з ім&apos;ям &quot;name&quot;.
Якщо &quot;name&quot; не вказане, то використовується активний
об&apos;єкт.</translation>
    </message>
    <message>
        <source>getText([&quot;name&quot;]) -&gt; string

Returns the text of the text frame &quot;name&quot;. If this text frame has some text
selected, the selected text is returned. All text in the frame, not just
currently visible text, is returned. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation>getText([&quot;name&quot;]) -&gt; string

Повертає текст з текстової рамки &quot;name&quot;. Якщо в цій рамці частина тексту
виділена, то повертає виділений текст. Повертає весь текст в рамці, а не 
тільки видиму частину. Якщо &quot;name&quot; не вказане, то використовується
активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getAllText([&quot;name&quot;]) -&gt; string

Returns the text of the text frame &quot;name&quot; and of all text frames which are
linked with this frame. If this textframe has some text selected, the selected
text is returned. If &quot;name&quot; is not given the currently selected item is
used.
</source>
        <translation>getAllText([&quot;name&quot;]) -&gt; string

Повертає текст із текстової рамки &quot;name&quot; і всіх текстових рамок зв&apos;язаних з нею.
Якщо в цій рамці частина тексту виділена, то повертає виділений текст. Якщо 
&quot;name&quot; не вказано, то використовується активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getLineSpacing([&quot;name&quot;]) -&gt; float

Returns the line spacing (&quot;leading&quot;) of the text frame &quot;name&quot; expressed in
points. If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getLineSpacing([&quot;name&quot;]) -&gt; float

Повертає міжрядковий інтервал (&quot;leading&quot;) текстової рамки з ім&apos;ям &quot;name&quot;,
виражений в точках. Якщо &quot;name&quot; не вказано, то використовується активний
об&apos;єкт.</translation>
    </message>
    <message>
        <source>getColumnGap([&quot;name&quot;]) -&gt; float

Returns the column gap size of the text frame &quot;name&quot; expressed in points. If
&quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getColumnGap([&quot;name&quot;]) -&gt; float

Повертає розмір інтервалу між колонками тексту в текстовій рамці &quot;name&quot;, 
виражений в точках. Якщо &quot;name&quot; не задано, використовується активний
об&apos;єкт.</translation>
    </message>
    <message>
        <source>getColumns([&quot;name&quot;]) -&gt; integer

Gets the number of columns of the text frame &quot;name&quot;. If &quot;name&quot; is not
given the currently selected item is used.
</source>
        <translation>getColumns([&quot;name&quot;]) -&gt; integer

Повертає число колонок тексту в текстовій рамці &quot;name&quot;. Якщо &quot;name&quot; 
не вказано, використовується активний об&apos;єкт.</translation>
    </message>
    <message>
        <source>setText(&quot;text&quot;, [&quot;name&quot;])

Sets the text of the text frame &quot;name&quot; to the text of the string &quot;text&quot;.
Text must be UTF8 encoded - use e.g. unicode(text, &apos;iso-8859-2&apos;). See the FAQ
for more details. If &quot;name&quot; is not given the currently selected item is
used.
</source>
        <translation>setText(&quot;text&quot;, [&quot;name&quot;])

Змінює текст в текстовій рамці &quot;name&quot; на зміст текстової змінної &quot;text&quot;.
Текст має бути в кодуванні UTF8 - використовуйте, наприклад, 
unicode(text, &apos;iso-8859-2&apos;). Додаткова інформація по цьому приводу
розміщена в часто задаваних питаннях. Якщо &quot;name&quot; не вказано, то
використовується активний об&apos;єкт.</translation>
    </message>
    <message>
        <source>setFont(&quot;font&quot;, [&quot;name&quot;])

Sets the font of the text frame &quot;name&quot; to &quot;font&quot;. If there is some text
selected only the selected text is changed.  If &quot;name&quot; is not given the
currently selected item is used.

May throw ValueError if the font cannot be found.
</source>
        <translation>setFont(&quot;font&quot;, [&quot;name&quot;])

Установлює шрифт текстової рамки &quot;name&quot; до &quot;font&quot;. Якщо вибрана лише 
частина тексту в рамці то зміна шрифта відноситься лише до неї. Якщо  
&quot;name&quot; не вказано, то використовується активний об&apos;єкт.

Може повернути ValueError, якщо шрифт не може бути знайдено.
</translation>
    </message>
    <message>
        <source>setFontSize(size, [&quot;name&quot;])

Sets the font size of the text frame &quot;name&quot; to &quot;size&quot;. &quot;size&quot; is treated
as a value in points. If there is some text selected only the selected text is
changed. &quot;size&quot; must be in the range 1 to 512. If &quot;name&quot; is not given the
currently selected item is used.

May throw ValueError for a font size that&apos;s out of bounds.
</source>
        <translation>setFontSize(size, [&quot;name&quot;])

Установлює розмір шрифта в текстовій рамці &quot;name&quot; до розміру &quot;size&quot;. 
Значення &quot;size&quot; визначається в точках. Якщо в рамці вибрана частина
тексту, то зміна розміру шрифта відноситься лише до неї. Діапазон &quot;size&quot; 
від 1 до 512. Якщо &quot;name&quot; не вказано, то використовується активний
об&apos;єкт.

Може повернути помилку ValueError, якщо розмір шрифта виходить за
дозволений діапазон.</translation>
    </message>
    <message>
        <source>setLineSpacing(size, [&quot;name&quot;])

Sets the line spacing (&quot;leading&quot;) of the text frame &quot;name&quot; to &quot;size&quot;.
&quot;size&quot; is a value in points. If &quot;name&quot; is not given the currently selected
item is used.

May throw ValueError if the line spacing is out of bounds.
</source>
        <translation>setLineSpacing(size, [&quot;name&quot;])

Установлює міжрядковий інтервал (початковий) в текстовій рамці &quot;name&quot;
до розміру &quot;size&quot;. Значення &quot;size&quot; виражається в точках. Якщо &quot;name&quot; не
вказано, використовується активний об&apos;єкт.

Може повернути помилку ValueError, якщо значення інтервалу виходить
за доступний діапазон.
</translation>
    </message>
    <message>
        <source>setColumnGap(size, [&quot;name&quot;])

Sets the column gap of the text frame &quot;name&quot; to the value &quot;size&quot;. If
&quot;name&quot; is not given the currently selected item is used.

May throw ValueError if the column gap is out of bounds (must be positive).
</source>
        <translation>setColumnGap(size, [&quot;name&quot;])

Установлює проміжок між колонками в текстовій рамці &quot;name&quot; до значення
&quot;size&quot;. Якщо &quot;name&quot; не задано, використовується активний об&apos;єкт.

Може повернути помилку ValueError, якщо проміжок між колонками виходить
за доступний діапазон (повинен бути позитивним).
</translation>
    </message>
    <message>
        <source>setColumns(nr, [&quot;name&quot;])

Sets the number of columns of the text frame &quot;name&quot; to the integer &quot;nr&quot;.
If &quot;name&quot; is not given the currently selected item is used.

May throw ValueError if number of columns is not at least one.
</source>
        <translation>setColumns(nr, [&quot;name&quot;])

Установлює число колонок в текстовій рамці &quot;name&quot; до цілого числа &quot;nr&quot;.
Якщо &quot;name&quot; не задано, використовується активний об&apos;єкт.

Може повернути помилку ValueError, якщо не вказана хоч одна колонка.
</translation>
    </message>
    <message>
        <source>setTextAlignment(align, [&quot;name&quot;])

Sets the text alignment of the text frame &quot;name&quot; to the specified alignment.
If &quot;name&quot; is not given the currently selected item is used. &quot;align&quot; should
be one of the ALIGN_ constants defined in this module - see dir(scribus).

May throw ValueError for an invalid alignment constant.
</source>
        <translation>setTextAlignment(align, [&quot;name&quot;])

Установлює вирівнювання тексту в текстовій рамці &quot;name&quot; до вказаного.
Якщо &quot;name&quot; не вказано, використовується активний об&apos;єкт. &quot;align&quot; повинне
дорівнювати одній з констант ALIGN_ constants визначених в цьому модулі -
дивіться в dir(scribus).

Може повернути помилку ValueError, якщо константа вирівнювання задана
невірно.
</translation>
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

Вибирає &quot;count&quot; число знаків тексту в текстовій рамці &quot;name&quot;, починаючи з
знака &quot;start&quot;. Рахунок знаків починається з 0. Якщо &quot;count&quot; дорівнює нулю,
текстова вибірка буде знята. Якщо &quot;name&quot; не задано, буде використано
активний об&apos;єкт.

Може повернути помилку IndexError, якщо вибірка виходить за межі 
тексту.
</translation>
    </message>
    <message>
        <source>deleteText([&quot;name&quot;])

Deletes any text in the text frame &quot;name&quot;. If there is some text selected,
only the selected text will be deleted. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation>deleteText([&quot;name&quot;])

Видаляє весь текст в текстовій рамці &quot;name&quot;. Якщо частина тексту вибрана
то видаляється лише вона. Якщо &quot;name&quot; не задано, використовується
активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>setTextColor(&quot;color&quot;, [&quot;name&quot;])

Sets the text color of the text frame &quot;name&quot; to the color &quot;color&quot;. If there
is some text selected only the selected text is changed. If &quot;name&quot; is not
given the currently selected item is used.
</source>
        <translation>setTextColor(&quot;color&quot;, [&quot;name&quot;])

Установлює колір тексту в текстовій рамці &quot;name&quot; до кольору &quot;color&quot;. Якщо
частина тексту вибрана - змінюється лише вона. Якщо &quot;name&quot; не задано,
використовується активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>setTextStroke(&quot;color&quot;, [&quot;name&quot;])

Set &quot;color&quot; of the text stroke. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation>setTextStroke(&quot;color&quot;, [&quot;name&quot;])

Установлює колір &quot;color&quot; текстового контура. Якщо &quot;name&quot; не задано,
використовується активний об&apos;єкт.
</translation>
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

Установлює тінь кольору тексту об&apos;єкта &quot;name&quot; до &quot;shade&quot;. Якщо
частина тексту вибрана - змінюється лише вона. &quot;shade&quot; має бути
цілим числом від 0 (найсвітліша) до 100 (повна насиченість кольору).
Якщо &quot;name&quot; не задано, використовується активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>linkTextFrames(&quot;fromname&quot;, &quot;toname&quot;)

Link two text frames. The frame named &quot;fromname&quot; is linked to the
frame named &quot;toname&quot;. The target frame must be an empty text frame
and must not link to or be linked from any other frames already.

May throw ScribusException if linking rules are violated.
</source>
        <translation>linkTextFrames(&quot;fromname&quot;, &quot;toname&quot;)

Зв&apos;язує дві текстові рамки. Рамка з ім&apos;ям &quot;fromname&quot; приєднується до
рамки з ім&apos;ям &quot;toname&quot;. Кінцева рамка має бути пустою текстовою
рамкою і не повинна бути з&apos;єднана ні з якою іншою рамкою.

Може повернути помилку ScribusException, якщо відбувається порушення
правил зв&apos;язування рамок.
</translation>
    </message>
    <message>
        <source>unlinkTextFrames(&quot;name&quot;)

Remove the specified (named) object from the text frame flow/linkage. If the
frame was in the middle of a chain, the previous and next frames will be
connected, eg &apos;a-&gt;b-&gt;c&apos; becomes &apos;a-&gt;c&apos; when you unlinkTextFrames(b)&apos;

May throw ScribusException if linking rules are violated.
</source>
        <translation>unlinkTextFrames(&quot;name&quot;)

Видаляє вказаний (названий) об&apos;єкт з ланцюжка зв&apos;язаних текстових
рамок. Якщо рамка знаходиться всередині ланцюжка, то рамки, які
знаходилися перед і після неї будуть з&apos;єднані, наприклад &apos;a-&gt;b-&gt;c&apos; 
зміниться на &apos;a-&gt;c&apos;, при виконанні unlinkTextFrames(b)&apos;

Може повернути помилку ScribusException при порушенні правил
з&apos;єднання рамок.
</translation>
    </message>
    <message>
        <source>traceText([&quot;name&quot;])

Convert the text frame &quot;name&quot; to outlines. If &quot;name&quot; is not given the
currently selected item is used.</source>
        <translation>traceText([&quot;name&quot;])

Конвертує текстову рамку &quot;name&quot; в контурний текст. Якщо &quot;name&quot; 
не вказано, використовується активний об&apos;єкт.</translation>
    </message>
    <message>
        <source>getColor(&quot;name&quot;) -&gt; tuple

Returns a tuple (C, M, Y, K) containing the four color components of the
color &quot;name&quot; from the current document. If no document is open, returns
the value of the named color from the default document colors.

May raise NotFoundError if the named color wasn&apos;t found.
May raise ValueError if an invalid color name is specified.
</source>
        <translation>getColor(&quot;name&quot;) -&gt; tuple

Повертає тупль (C, M, Y, K), який містить чотири складових
кольору &quot;name&quot; з активного документа. Якщо не відкрито
жодного документа, повертає значення для названого
кольору з палітри стандартних кольорів.

Може повернути помилку NotFoundError, якщо названий колір не знайдено.
Може повернути помилку ValueError, якщо було вказано недійсне ім&apos;я кольору.
</translation>
    </message>
    <message>
        <source>changeColor(&quot;name&quot;, c, m, y, k)

Changes the color &quot;name&quot; to the specified CMYK value. The color value is
defined via four components c = Cyan, m = Magenta, y = Yellow and k = Black.
Color components should be in the range from 0 to 255.

May raise NotFoundError if the named color wasn&apos;t found.
May raise ValueError if an invalid color name is specified.
</source>
        <translation>changeColor(&quot;name&quot;, c, m, y, k)

Змінює колір &quot;name&quot; до вказаних значень CMYK. Значення кольору
визначається його чотирма компонентами c = Cyan (салатовий),
m = Magenta (малиновий), y = Yellow (жовтий) та k = Black (чорний).
Значення складових кольору повинні знаходитися в діапазоні від
0 до 255.

Може повернути помилку NotFoundError, якщо названий колір не знайдено.
Може повернути помилку ValueError, якщо було вказано недійсне ім&apos;я кольору.
</translation>
    </message>
    <message>
        <source>deleteColor(&quot;name&quot;, &quot;replace&quot;)

Deletes the color &quot;name&quot;. Every occurence of that color is replaced by the
color &quot;replace&quot;. If not specified, &quot;replace&quot; defaults to the color
&quot;None&quot; - transparent.

deleteColor works on the default document colors if there is no document open.
In that case, &quot;replace&quot;, if specified, has no effect.

May raise NotFoundError if a named color wasn&apos;t found.
May raise ValueError if an invalid color name is specified.
</source>
        <translation>deleteColor(&quot;name&quot;, &quot;replace&quot;)

Видаляє колір &quot;name&quot;. Кожний приклад цього кольору заміняється на колір
&quot;replace&quot;. Якщо &quot;replace&quot; не вказано, то використовується колір &quot;None&quot; - прозорість.

deleteColor змінює стандартні кольори при відсутності відчинених документів. В
цьому випадку &quot;replace&quot;, якщо вказаний, ефекту не має.

Може повернути помилку NotFoundError, якщо названий колір не знайдено.
Може повернути помилку ValueError, якщо було вказано недійсне ім&apos;я кольору.</translation>
    </message>
    <message>
        <source>replaceColor(&quot;name&quot;, &quot;replace&quot;)

Every occurence of the color &quot;name&quot; is replaced by the color &quot;replace&quot;.

May raise NotFoundError if a named color wasn&apos;t found.
May raise ValueError if an invalid color name is specified.
</source>
        <translation>replaceColor(&quot;name&quot;, &quot;replace&quot;)

Кожний приклад кольору &quot;name&quot; заміняється на колір &quot;replace&quot;.

Може повернути помилку NotFoundError, якщо названий колір не знайдено.
Може повернути помилку ValueError, якщо було вказано недійсне ім&apos;я кольору.</translation>
    </message>
    <message>
        <source>messageBox(&quot;caption&quot;, &quot;message&quot;,
    icon=ICON_NONE, button1=BUTTON_OK|BUTTONOPT_DEFAULT,
    button2=BUTTON_NONE, button3=BUTTON_NONE) -&gt; integer

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
result = messageBox(&apos;Script failed&apos;,
                    &apos;This script only works when you have a text frame selected.&apos;,
                    ICON_ERROR)
result = messageBox(&apos;Monkeys!&apos;, &apos;Something went ook! &lt;i&gt;Was it a monkey?&lt;/i&gt;&apos;,
                    ICON_WARNING, BUTTON_YES|BUTTONOPT_DEFAULT,
                    BUTTON_NO, BUTTON_IGNORE|BUTTONOPT_ESCAPE)

Defined button and icon constants:
BUTTON_NONE, BUTTON_ABORT, BUTTON_CANCEL, BUTTON_IGNORE, BUTTON_NO,
BUTTON_NOALL, BUTTON_OK, BUTTON_RETRY, BUTTON_YES, BUTTON_YESALL,
ICON_NONE, ICON_INFORMATION, ICON_WARNING, ICON_CRITICAL.
</source>
        <translation>messageBox(&quot;caption&quot;, &quot;message&quot;,
    icon=ICON_NONE, button1=BUTTON_OK|BUTTONOPT_DEFAULT,
    button2=BUTTON_NONE, button3=BUTTON_NONE) -&gt; ціле число

Показує діалогове вікно з заголовком &quot;caption&quot;, повідомленням &quot;message&quot;, 
та іконкою &quot;icon&quot; та до 3-х кнопок. По умовчанню іконка не використовується, 
присутня лише проста кнопка &quot;Гаразд&quot;. Обов&apos;язковими являються лише 
аргументи &quot;caption&quot; та &quot;message&quot;, хоча установка іконки та відповідних
кнопок настійливо рекомендується. Текст повідомлення може містити
просту розмітку по типу HTML.

Повертає номер кнопки, натиснутої користувачем. Номера кнопок
починаються з 1.

Для іконок та кнопок існують наперед визначені константи з іменами 
описаними в документації по Qt. Вони включають BUTTON_* та
ICON_* константи, визначені в модулі. Додатково є ще дві константи,
для яких може бути виконана бінарна логічна операція OR з константами
кнопок
    BUTTONOPT_DEFAULT  Натискування клавіші &quot;Ввід&quot; (Enter) натискує цю кнопку.
    BUTTONOPT_ESCAPE    Натискування клавіші &quot;Відміна&quot; (Escape) натискує цю кнопку.

Приклади використання:
result = messageBox(&apos;Script failed&apos;,
                    &apos;Цей скрипт працює лише при наявності вибраної текстової рамки.&apos;,
                    ICON_ERROR)
result = messageBox(&apos;Мавпи!&apos;, &apos;Сталося щось негарне! &lt;i&gt;Це була мавпа?&lt;/i&gt;&apos;,
                    ICON_WARNING, BUTTON_YES|BUTTONOPT_DEFAULT,
                    BUTTON_NO, BUTTON_IGNORE|BUTTONOPT_ESCAPE)

Визначені константи кнопок та іконок:
BUTTON_NONE, BUTTON_ABORT, BUTTON_CANCEL, BUTTON_IGNORE, BUTTON_NO,
BUTTON_NOALL, BUTTON_OK, BUTTON_RETRY, BUTTON_YES, BUTTON_YESALL,
ICON_NONE, ICON_INFORMATION, ICON_WARNING, ICON_CRITICAL.</translation>
    </message>
    <message>
        <source>valueDialog(caption, message [,defaultvalue]) -&gt; string

Shows the common &apos;Ask for string&apos; dialog and returns its value as a string
Parameters: window title, text in the window and optional &apos;default&apos; value.

Example: valueDialog(&apos;title&apos;, &apos;text in the window&apos;, &apos;optional&apos;)
</source>
        <translation>valueDialog(caption, message [,defaultvalue]) -&gt; строкова величина

Показує стандартний &apos;Введіть строкову величину&apos; діалог та повертає
отримане значення, як строкову величину
Параметри: заголовок вікна, текст у вікні та необов&apos;язкове &apos;значення 
по умовчанню&apos; (default).

Приклад: valueDialog(&apos;заголовок&apos;, &apos;текст у вікні&apos;, &apos;необов&quot;язкове значення&apos;)
</translation>
    </message>
    <message>
        <source>closeDoc()

Closes the current document without prompting to save.

May throw NoDocOpenError if there is no document to close
</source>
        <translation>closeDoc()

Зачиняє активний документ без запиту про запис.

Може повернути помилку NoDocOpenError при відсутності
документа для зачиняння
</translation>
    </message>
    <message>
        <source>haveDoc() -&gt; bool

Returns true if there is a document open.
</source>
        <translation>haveDoc() -&gt; булеве значення

Повертає правдиве булеве значення при 
наявності відчиненого документа.</translation>
    </message>
    <message>
        <source>openDoc(&quot;name&quot;)

Opens the document &quot;name&quot;.

May raise ScribusError if the document could not be opened.
</source>
        <translation>openDoc(&quot;name&quot;)

Відчиняє документ &quot;name&quot;.

Може повернути помилку ScribusError, якщо документ не можна
було відчинити.
</translation>
    </message>
    <message>
        <source>saveDoc()

Saves the current document with its current name, returns true if successful.
If the document has not already been saved, this may bring up an interactive
save file dialog.

If the save fails, there is currently no way to tell.
</source>
        <translation>saveDoc()

Записує активний документ під його теперішнім іменем, повертає
правдиве булеве значення при успішному завершенні операції.
Якщо документ ще не був записаний, може викликати інтерактивний
діалог збереження файла.

В даний час неможливо визначити чи запис був успішним.
</translation>
    </message>
    <message>
        <source>saveDocAs(&quot;name&quot;)

Saves the current document under the new name &quot;name&quot; (which may be a full or
relative path).

May raise ScribusError if the save fails.
</source>
        <translation>saveDocAs(&quot;name&quot;)

Записує активний документ під новим ім&apos;ям &quot;name&quot;, яке може бути
повним або відносним шляхом.

Може повернути помилку ScribusError, якщо запис не буде успішним.
</translation>
    </message>
    <message>
        <source>saveDocAs(&quot;author&quot;, &quot;info&quot;, &quot;description&quot;) -&gt; bool

Sets the document information. &quot;Author&quot;, &quot;Info&quot;, &quot;Description&quot; are
strings.
</source>
        <translation type="obsolete">saveDocAs(&quot;author&quot;, &quot;info&quot;, &quot;description&quot;) -&gt; булеве значення

Установлює опис документа. &quot;Author (&quot;Автор&quot;), &quot;Info&quot; (&quot;Інформація&quot;),
&quot;Description&quot; (&quot;Опис&quot;) є строковими величинами.
</translation>
    </message>
    <message>
        <source>setMargins(lr, rr, tr, br)

Sets the margins of the document, Left(lr), Right(rr), Top(tr) and Bottom(br)
margins are given in the measurement units of the document - see UNIT_&lt;type&gt;
constants.
</source>
        <translation>setMargins(lr, rr, tr, br)

Установлює поля документа, Ліве (lr), Праве (rr), Верхнє (tr) та Нижнє (br)
поля задаються в одиницях виміру документа - див. UNIT_&lt;type&gt;
константи.
</translation>
    </message>
    <message>
        <source>setUnit(type)

Changes the measurement unit of the document. Possible values for &quot;unit&quot; are
defined as constants UNIT_&lt;type&gt;.

May raise ValueError if an invalid unit is passed.
</source>
        <translation>setUnit(type)

Установлює одиницю виміру документа. Можливі значення для &quot;unit&quot; 
визначаються як константи UNIT_&lt;type&gt;.

Може повернути помилку ValueError, якщо було задано невірну одиницю
виміру.
</translation>
    </message>
    <message>
        <source>getUnit() -&gt; integer (Scribus unit constant)

Returns the measurement units of the document. The returned value will be one
of the UNIT_* constants:
UNIT_INCHES, UNIT_MILLIMETERS, UNIT_PICAS, UNIT_POINTS.
</source>
        <translation>getUnit() -&gt; integer (Scribus unit constant)

Повертає одиниці виміру документа. Повернене значення буде однією з
констант UNIT_* constants:
UNIT_INCHES, UNIT_MILLIMETERS, UNIT_PICAS, UNIT_POINTS.
</translation>
    </message>
    <message>
        <source>loadStylesFromFile(&quot;filename&quot;)

Loads paragraph styles from the Scribus document at &quot;filename&quot; into the
current document.
</source>
        <translation>loadStylesFromFile(&quot;filename&quot;)

Завантажує стилі абзаців з документу Scribus &quot;filename&quot; в активний документ.
</translation>
    </message>
    <message>
        <source>setDocType(facingPages, firstPageLeft)

Sets the document type. To get facing pages set the first parameter to
FACINGPAGES, to switch facingPages off use NOFACINGPAGES instead.  If you want
to be the first page a left side set the second parameter to FIRSTPAGELEFT, for
a right page use FIRSTPAGERIGHT.
</source>
        <translation>setDocType(facingPages, firstPageLeft)

Установлює тип документа. Для задання книжкового розташування сторінок
установіть перший параметр до FACINGPAGES, а для відміни замість facingPages 
використайте NOFACINGPAGES. Щоб перша сторінка була зліва установіть
другий параметр до FIRSTPAGELEFT, а справа - FIRSTPAGERIGHT.
</translation>
    </message>
    <message>
        <source>getLineColor([&quot;name&quot;]) -&gt; string

Returns the name of the line color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getLineColor([&quot;name&quot;]) -&gt; строкове значення

Повертає назву кольорі ліній об&apos;єкту &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getLineWidth([&quot;name&quot;]) -&gt; integer

Returns the line width of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
        <translation>getLineWidth([&quot;name&quot;]) -&gt; ціле число

Повертає товщину лінії об&apos;єкта &quot;name&quot;. Якщо &quot;name&quot;
не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getLineShade([&quot;name&quot;]) -&gt; integer

Returns the shading value of the line color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getLineShade([&quot;name&quot;]) -&gt; ціле число

Повертає значення затінення об&apos;єкта &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getLineJoin([&quot;name&quot;]) -&gt; integer (see contants)

Returns the line join style of the object &quot;name&quot;. If &quot;name&quot; is not given
the currently selected item is used.  The join types are:
JOIN_BEVEL, JOIN_MITTER, JOIN_ROUND
</source>
        <translation>getLineJoin([&quot;name&quot;]) -&gt; ціле число (див. умови)

Повертає стиль з&apos;єднань ліній об&apos;єкта &quot;name&quot;. Якщо &quot;name&quot; не
задано, буде використано активний об&apos;єкт. Типи з&apos;єднать:
JOIN_BEVEL (фасочне), JOIN_MITTER (фацеточне), JOIN_ROUND (закруглене)
</translation>
    </message>
    <message>
        <source>getLineEnd([&quot;name&quot;]) -&gt; integer (see constants)

Returns the line cap style of the object &quot;name&quot;. If &quot;name&quot; is not given the
currently selected item is used. The cap types are:
CAP_FLAT, CAP_ROUND, CAP_SQUARE
</source>
        <translation>getLineEnd([&quot;name&quot;]) -&gt; ціле число (див. умови)

Повертає стиль кінців ліній об&apos;єкта &quot;name&quot;. Якщо &quot;name&quot; не
задано, буде використано активний об&apos;єкт. Типи кінців:
CAP_FLAT (плаский), CAP_ROUND (заокруглений), CAP_SQUARE (квадратний)
</translation>
    </message>
    <message>
        <source>getLineStyle([&quot;name&quot;]) -&gt; integer (see constants)

Returns the line style of the object &quot;name&quot;. If &quot;name&quot; is not given the
currently selected item is used. Line style constants are:
LINE_DASH, LINE_DASHDOT, LINE_DASHDOTDOT, LINE_DOT, LINE_SOLID
</source>
        <translation>getLineStyle([&quot;name&quot;]) -&gt; ціле число (див. обмеження)

Повертає стиль ліній об&apos;єкта &quot;name&quot;. Якщо &quot;name&quot; не задано, буде 
використано активний об&apos;єкт. Обмеження типів ліній:
LINE_DASH (пунктирна), LINE_DASHDOT (пунктир-крапка), 
LINE_DASHDOTDOT (пунктир-крапка-крапка), LINE_DOT (крапка),
LINE_SOLID (суцільна)
</translation>
    </message>
    <message>
        <source>getFillShade([&quot;name&quot;]) -&gt; integer

Returns the shading value of the fill color of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getFillShade([&quot;name&quot;]) -&gt; integer

Повертає значення затінення кольору заповнення об&apos;єкта &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getImageScale([&quot;name&quot;]) -&gt; (x,y)

Returns a (x, y) tuple containing the scaling values of the image frame
&quot;name&quot;.  If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation>getImageScale([&quot;name&quot;]) -&gt; (x,y)

Повертає тупль (x, y), який містить значення масштабу рамки для зображень
&quot;name&quot;.  Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getImageName([&quot;name&quot;]) -&gt; string

Returns the filename for the image in the image frame. If &quot;name&quot; is not
given the currently selected item is used.
</source>
        <translation>getImageName([&quot;name&quot;]) -&gt; строкове значення

Повертає ім&apos;я файла для зображення в рамці для зображень. Якщо &quot;name&quot; 
не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getSize([&quot;name&quot;]) -&gt; (width,height)

Returns a (width, height) tuple with the size of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used. The size is
expressed in the current measurement unit of the document - see UNIT_&lt;type&gt;
for reference.
</source>
        <translation>getSize([&quot;name&quot;]) -&gt; (ширина,висота)

Повертає тупль (ширина,висота) з розміром об&apos;єкта &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт. Розмір
виражається в активних одиницях виміру документа - див.  UNIT_&lt;type&gt;
для подальшої інформації.
</translation>
    </message>
    <message>
        <source>getRotation([&quot;name&quot;]) -&gt; integer

Returns the rotation of the object &quot;name&quot;. The value is expressed in degrees,
and clockwise is positive. If &quot;name&quot; is not given the currently selected item
is used.
</source>
        <translation>getRotation([&quot;name&quot;]) -&gt; ціле число

Повертає кут повороту об&apos;єкта &quot;name&quot;. Значення виражається в градусах 
і поворот по часовії стрілці є позитивним. Якщо &quot;name&quot; не задано, буде
використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getAllObjects() -&gt; list

Returns a list containing the names of all objects on the current page.
</source>
        <translation>getAllObjects() -&gt; список

Повертає список, що містить імена всіх об&apos;єктів на активній сторінці.
</translation>
    </message>
    <message>
        <source>moveObjectAbs(x, y [, &quot;name&quot;])

Moves the object &quot;name&quot; to a new location. The coordinates are expressed in
the current measurement unit of the document (see UNIT constants).  If &quot;name&quot;
is not given the currently selected item is used.  If the object &quot;name&quot;
belongs to a group, the whole group is moved.
</source>
        <translation>moveObjectAbs(x, y [, &quot;name&quot;])

Переміщує об&apos;єкт &quot;name&quot;  в нове місце. Координати виражаються в
активних одиницях виміру документа (див. константи UNIT).  Якщо 
&quot;name&quot; не задано, буде використано активний об&apos;єкт. Якщо об&apos;єкт 
&quot;name&quot; є частиною групи, переміщається вся група.
</translation>
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

Відносно повертає об&apos;єкт &quot;name&quot; на &quot;rot&quot; градусів. Об&apos;єкт повертається
навколо вортекса, який є активно вибраною точкою обертання. По
умовчанню верхній лівий вортекс при нульовому куті повороту. 
Позитивні значення означають поворот проти часової стрілки при
використанні точки обертання по умовчанню. Якщо &quot;name&quot; не задано, 
буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>sizeObject(width, height [, &quot;name&quot;])

Resizes the object &quot;name&quot; to the given width and height. If &quot;name&quot;
is not given the currently selected item is used.
</source>
        <translation>sizeObject(ширина, висота [, &quot;name&quot;])

Змінює розмір об&apos;єкта &quot;name&quot; до вказаної висоти та ширини. Якщо 
&quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getSelectedObject([nr]) -&gt; string

Returns the name of the selected object. &quot;nr&quot; if given indicates the number
of the selected object, e.g. 0 means the first selected object, 1 means the
second selected Object and so on.
</source>
        <translation>getSelectedObject([nr]) -&gt; строкова величина

Повертає ім&apos;я вибраного об&apos;єкта. &quot;nr&quot;, якщо задано, вказує на індекс
вибраного об&apos;єкта, напр. 0 означає перший вибраний об&apos;єкт, 1 означає
другий вибраний об&apos;єкт і так далі.
</translation>
    </message>
    <message>
        <source>selectionCount() -&gt; integer

Returns the number of selected objects.
</source>
        <translation>selectionCount() -&gt; ціле число

Повертає число вибраних об&apos;єктів.
</translation>
    </message>
    <message>
        <source>selectObject(&quot;name&quot;)

Selects the object with the given &quot;name&quot;.
</source>
        <translation>selectObject(&quot;name&quot;)

Повертає об&apos;єкт з даним іменем &quot;name&quot;.
</translation>
    </message>
    <message>
        <source>deselectAll()

Deselects all objects in the whole document.
</source>
        <translation>deselectAll()

Відмінює вибір всіх об&apos;єктів у всьому документі.
</translation>
    </message>
    <message>
        <source>groupObjects(list)

Groups the objects named in &quot;list&quot; together. &quot;list&quot; must contain the names
of the objects to be grouped. If &quot;list&quot; is not given the currently selected
items are used.
</source>
        <translation>groupObjects(list)

Згруповує об&apos;єкти названі в списку &quot;list&quot;. &quot;list&quot; повинен містити імена
об&apos;єктів, які будуть згруповані. Якщо &quot;list&quot; не задано, буде 
використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>unGroupObjects(&quot;name&quot;)

Destructs the group the object &quot;name&quot; belongs to.If &quot;name&quot; is not given the currently selected item is used.</source>
        <translation>unGroupObjects(&quot;name&quot;)

Видаляє групу, яка містить об&apos;єкт з іменем &quot;name&quot;. Якщо &quot;name&quot; не задано, 
буде використано активний об&apos;єкт.</translation>
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

Змінює розмір групи, яка містить об&apos;єкт &quot;name&quot;. Значення понад 1 збільшують 
розмір, а значення менші за 1 його зменшують, напр. значення 0.5 змінює
розмір групи до 50 % початкового, а значення 1.5 змінює розмір до 150 % 
початкового. Значення &quot;factor&quot; повинне бути більшим за 0. Якщо &quot;name&quot; не
задано, буде використано активний об&apos;єкт.

Може повернути помилку ValueError, якщо задано недійсний фактор масштабу.
</translation>
    </message>
    <message>
        <source>loadImage(&quot;filename&quot; [, &quot;name&quot;])

Loads the picture &quot;picture&quot; into the image frame &quot;name&quot;. If &quot;name&quot; is
not given the currently selected item is used.

May raise WrongFrameTypeError if the target frame is not an image frame
</source>
        <translation>loadImage(&quot;filename&quot; [, &quot;name&quot;])

Завантажує зображення &quot;picture&quot; в рамку для зображень &quot;name&quot;. Якщо 
&quot;name&quot; не задано, буде використано активний об&apos;єкт.

Може повернути помилку WrongFrameTypeError, якщо рамка не є рамкою
для зображень
</translation>
    </message>
    <message>
        <source>scaleImage(x, y [, &quot;name&quot;])

Sets the scaling factors of the picture in the image frame &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used. A number of 1
means 100 %.

May raise WrongFrameTypeError if the target frame is not an image frame
</source>
        <translation>scaleImage(x, y [, &quot;name&quot;])

Установлює масштаб зображення в рамці для зображень &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт. Число 1
дорівнює 100 %.

Може повернути помилку WrongFrameTypeError, якщо рамка не є 
рамкою для зображень 
</translation>
    </message>
    <message>
        <source>lockObject([&quot;name&quot;]) -&gt; bool

Locks the object &quot;name&quot; if it&apos;s unlocked or unlock it if it&apos;s locked.
If &quot;name&quot; is not given the currently selected item is used. Returns true
if locked.
</source>
        <translation>lockObject([&quot;name&quot;]) -&gt; bool

Замикає об&apos;єкт &quot;name&quot;, якщо він незамкнений, і навпаки. Якщо 
&quot;name&quot; не задано, буде використано активний об&apos;єкт. Повертає
булеве значення &quot;true&quot;, якщо об&apos;єкт замкнений.
</translation>
    </message>
    <message>
        <source>isLocked([&quot;name&quot;]) -&gt; bool

Returns true if is the object &quot;name&quot; locked.  If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation>isLocked([&quot;name&quot;]) -&gt; bool

Повертає булеве значення &quot;true&quot;, якщо об&apos;єкт замкнений. Якщо 
&quot;name&quot; не задано, буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getFontNames() -&gt; list

Returns a list with the names of all available fonts.
</source>
        <translation>getFontNames() -&gt; list

Повертає список з назвами доступних шрифтів.
</translation>
    </message>
    <message>
        <source>getXFontNames() -&gt; list of tuples

Returns a larger font info. It&apos;s a list of the tuples with:
[ (Scribus name, Family, Real name, subset (1|0), embed PS (1|0), font file), (...), ... ]
</source>
        <translation>getXFontNames() -&gt; список туплів

Повертає додаткову інформацію про шрифти у вигляді списка туплів:
[ (Назва шрифта в Scribus, гарнітура, справжня назва, вибірка (1|0), 
вбудований PS (1|0), файл з шрифтом), (...), ... ]
</translation>
    </message>
    <message>
        <source>getLayers() -&gt; list

Returns a list with the names of all defined layers.
</source>
        <translation>getLayers() -&gt; list

Повертає список з назвами всіх визначених планів.
</translation>
    </message>
    <message>
        <source>setActiveLayer(&quot;name&quot;)

Sets the active layer to the layer named &quot;name&quot;.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>setActiveLayer(&quot;name&quot;)

Установлює &quot;name&quot;, як активний план.

Може повернути помилку NotFoundError, якщо план не знайдено.
Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>getActiveLayer() -&gt; string

Returns the name of the current active layer.
</source>
        <translation>getActiveLayer() -&gt; string

Повертає назву активного плану.
</translation>
    </message>
    <message>
        <source>sentToLayer(&quot;layer&quot; [, &quot;name&quot;])

Sends the object &quot;name&quot; to the layer &quot;layer&quot;. The layer must exist.
If &quot;name&quot; is not given the currently selected item is used.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>sentToLayer(&quot;layer&quot; [, &quot;name&quot;])

Переміщує об&apos;єкт &quot;name&quot; на план &quot;layer&quot;. План повинен існувати.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.

Може повернути помилку NotFoundError, якщо план не знайдено.
Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>setLayerVisible(&quot;layer&quot;, visible)

Sets the layer &quot;layer&quot; to be visible or not. If is the visible set to false
the layer is invisible.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>setLayerVisible(&quot;layer&quot;, visible)

Змінює видимість плану &quot;layer&quot;. Якщо &quot;visible&quot; дорівнює булевому
значенню &quot;false&quot; - план невидимий.

Може повернути помилку NotFoundError, якщо план не знайдено.
Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>setLayerPrintable(&quot;layer&quot;, printable)

Sets the layer &quot;layer&quot; to be printable or not. If is the printable set to
false the layer won&apos;t be printed.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="obsolete">setLayerPrintable(&quot;layer&quot;, printable)

Змінює доступність плану &quot;layer&quot; для друку. Якщо &quot;printable&quot;
дорівнює булевому значенню &quot;false&quot;, план не буде надруковано.

Може повернути помилку NotFoundError, якщо план не знайдено.
Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>deleteLayer(&quot;layer&quot;)

Deletes the layer with the name &quot;layer&quot;. Nothing happens if the layer doesn&apos;t
exists or if it&apos;s the only layer in the document.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>deleteLayer(&quot;layer&quot;)

Видаляє план з назвою &quot;layer&quot;. При відсутності плану або якщо це 
останній план документа нічого не відбувається.

Може повернути помилку NotFoundError, якщо план не знайдено.
Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>createLayer(layer)

Creates a new layer with the name &quot;name&quot;.

May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>createLayer(layer)

Створює новий план з назвою &quot;name&quot;.

Може повернути помилку ValueError, якщо назва плану недопустима.
</translation>
    </message>
    <message>
        <source>getGuiLanguage() -&gt; string

Returns a string with the -lang value.
</source>
        <translation>getGuiLanguage() -&gt; строкова величина

Повертає строкову величину, яка містить значення -lang.
</translation>
    </message>
    <message>
        <source>createEllipse(x, y, width, height, [&quot;name&quot;]) -&gt; string

Creates a new ellipse on the current page and returns its name.
The coordinates are given in the current measurement units of the document
(see UNIT constants). &quot;name&quot; should be a unique identifier for the object
because you need this name for further referencing of that object. If &quot;name&quot;
is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
</source>
        <translation>createEllipse(x, y, width, height, [&quot;name&quot;]) -&gt; строкова величина

Створює новий еліпс на активній сторінці та повертає його назву.
Координати задаються в активних одиницях виміру документа (див.
константи UNIT). &quot;name&quot; повинне бути неповторним визначником
об&apos;єкта, тому що воно служить для подальших звернень до нього.
Якщо &quot;name&quot; не задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
</translation>
    </message>
    <message>
        <source>createImage(x, y, width, height, [&quot;name&quot;]) -&gt; string

Creates a new picture frame on the current page and returns its name. The
coordinates are given in the current measurement units of the document.
&quot;name&quot; should be a unique identifier for the object because you need this
name for further access to that object. If &quot;name&quot; is not given Scribus will
create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
</source>
        <translation>createImage(x, y, width, height, [&quot;name&quot;]) -&gt; строкова величина

Створює нову рамку для зображень на активній сторінці та повертає
її назву. Координати задаються в активних одиницях виміру документа.
&quot;name&quot; повинне бути неповторним визначником об&apos;єкта, тому що воно 
служить для подальших звернень до нього. Якщо &quot;name&quot; не задано, 
Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
</translation>
    </message>
    <message>
        <source>createText(x, y, width, height, [&quot;name&quot;]) -&gt; string

Creates a new text frame on the actual page and returns its name.
The coordinates are given in the actual measurement unit of the document (see
UNIT constants). &quot;name&quot; should be a unique identifier for the object because
you need this name for further referencing of that object. If &quot;name&quot; is not
given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
</source>
        <translation>createText(x, y, width, height, [&quot;name&quot;]) -&gt; строкова величина

Створює нову текстову рамку на активній сторінці та повертає
її назву. Координати задаються в активних одиницях виміру документа
(див константи UNIT). &quot;name&quot; повинне бути неповторним визначником 
об&apos;єкта, тому що воно служить для подальших звернень до нього. Якщо 
&quot;name&quot; не задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.

</translation>
    </message>
    <message>
        <source>createLine(x1, y1, x2, y2, [&quot;name&quot;]) -&gt; string

Creates a new line from the point(x1, y1) to the point(x2, y2) and returns
its name. The coordinates are given in the current measurement unit of the
document (see UNIT constants). &quot;name&quot; should be a unique identifier for the
object because you need this name for further access to that object. If
&quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
</source>
        <translation>createLine(x1, y1, x2, y2, [&quot;name&quot;]) -&gt; строкова величина

Створює нову лінію від точки (x1, y1) до точки (x2, y2) та повертає
її назву. Координати задаються в активних одиницях виміру документа
(див константи UNIT). &quot;name&quot; повинне бути неповторним визначником 
об&apos;єкта, тому що воно служить для подальших звернень до нього. Якщо 
&quot;name&quot; не задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
</translation>
    </message>
    <message>
        <source>createPolyLine(list, [&quot;name&quot;]) -&gt; string

Creates a new polyline and returns its name. The points for the polyline are
stored in the list &quot;list&quot; in the following order: [x1, y1, x2, y2...xn. yn].
The coordinates are given in the current measurement units of the document (see
UNIT constants). &quot;name&quot; should be a unique identifier for the object because
you need this name for further access to that object. If &quot;name&quot; is not given
Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don&apos;t group into points without leftovers.
</source>
        <translation>createPolyLine(list, [&quot;name&quot;]) -&gt; строкова величина

Створює багатосегментну лінію та повертає її назву. Точки лінії 
зберігаються в списку &quot;list&quot; у визначеному порядку [x1, y1, x2, y2...xn. yn]. 
Координати задаються в активних одиницях виміру документа
(див константи UNIT). &quot;name&quot; повинне бути неповторним визначником 
об&apos;єкта, тому що воно служить для подальших звернень до нього. Якщо 
&quot;name&quot; не задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
Може повернути помилку ValueError, якщо задане недостатнє число точок
або число заданих координат не відповідає числу точок.
</translation>
    </message>
    <message>
        <source>createPolygon(list, [&quot;name&quot;]) -&gt; string

Creates a new polygon and returns its name. The points for the polygon are
stored in the list &quot;list&quot; in the following order: [x1, y1, x2, y2...xn. yn].
At least three points are required. There is no need to repeat the first point
to close the polygon. The polygon is automatically closed by connecting the
first and the last point.  The coordinates are given in the current measurement
units of the document (see UNIT constants).  &quot;name&quot; should be a unique
identifier for the object because you need this name for further access to that
object. If &quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don&apos;t group into points without leftovers.
</source>
        <translation>createPolygon(list, [&quot;name&quot;]) -&gt; строкова величина

Створює полігон та повертає його назву. Точки кутів полігона
зберігаються в списку &quot;list&quot; у визначеному порядку [x1, y1, x2, y2...xn. yn]. 
Як мінімум мають бути задані три точки. Необхідності в повторенні першої
точки для замикання полігона не існує. Полігон автоматично замикається
з&apos;єднанням першої та останньої заданих точок. Координати задаються в 
активних одиницях виміру документа (див константи UNIT). &quot;name&quot; повинне 
бути неповторним визначником об&apos;єкта, тому що воно служить для подальших 
звернень до нього. Якщо &quot;name&quot; не задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
Може повернути помилку ValueError, якщо задане недостатнє число точок
або число заданих координат не відповідає числу точок.
</translation>
    </message>
    <message>
        <source>createBezierLine(list, [&quot;name&quot;]) -&gt; string

Creates a new bezier curve and returns its name. The points for the bezier
curve are stored in the list &quot;list&quot; in the following order:
[x1, y1, kx1, ky1, x2, y2, kx2, ky2...xn. yn, kxn. kyn]
In the points list, x and y mean the x and y coordinates of the point and kx
and ky meaning the control point for the curve.  The coordinates are given in
the current measurement units of the document (see UNIT constants). &quot;name&quot;
should be a unique identifier for the object because you need this name for
further access to that object. If &quot;name&quot; is not given Scribus will create one
for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
May raise ValueError if an insufficient number of points is passed or if
the number of values passed don&apos;t group into points without leftovers.
</source>
        <translation>createBezierLine(list, [&quot;name&quot;]) -&gt; строкова величина

Створює нову криву Безьє  та повертає її назву. Точки кривої
зберігаються в списку &quot;list&quot; у визначеному порядку 
[x1, y1, kx1, ky1, x2, y2, kx2, ky2...xn. yn, kxn. kyn]
В списку точок x та y відповідають координатам точки, а kx та ky 
відповідають контрольним точкам кривої. Координати задаються 
в активних одиницях виміру документа (див константи UNIT). 
&quot;name&quot; повинне бути неповторним визначником об&apos;єкта, тому що 
воно служить для подальших звернень до нього. Якщо &quot;name&quot; не 
задано, Scribus створить його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
Може повернути помилку ValueError, якщо задане недостатнє число точок
або число заданих координат не відповідає числу точок.
</translation>
    </message>
    <message>
        <source>createPathText(x, y, &quot;textbox&quot;, &quot;beziercurve&quot;, [&quot;name&quot;]) -&gt; string

Creates a new pathText by merging the two objects &quot;textbox&quot; and
&quot;beziercurve&quot; and returns its name. The coordinates are given in the current
measurement unit of the document (see UNIT constants). &quot;name&quot; should be a
unique identifier for the object because you need this name for further access
to that object. If &quot;name&quot; is not given Scribus will create one for you.

May raise NameExistsError if you explicitly pass a name that&apos;s already used.
May raise NotFoundError if one or both of the named base object don&apos;t exist.
</source>
        <translation>createPathText(x, y, &quot;textbox&quot;, &quot;beziercurve&quot;, [&quot;name&quot;]) -&gt; строкова величина

Створює новий текстовий шлях (pathText) через з&apos;єднання двох об&apos;єктів
&quot;textbox&quot; та &quot;beziercurve&quot; та повертає його назву. Координати задаються 
в активних одиницях виміру документа (див константи UNIT). &quot;name&quot; 
повинне бути неповторним визначником об&apos;єкта, тому що воно служить 
для подальших звернень до нього. Якщо &quot;name&quot; не задано, Scribus створить 
його сам.

Може повернути помилку NameExistsError при спробі задання вже
використаної назви.
Може повернути помилку NotFoundError, якщо один чи обидва названих
базових об&apos;єкти не існують.
</translation>
    </message>
    <message>
        <source>deleteObject([&quot;name&quot;])

Deletes the item with the name &quot;name&quot;. If &quot;name&quot; is not given the currently
selected item is deleted.
</source>
        <translation>deleteObject([&quot;name&quot;])

Видаляє об&apos;єкт &quot;name&quot;. Якщо &quot;name&quot; не вказано, буде видалено вибраний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>textFlowsAroundFrame(&quot;name&quot; [, state])

Enables/disables &quot;Text Flows Around Frame&quot; feature for object &quot;name&quot;.
Called with parameters string name and optional boolean &quot;state&quot;. If &quot;state&quot;
is not passed, text flow is toggled.
</source>
        <translation type="obsolete">textFlowsAroundFrame(&quot;name&quot; [, state])

Вмикає/вимикає параметр &quot;Текст обтікає рамку&quot; об&apos;єкта &quot;name&quot;.
При виклиці задається строковий параметр &quot;name&quot; та необов&apos;язковий
булевий параметр &quot;state&quot;. Якщо &quot;state&quot; не задано, відбувається зміна
стану параметра на протилежний.
</translation>
    </message>
    <message>
        <source>objectExists([&quot;name&quot;]) -&gt; bool

Test if an object with specified name really exists in the document.
The optional parameter is the object name. When no object name is given,
returns True if there is something selected.
</source>
        <translation>objectExists([&quot;name&quot;]) -&gt; булеве значення

Перевіряє чи вказаний об&apos;єкт вже існує в документі. Назва об&apos;єкта є 
необов&apos;язковим параметром. Якщо назва не задана, повертає булеве
значення &quot;True&quot;, при наявності вибраного об&apos;єкта.
</translation>
    </message>
    <message>
        <source>setStyle(&quot;style&quot; [, &quot;name&quot;])

Apply the named &quot;style&quot; to the object named &quot;name&quot;. If is no object name
given, it&apos;s applied on the selected object.
</source>
        <translation>setStyle(&quot;style&quot; [, &quot;name&quot;])

Застосовує стиль &quot;style&quot; для об&apos;єкта &quot;name&quot;. Якщо &quot;name&quot; не вказано, 
буде використано вибраний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>getAllStyles() -&gt; list

Return a list of the names of all paragraph styles in the current document.
</source>
        <translation>getAllStyles() -&gt; список

Повертає список всіх стилів абзаців в активному документі.
</translation>
    </message>
    <message>
        <source>currentPage() -&gt; integer

Returns the number of the current working page. Page numbers are counted from 1
upwards, no matter what the displayed first page number of your document is.
</source>
        <translation>currentPage() -&gt; ціле число

Повертає номер активної сторінки. Номери сторінок рахуються вгору від 1,
незалежно від того, який номер показаний на першій сторінці документа.
</translation>
    </message>
    <message>
        <source>redrawAll()

Redraws all pages.
</source>
        <translation>redrawAll()

Перерисовує всі сторінки.
</translation>
    </message>
    <message>
        <source>savePageAsEPS(&quot;name&quot;)

Saves the current page as an EPS to the file &quot;name&quot;.

May raise ScribusError if the save failed.
</source>
        <translation>savePageAsEPS(&quot;name&quot;)

Зберігає активну сторінку, як файл EPS з назвою &quot;name&quot;.

Може повернути помилку ScribusError, якщо запис не був успішним.
</translation>
    </message>
    <message>
        <source>deletePage(nr)

Deletes the given page. Does nothing if the document contains only one page.
Page numbers are counted from 1 upwards, no matter what the displayed first
page number is.

May raise IndexError if the page number is out of range
</source>
        <translation>deletePage(nr)

Видалає дану сторінку. Якщо в документі є лише одна сторінка - нічого
не відбудеться. Номери сторінок рахуються вгору від 1, незалежно від 
того, який номер показаний на першій сторінці документа.

Може повернути помилку IndexError, якщо номер сторінки виходить за
межі доступного діапазону
</translation>
    </message>
    <message>
        <source>gotoPage(nr)

Moves to the page &quot;nr&quot; (that is, makes the current page &quot;nr&quot;). Note that
gotoPage doesn&apos;t (curently) change the page the user&apos;s view is displaying, it
just sets the page that script commands will operates on.

May raise IndexError if the page number is out of range.
</source>
        <translation>gotoPage(nr)

Переходить до сторінки номер &quot;nr&quot; (тобто робить сторінку номер &quot;nr&quot; активною). 
Майте на увазі, що gotoPage лише установлює сторінку на якій буде оперувати
сценарій і не змінює того, яка сторінка видима користувачу.

Може повернути помилку IndexError, якщо номер сторінки виходить за межі 
доступного діапазону.
</translation>
    </message>
    <message>
        <source>pageCount() -&gt; integer

Returns the number of pages in the document.
</source>
        <translation>pageCount() -&gt; ціле число

Повертає число сторінок в документі.
</translation>
    </message>
    <message>
        <source>getHGuides() -&gt; list

Returns a list containing positions of the horizontal guides. Values are in the
document&apos;s current units - see UNIT_&lt;type&gt; constants.
</source>
        <translation>getHGuides() -&gt; список

Повертає список розміщення горизонтальних направляючих. Значення
виражаються в активних одиницях виміру документа - див. константи
UNIT_&lt;type&gt;.
</translation>
    </message>
    <message>
        <source>setHGuides(list)

Sets horizontal guides. Input parameter must be a list of guide positions
measured in the current document units - see UNIT_&lt;type&gt; constants.

Example: setHGuides(getHGuides() + [200.0, 210.0] # add new guides without any lost
         setHGuides([90,250]) # replace current guides entirely
</source>
        <translation>setHGuides(list)

Установлює горизонтальні направляючі. Вхідний параметр має бути заданий
як список позицій направляючих, виражених в активних одиницях виміру
документа - див. константи UNIT_&lt;type&gt;.

Приклад: setHGuides(getHGuides() + [200.0, 210.0] # додати нові направляючі без
заміщення існуючих
         setHGuides([90,250]) # повністю замінити існуючі направляючі
</translation>
    </message>
    <message>
        <source>getVGuides()

See getHGuides.
</source>
        <translation>getVGuides()

Див. getHGuides.
</translation>
    </message>
    <message>
        <source>setVGuides()

See setHGuides.
</source>
        <translation>setVGuides()

Див. setHGuides.
</translation>
    </message>
    <message>
        <source>getPageSize() -&gt; tuple

Returns a tuple with page dimensions measured in the document&apos;s current units.
See UNIT_&lt;type&gt; constants and getPageMargins()
</source>
        <translation>getPageSize() -&gt; тупль

Повертає тупль з розміром сторінки, вираженим в активних одиницях виміру
документа. Див. константи UNIT_&lt;type&gt; та функцію getPageMargins()
</translation>
    </message>
    <message>
        <source>getPageItems() -&gt; list

Returns a list of tuples with items on the current page. The tuple is:
(name, objectType, order) E.g. [(&apos;Text1&apos;, 4, 0), (&apos;Image1&apos;, 2, 1)]
means that object named &apos;Text1&apos; is a text frame (type 4) and is the first at
the page...
</source>
        <translation>getPageItems() -&gt; список

Повертає список туплів з об&apos;єктами, розташованими на активній сторінці.
Тупль має вигляд (name, objectType, order).  Наприклад &apos;Text1&apos;, 4, 0), (&apos;Image1&apos;, 2, 1)]
означає, що об&apos;єкт &apos;Text1&apos; є текстовою рамкою (тип 4) і є першим об&apos;єктом сторінки...
</translation>
    </message>
    <message>
        <source>setFillColor(&quot;color&quot;, [&quot;name&quot;])

Sets the fill color of the object &quot;name&quot; to the color &quot;color&quot;. &quot;color&quot;
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation>setFillColor(&quot;color&quot;, [&quot;name&quot;])

Установлює колір заповнення &quot;color&quot; для об&apos;&apos;єкта &quot;name&quot;. &quot;color&quot;
повинен бути попередньо визначеним. Якщо &quot;name&quot; не задано, 
буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>setLineColor(&quot;color&quot;, [&quot;name&quot;])

Sets the line color of the object &quot;name&quot; to the color &quot;color&quot;. If &quot;name&quot;
is not given the currently selected item is used.
</source>
        <translation>setLineColor(&quot;color&quot;, [&quot;name&quot;])

Установлює колір &quot;color&quot; для об&apos;&apos;єкта &quot;name&quot;. Якщо &quot;name&quot; не задано, 
буде використано активний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>setLineWidth(width, [&quot;name&quot;])

Sets line width of the object &quot;name&quot; to &quot;width&quot;. &quot;width&quot; must be in the
range from 0.0 to 12.0 inclusive, and is measured in points. If &quot;name&quot; is not
given the currently selected item is used.

May raise ValueError if the line width is out of bounds.
</source>
        <translation>setLineWidth(width, [&quot;name&quot;])

Установлює товщину об&apos;єкта &quot;name&quot; до &quot;width&quot;. &quot;width&quot; повинна бути в
діапазоні від 0.0 до 12.0 включно і вимірюється в точках. Якщо &quot;name&quot; 
не задано, буде використано активний об&apos;єкт. 

Може повернути помилку ValueError, якщо товщина лінії виходить за
доступний діапазон.
</translation>
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

Установлює тінь ліній об&apos;єкта &quot;name&quot; до &quot;shade&quot;. &quot;shade&quot; повинна бути 
в діапазоні від 0 (найсвітліша) до 100 (повна насиченість кольору).
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт. 

Може повернути помилку ValueError, якщо тінь виходить за 
доступний діапазон.
</translation>
    </message>
    <message>
        <source>setLineJoin(join, [&quot;name&quot;])

Sets the line join style of the object &quot;name&quot; to the style &quot;join&quot;.
If &quot;name&quot; is not given the currently selected item is used. There are
predefined constants for join - JOIN_&lt;type&gt;.
</source>
        <translation>setLineJoin(join, [&quot;name&quot;])

Установлює тип з&apos;єднань ліній об&apos;єкта &quot;name&quot; до стиля &quot;join&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
Існують попередньо визначені константи для &quot;join&quot; - JOIN_&lt;type&gt;.
</translation>
    </message>
    <message>
        <source>setLineEnd(endtype, [&quot;name&quot;])

Sets the line cap style of the object &quot;name&quot; to the style &quot;cap&quot;.
If &quot;name&quot; is not given the currently selected item is used. There are
predefined constants for &quot;cap&quot; - CAP_&lt;type&gt;.
</source>
        <translation>setLineEnd(endtype, [&quot;name&quot;])

Установлює тип кінцівок ліній об&apos;єкта &quot;name&quot; до стиля &quot;cap&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
Існують попередньо визначені константи для &quot;cap&quot; - CAP_&lt;type&gt;.
</translation>
    </message>
    <message>
        <source>setLineStyle(style, [&quot;name&quot;])

Sets the line style of the object &quot;name&quot; to the style &quot;style&quot;. If &quot;name&quot;
is not given the currently selected item is used. There are predefined
constants for &quot;style&quot; - LINE_&lt;style&gt;.
</source>
        <translation>setLineStyle(style, [&quot;name&quot;])

Установлює стиль ліній об&apos;єкта &quot;name&quot; до стиля &quot;style&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.
Існують попередньо визначені константи для &quot;style&quot; - LINE_&lt;style&gt;.
</translation>
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

Установлює тінь заповнення об&apos;єкта &quot;name&quot; до &quot;shade&quot;. &quot;shade&quot; 
повинна бути в діапазоні від 0 (найсвітліша) до 100 (повна 
насиченість кольору). Якщо &quot;name&quot; не задано, буде використано 
активний об&apos;єкт. 

Може повернути помилку ValueError, якщо тінь виходить за 
доступний діапазон.
</translation>
    </message>
    <message>
        <source>setCornerRadius(radius, [&quot;name&quot;])

Sets the corner radius of the object &quot;name&quot;. The radius is expressed
in points. If &quot;name&quot; is not given the currently selected item is used.

May raise ValueError if the corner radius is negative.
</source>
        <translation>setCornerRadius(radius, [&quot;name&quot;])

Установлює радіус кутів об&apos;єкта &quot;name&quot;. Радіус виражається в точках.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт. 

Може повернути помилку ValueError, якщо радіус негативний.
</translation>
    </message>
    <message>
        <source>setMultiLine(&quot;namedStyle&quot;, [&quot;name&quot;])

Sets the line style of the object &quot;name&quot; to the named style &quot;namedStyle&quot;.
If &quot;name&quot; is not given the currently selected item is used.

May raise NotFoundError if the line style doesn&apos;t exist.
</source>
        <translation>setMultiLine(&quot;namedStyle&quot;, [&quot;name&quot;])

Установлює стиль ліній об&apos;єкта &quot;name&quot; до стиля &quot;namedStyle&quot;.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.

Може повернути помилку NotFoundError, якщо цей стиль ліній не існує.
</translation>
    </message>
    <message>
        <source>progressReset()

Cleans up the Scribus progress bar previous settings. It is called before the
new progress bar use. See progressSet.
</source>
        <translation>progressReset()

Видалає попередні установки панелі прогресу. Викликається до нового
використання панелі. Див. progressSet.
</translation>
    </message>
    <message>
        <source>progressTotal(max)

Sets the progress bar&apos;s maximum steps value to the specified number.
See progressSet.
</source>
        <translation>progressTotal(max)

Установлює максимальне значення для панелі прогресу до заданого
число. Див. progressSet.
</translation>
    </message>
    <message>
        <source>progressSet(nr)

Set the progress bar position to &quot;nr&quot;, a value relative to the previously set
progressTotal. The progress bar uses the concept of steps; you give it the
total number of steps and the number of steps completed so far and it will
display the percentage of steps that have been completed. You can specify the
total number of steps with progressTotal(). The current number of steps is set
with progressSet(). The progress bar can be rewound to the beginning with
progressReset(). [based on info taken from Trolltech&apos;s Qt docs]
</source>
        <translation>progressSet(nr)

Установлює позицію панелі прогресу до значення &quot;nr&quot; відносно 
попередньо вираженого значення progressTotal. Панель прогресу
виражає концепцію сходинок - задається загальне число сходинок
та число пройдених сходинок і панель буде показувати прогрес
проходження сходинок у відсотках від завершення. Сумма сходинок
задається значенням progressTotal(). Активне число сходинок
установлюється за допомогою progressSet(). Панель прогресу може 
бути повернена на початок за допомогою progressReset(). [основано
на документації фірми Trolltech&apos;s по Qt]
</translation>
    </message>
    <message>
        <source>setCursor()

[UNSUPPORTED!] This might break things, so steer clear for now.
</source>
        <translation>setCursor()

[НЕ ПІДТРИМУЄТЬСЯ!] Може призвести до помилок в роботі програми.
Поки що не використовуйте.
</translation>
    </message>
    <message>
        <source>docChanged(bool)

Enable/disable save icon in the Scribus icon bar and the Save menu item. It&apos;s
useful to call this procedure when you&apos;re changing the document, because Scribus
won&apos;t automatically notice when you change the document using a script.
</source>
        <translation>docChanged(булеве значення)

Ввімкнути/вимкнути іконку запису на панелі іконокScribus та в меню &quot;Записати&quot;.
Використовуйте цю функцію при зміні документа, тому що Scribus не реєструє
змін автоматично при роботі сценарія.
</translation>
    </message>
    <message>
        <source>setScaleImageToFrame(scaletoframe, proportional=None, name=&lt;selection&gt;)

Sets the scale to frame on the selected or specified image frame to `scaletoframe&apos;.
If `proportional&apos; is specified, set fixed aspect ratio scaling to `proportional&apos;.
Both `scaletoframe&apos; and `proportional&apos; are boolean.

May raise WrongFrameTypeError.
</source>
        <translation>setScaleImageToFrame(scaletoframe, proportional=None, name=&lt;selection&gt;)

Установлює масштабування зображення до розмірів рамки для вибраної
або вказаної рамки для зображень до `scaletoframe&apos;. Вибір
`proportional&apos; (пропорційне) значення встановлює фіксоване відношення 
сторін зображення при масштабуванні. І `scaletoframe&apos; і `proportional&apos; являються
булевими змінними.

Може повернути помилку WrongFrameTypeError.
</translation>
    </message>
    <message>
        <source>isLayerPrintable(&quot;layer&quot;) -&gt; bool

Returns whether the layer &quot;layer&quot; is printable or not, a value of True means
that the layer &quot;layer&quot; can be printed, a value of False means that printing
the layer &quot;layer&quot; is disabled.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation>isLayerPrintable(&quot;layer&quot;) -&gt; bool

Повертає булеве значення, яке вказує на те чи можна друкувати план &quot;layer&quot;.
True означає, що &quot;layer&quot; можна друкувати, False означає, що друк плана
&quot;layer&quot; не дозволено.

Може повернути помилку NotFoundError, якщо план не знайдено.
May raise ValueError при використанні недопустимої назви плана.
</translation>
    </message>
    <message>
        <source>renderFont(&quot;name&quot;, &quot;filename&quot;, &quot;sample&quot;, size, format=&quot;PPM&quot;) -&gt; bool

Creates an image preview of font &quot;name&quot; with given text &quot;sample&quot; and size.
If &quot;filename&quot; is not &quot;&quot;, image is saved into &quot;filename&quot;. Otherwise
image data is returned as a string. The optional &quot;format&quot; argument
specifies the image format to generate, and supports any format allowed
by QPixmap.save(). Common formats are PPM, JPEG, PNG and XPM.

May raise NotFoundError if the specified font can&apos;t be found.
May raise ValueError if an empty sample or filename is passed.
</source>
        <translation>renderFont(&quot;name&quot;, &quot;filename&quot;, &quot;sample&quot;, size, format=&quot;PPM&quot;) -&gt; bool

Створює растрове зображення шрифта з іменем &quot;name&quot; з заданим
текстом &quot;sample&quot; та розміром &quot;size&quot;. Якщо &quot;filename&quot; не дорівнює &quot;&quot;, 
зображення буде записане в файл з назвою &quot;filename&quot;. В протилежному
випадку зображення буде повернене, як строкова величина.
Необов&apos;язковий аргумент &quot;format&quot; вказує на те, який формат зображення
генерувати і підтримує всі формати дозволені QPixmap.save(). Часто
вживані формати включають PPM, JPEG, PNG та XPM.

Може повернути помилку NotFoundError, якщо вказаний шрифт не
було знайдено.
Може повернути помилку ValueError, якщо функції був переданий пустий
зразковий текст або ім&apos;я файла.
</translation>
    </message>
    <message>
        <source>setPDFBookmark(&quot;toggle&quot;, [&quot;name&quot;])

Sets wether (toggle = 1) the text frame &quot;name&quot; is a bookmark nor not.
If &quot;name&quot; is not given the currently selected item is used.

May raise WrongFrameTypeError if the target frame is not a text frame
</source>
        <translation>setPDFBookmark(&quot;toggle&quot;, [&quot;name&quot;])

Установлює те чи (&quot;toggle&quot; = 1) текстова рамка &quot;name&quot; є закладкою.
Якщо ім&apos;я &quot;name&quot; не задано, буде використано активний об&apos;єкт.

Може повернути помилку WrongFrameTypeError, якщо задана рамка не є 
текстовою рамкою
</translation>
    </message>
    <message>
        <source>isPDFBookmark([&quot;name&quot;]) -&gt; bool

Returns true if the text frame &quot;name&quot; is a PDF bookmark.
If &quot;name&quot; is not given the currently selected item is used.

May raise WrongFrameTypeError if the target frame is not a text frame
</source>
        <translation>isPDFBookmark([&quot;name&quot;]) -&gt; bool

Повертає булеве значення true, якщо текстова рамка &quot;name&quot; є закладкою PDF.
Якщо &quot;name&quot; не задано, буде використано активний об&apos;єкт.

Може повернути помилку WrongFrameTypeError, якщо задана рамка не
являється текстовою
</translation>
    </message>
    <message>
        <source>getPageMargins()

Returns the page margins as a (top, left, right, bottom) tuple in the current
units. See UNIT_&lt;type&gt; constants and getPageSize().
</source>
        <translation>getPageMargins()

Повертає поля сторінки як тупль (верхнє, ліве, праве, нижнє) в активних одиницях. Дивіться UNIT_&lt;type&gt; константи та getPageSize().
</translation>
    </message>
    <message>
        <source>getColorAsRGB(&quot;name&quot;) -&gt; tuple

Returns a tuple (R,G,B) containing the three color components of the
color &quot;name&quot; from the current document, converted to the RGB color
space. If no document is open, returns the value of the named color
from the default document colors.

May raise NotFoundError if the named color wasn&apos;t found.
May raise ValueError if an invalid color name is specified.
</source>
        <translation>getColorAsRGB(&quot;name&quot;) -&gt; тупль

Повертає тупль (R,G,B), який містить три компоненти кольору &quot;name&quot; з активного документа, конвертовані в кольоровий простір RGB. При відсутності активного документа повертає значення названого кольору з основної палітри кольорів.

Може повернути помилку NotFoundError, якщо названий колір не було знайдено.
Може повернути помилку ValueError, якщо ім&apos;я кольору вказано неправильно.
</translation>
    </message>
    <message>
        <source>defineColor(&quot;name&quot;, c, m, y, k)

Defines a new color &quot;name&quot;. The color Value is defined via four components:
c = Cyan, m = Magenta, y = Yello and k = Black. Color components should be in
the range from 0 to 255.

May raise ValueError if an invalid color name is specified.
</source>
        <translation type="obsolete">defineColor(&quot;name&quot;, c, m, y, k)

Визначає новий колір &quot;name&quot;. Значення кольору визначається через чотири компоненти:
c = Cyan (Салатовий), m = Magenta (Рожевий), y = Yello (Жовтий) and k = Black (Чорний). Компоненти кольору повинні бути в діапазоні від 0 до 255.

Може повернути помилку ValueError, якщо ім&apos;я кольору було вказано невірно.
</translation>
    </message>
    <message>
        <source>fileDialog(&quot;caption&quot;, [&quot;filter&quot;, &quot;defaultname&quot;, haspreview, issave, isdir]) -&gt; string with filename

Shows a File Open dialog box with the caption &quot;caption&quot;. Files are filtered
with the filter string &quot;filter&quot;. A default filename or file path can also
supplied, leave this string empty when you don&apos;t want to use it.  A value of
True for haspreview enables a small preview widget in the FileSelect box.  When
the issave parameter is set to True the dialog acts like a &quot;Save As&quot; dialog
otherwise it acts like a &quot;File Open Dialog&quot;. When the isdir parameter is True
the dialog shows and returns only directories. The default for all of the
opional parameters is False.

The filter, if specified, takes the form &apos;comment (*.type *.type2 ...)&apos;.
For example &apos;Images (*.png *.xpm *.jpg)&apos;.

Refer to the Qt-Documentation for QFileDialog for details on filters.

Example: fileDialog(&apos;Open input&apos;, &apos;CSV files (*.csv)&apos;)
Example: fileDialog(&apos;Save report&apos;, defaultname=&apos;report.txt&apos;, issave=True)
</source>
        <translation>fileDialog(&quot;caption&quot;, [&quot;filter&quot;, &quot;defaultname&quot;, haspreview, issave, isdir]) -&gt; строкова величина з назвою файла

Показує діалог відкриття файла з підписом &quot;caption&quot;. Назви файлів фільтруються за допомогою текстової величини &quot;filter&quot;. Назва або шлях до файла по умовчанню також можуть бути вказані. Залиште цю строкову величину пустою, якщо Ви не збираєтеся її використовувати. Булеве значення True для haspreview вмикає невелике поля для попереднього перегляду в діалоговому вікні FileSelect. Якщо параметр issave дорівнює True то діалог перетворюється в &quot;Записати як&quot;. В протилежному випадку він діє як &quot;Відчинити файл&quot; діалог. Якщо параметр isdir дорівнює True то діалог показує і повертає лише директорії. Значення всіх необов&apos;язкових параметрів по умовчанню дорівнює False.

Якщо вкзано фільтр він повинен прийняти форму &apos;comment (*.type *.type2 ...)&apos;.
Наприклад &apos;Зображення (*.png *.xpm *.jpg)&apos;.

Зверніться до документації Qt по QFileDialog за детальним описом фільтрів.

Приклад: fileDialog(&apos;Відкрити дані&apos;, &apos;CSV files (*.csv)&apos;)
Приклад: fileDialog(&apos;Записати звіт&apos;, defaultname=&apos;report.txt&apos;, issave=True)
</translation>
    </message>
    <message>
        <source>getCornerRadius([&quot;name&quot;]) -&gt; integer

Returns the corner radius of the object &quot;name&quot;. The radius isexpressed in points. If &quot;name&quot; is not given the currentlyselected item is used.
</source>
        <translation type="obsolete">getCornerRadius([&quot;name&quot;]) -&gt; ціле число

Повертає радіус кута об&apos;єкта &quot;name&quot;. Радіус виражається в точках. Якщо &quot;name&quot; не задано - буде використано вибраний об&apos;єкт.</translation>
    </message>
    <message>
        <source>getPosition([&quot;name&quot;]) -&gt; (x,y)

Returns a (x, y) tuple with the position of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.The position is expressed in the actual measurement unit of the document
- see UNIT_&lt;type&gt; for reference.
</source>
        <translation type="obsolete">getPosition([&quot;name&quot;]) -&gt; (x,y)

Повертає тупль (x, y) з координатами об&apos;єкта &quot;name&quot;.
Якщо &quot;name&quot; не задано, буде використано вибраний об&apos;єкт. Координати виражаються в одиницях виміру прийнятих для документа. Дивіться UNIT_&lt;type&gt; для додаткової інформації.
</translation>
    </message>
    <message>
        <source>getPropertyCType(object, property, includesuper=True)

Returns the name of the C type of `property&apos; of `object&apos;. See getProperty()
for details of arguments.

If `includesuper&apos; is true, search inherited properties too.
</source>
        <translation>getPropertyCType(object, property, includesuper=True)

Повертає назву типу С для атрибута `property&apos; об&apos;єкта `object&apos;. Див. getProperty()
для додаткової інформації про атрибути.

Якщо `includesuper&apos; дорівнює true - також шукати наслідкові атрибути.
</translation>
    </message>
    <message>
        <source>getPropertyNames(object, includesuper=True)

Return a list of property names supported by `object&apos;.
If `includesuper&apos; is true, return properties supported
by parent classes as well.
</source>
        <translation>getPropertyNames(object, includesuper=True)

Повертає лист назв атрибутів, які підтримує об&apos;єкт `object&apos;.
Якщо `includesuper&apos; дорівнює true, також повернути атрибути, які підтримуються батьківськими класами.
</translation>
    </message>
    <message>
        <source>getProperty(object, property)

Return the value of the property `property&apos; of the passed `object&apos;.

The `object&apos; argument may be a string, in which case the named PageItem
is searched for. It may also be a PyCObject, which may point to any
C++ QObject instance.

The `property&apos; argument must be a string, and is the name of the property
to look up on `object&apos;.

The return value varies depending on the type of the property.
</source>
        <translation>getProperty(object, property)

Повертає значення атрибута `property&apos; переданого об&apos;єкта `object&apos;.

Аргумент `object&apos; може бути строковою величиною. В цьому випадку буде шукатися названий об&apos;єкт PageItem. Він також може бути об&apos;єктом PyCObject, який може вказувати на любий екземпляр C++ QObject.

Аргумент `property&apos; повинен бути строковою величиною і являється назвою атрибута об&apos;єкта  `object&apos;.

Повернене значення залежить від типу атрибута.
</translation>
    </message>
    <message>
        <source>setProperty(object, property, value)

Set `property&apos; of `object&apos; to `value&apos;. If `value&apos; cannot be converted to a type
compatible with the type of `property&apos;, an exception is raised. An exception may
also be raised if the underlying setter fails.

See getProperty() for more information.
</source>
        <translation>setProperty(object, property, value)

Установити `property&apos; об&apos;єкта `object&apos; до значення `value&apos;. Якщо `value&apos; не може бути конвертоване в тип сумісний з типом `property&apos; - буде повернена помилка. Помилка може бути також повернена, якщо послідуюча установлююча функція не буде успішно виконана.

Дивіться getProperty() для додаткової інформації.
</translation>
    </message>
    <message>
        <source>getChildren(object, ofclass=None, ofname=None, regexpmatch=False, recursive=True)

Return a list of children of `object&apos;, possibly restricted to children
of class named `ofclass&apos; or children named `ofname&apos;. If `recursive&apos; is true,
search recursively through children, grandchildren, etc.

See QObject::children() in the Qt docs for more information.
</source>
        <translation>getChildren(object, ofclass=None, ofname=None, regexpmatch=False, recursive=True)

Повертає список дітей об&apos;єкта `object&apos;. Можливо дозволити лише повернення дітей класу з назвою `ofclass&apos; або лише дітей з назвами`ofname&apos;. Якщо `recursive&apos; дорівнює true,
пошук буде проводитися рекурсивно між дітей, внуків і т.д.

Дивіться QObject::children() в документації Qt для подальшої інформації.
</translation>
    </message>
    <message>
        <source>getChild(object, childname, ofclass=None, recursive=True)

Return the first child of `object&apos; named `childname&apos;, possibly restricting
the search to children of type name `ofclass&apos;. If `recursive&apos; is true,
search recursively through children, grandchildren, etc.
</source>
        <translation>getChild(object, childname, ofclass=None, recursive=True)

Повертає першу дитину об&apos;єкта `object&apos; названу `childname&apos; з можливим обмеженням дітьми класу з назвою `ofclass&apos;. Якщо `recursive&apos; дорівнює true, пошук буде проводитися рекурсивно між дітей, внуків і т.д.
</translation>
    </message>
    <message>
        <source>rotateObjectAbs(rot [, &quot;name&quot;])

Sets the rotation of the object &quot;name&quot; to &quot;rot&quot;. Positve values
mean counter clockwise rotation. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation type="obsolete">rotateObjectAbs(rot [, &quot;name&quot;])

Установлює кут повороту об&apos;єкта &quot;name&quot; до &quot;rot&quot;. Позитивні значення приводять до повороту проти часової стрілки. Якщо &quot;name&quot; не задано, буде використано вибраний об&apos;єкт.
</translation>
    </message>
    <message>
        <source>isLayerPrintable(&quot;layer&quot;) -&gt; bool

Returns whether the layer &quot;layer&quot; is visible or not, a value of True means
that the layer &quot;layer&quot; is visible, a value of False means that the layer
&quot;layer&quot; is invisible.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="obsolete">isLayerPrintable(&quot;layer&quot;) -&gt; bool

Повертає результат того чи видимий план &quot;layer&quot;. Значення True означає, що план
&quot;layer&quot; видимий, а значення False означає, що план невидимий.

Може повернути помилку NotFoundError, якщо план не може бути знайдено.
Може повернути помилку ValueError, якщо назва плана не допустима.
</translation>
    </message>
    <message>
        <source>insertText(&quot;text&quot;, pos, [&quot;name&quot;])

Inserts the text &quot;text&quot; at the position &quot;pos&quot; into the text frame &quot;name&quot;.
Text must be UTF encoded (see setText() as reference) The first character has an
index of 0. Inserting at position -1 appends text to the frame. If &quot;name&quot; is
not given the currently selected Item is used.

May throw IndexError for an insertion out of bounds.
</source>
        <translation type="obsolete">insertText(&quot;text&quot;, pos, [&quot;name&quot;])

Вставляє текст &quot;text&quot; в позицію &quot;pos&quot; в текстову рамку &quot;name&quot;.
Текст повинен бути в кодуванні UTF  (див. setText() для довідки). Перший знак має значення індекса 0. Вставка в позиції -1 добавляє текст до рамки. Якщо &quot;name&quot; не задано, буде використаний вибраний об&apos;єкт.

Може повернути помилку IndexError при спробі вставки за доступними межами.
</translation>
    </message>
    <message>
        <source>textOverflows([&quot;name&quot;, nolinks]) -&gt; integer

Returns the actual number of overflowing characters in text frame &quot;name&quot;.
If is nolinks set to non zero value it takes only one frame - it doesn&apos;t
use text frame linking. Without this parameter it search all linking chain.

May raise WrongFrameTypeError if the target frame is not an text frame
</source>
        <translation>textOverflows([&quot;name&quot;, nolinks]) -&gt; ціле число

Повертає дійсне число знаків, які виходять за межі текстової рамки &quot;name&quot;.
Якщо nolinks не дорівнює нулю, опрацьовується лише одна рамка. Зв&apos;язування рамок не грає ролі. При відсутності цього параметра пошук проводиться по всіх зв&apos;язаних рамках.

Може повернути помилку WrongFrameTypeError, якщо цільова рамка не являється текстовою</translation>
    </message>
    <message>
        <source>newStyleDialog() -&gt; string

Shows &apos;Create new paragraph style&apos; dialog. Function returns real
style name or None when user cancels the dialog.
</source>
        <translation>newStyleDialog() -&gt; string

Показує діалогове вікно &quot;новий стиль абзацу&quot;. Функція повертає справжнє
ім&apos;я стилю або None, якщо користувач відмінить діалог.
</translation>
    </message>
    <message>
        <source>newDoc(size, margins, orientation, firstPageNumber,
                   unit, facingPages, firstSideLeft) -&gt; bool

WARNING: Obsolete procedure! Use newDocument instead.

Creates a new document and returns true if successful. The parameters have the
following meaning:

    size = A tuple (width, height) describing the size of the document. You can
    use predefined constants named PAPER_&lt;paper_type&gt; e.g. PAPER_A4 etc.

    margins = A tuple (left, right, top, bottom) describing the document
    margins

    orientation = the page orientation - constants PORTRAIT, LANDSCAPE

    firstPageNumer = is the number of the first page in the document used for
    pagenumbering. While you&apos;ll usually want 1, it&apos;s useful to have higher
    numbers if you&apos;re creating a document in several parts.

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
        <translation>newDoc(size, margins, orientation, firstPageNumber,
                   unit, facingPages, firstSideLeft) -&gt; bool

ПОПЕРЕДЖЕННЯ: Застаріла процедура! Використовуйте newDocument навтомість.

Створює новий документ та повертає true після успішного завершення. 
Розшифрування параметрів:

    size (розмір) = Тупль (ширина, висота), який описує розмір документа. Ви
    використовувати попередньо визначені константи PAPER_&lt;paper_type&gt;,
    наприклад PAPER_A4 і т.п.

    margins (поля) = Тупль (ліве, праве, верхнє, нижнє), який описує поля
    документа

    orientation (орієнтація) = Орієнтація - константи PORTRAIT, LANDSCAPE

    firstPageNumer (номер першої сторінки) = Номер першої пронумерованої
    сторінки в документі. Звичайно починається з 1, але можливе й використання
    і більших чисел, наприклад при створенні документа з кількох частин.

    unit (одиниця) = Це значення установлює одиниці виміру документа. Використовуйте
    одну з попередньо визначених констант: UNIT_INCHES, UNIT_MILLIMETERS,
    UNIT_PICAS, UNIT_POINTS.

    facingPages (зеркально відображені сторінки) = FACINGPAGES, NOFACINGPAGES

    firstSideLeft = FIRSTPAGELEFT, FIRSTPAGERIGHT

Значення ширини, висоти, та полів виражаються в одиницях виміру документа. Константи
PAPER_* виражаються в точках. Майте це на увазі, якщо Ваш документ використовує
інші одиниці виміру.

Приклад: newDoc(PAPER_A4, (10, 10, 20, 20), LANDSCAPE, 1, UNIT_POINTS,
                FACINGPAGES, FIRSTPAGERIGHT)
</translation>
    </message>
    <message>
        <source>closeMasterPage()

Closes the currently active master page, if any, and returns editing
to normal. Begin editing with editMasterPage().
</source>
        <translation>closeMasterPage()

Зачиняє активну майстер сторінку, при наявності такої, та вмикає нормальний
режим редагування. Почніть редагування з editMasterPage().
</translation>
    </message>
    <message>
        <source>masterPageNames()

Returns a list of the names of all master pages in the document.
</source>
        <translation>masterPageNames()

Повертає список імен всіх майстер сторінок документа.
</translation>
    </message>
    <message>
        <source>editMasterPage(pageName)

Enables master page editing and opens the named master page
for editing. Finish editing with closeMasterPage().
</source>
        <translation>editMasterPage(pageName)

Дозволяє редагування майстер сторінки та відчиняє її для редагування.
Закінчуйте редагування з closeMasterPage().
</translation>
    </message>
    <message>
        <source>createMasterPage(pageName)

Creates a new master page named pageName and opens it for
editing.
</source>
        <translation>createMasterPage(pageName)

Створює нову майстер сторінку з назвою pageName та відчиняє її
для редагування.
</translation>
    </message>
    <message>
        <source>deleteMasterPage(pageName)

Delete the named master page.
</source>
        <translation>deleteMasterPage(pageName)

Видаляє названу (pageName) майстер сторінку.
</translation>
    </message>
    <message>
        <source>zoomDocument(double)

Zoom the document in main GUI window. Actions have whole number
values like 20.0, 100.0, etc. Zoom to Fit uses -100 as a marker.
</source>
        <translation>zoomDocument(double)

Збільшує масштаб документа в головному вікні. Значення збільшення
встановлюється в числах типу 20.0, 100.0, і т.д. Збільшити до розміру вікна
використовує -100 як позначку.
</translation>
    </message>
    <message>
        <source>getFillTransparency([&quot;name&quot;]) -&gt; float

Returns the fill transparency of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getFillBlendmode([&quot;name&quot;]) -&gt; integer

Returns the fill blendmode of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getLineTransparency([&quot;name&quot;]) -&gt; float

Returns the line transparency of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getLineBlendmode([&quot;name&quot;]) -&gt; integer

Returns the line blendmode of the object &quot;name&quot;. If &quot;name&quot;
is not given the currently selected Item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerLocked(&quot;layer&quot;, locked)

Sets the layer &quot;layer&quot; to be locked or not. If locked is set to
true the layer will be locked.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerOutlined&quot;layer&quot;, outline)

Sets the layer &quot;layer&quot; to be locked or not. If outline is set to
true the layer will be displayed outlined.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerFlow&quot;layer&quot;, flow)

Sets the layers &quot;layer&quot;  flowcontrol to flow. If flow is set to
true text in layers above this one will flow around objects on this layer.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerBlendmode&quot;layer&quot;, blend)

Sets the layers &quot;layer&quot;  blendmode to blend.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerTransparency&quot;layer&quot;, trans)

Sets the layers &quot;layer&quot;  transparency to trans.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isLayerLocked(&quot;layer&quot;) -&gt; bool

Returns whether the layer &quot;layer&quot; is locked or not, a value of True means
that the layer &quot;layer&quot; is editable, a value of False means that the layer
&quot;layer&quot; is locked.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isLayerOutlined(&quot;layer&quot;) -&gt; bool

Returns whether the layer &quot;layer&quot; is outlined or not, a value of True means
that the layer &quot;layer&quot; is outlined, a value of False means that the layer
&quot;layer&quot; is normal.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isLayerFlow(&quot;layer&quot;) -&gt; bool

Returns whether text flows around objects on layer &quot;layer&quot;, a value of True means
that text flows around, a value of False means that the text does not flow around.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getLayerBlendmode(&quot;layer&quot;) -&gt; int

Returns the &quot;layer&quot; layer blendmode,

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getLayerTransparency(&quot;layer&quot;) -&gt; float

Returns the &quot;layer&quot; layer transparency,

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>textFlowMode(&quot;name&quot; [, state])

Enables/disables &quot;Text Flows Around Frame&quot; feature for object &quot;name&quot;.
Called with parameters string name and optional int &quot;state&quot; (0 &lt;= state &lt;= 3).
Setting &quot;state&quot; to 0 will disable text flow.
Setting &quot;state&quot; to 1 will make text flow around object frame.
Setting &quot;state&quot; to 2 will make text flow around bounding box.
Setting &quot;state&quot; to 3 will make text flow around contour line.
If &quot;state&quot; is not passed, text flow is toggled.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>duplicateObject([&quot;name&quot;]) -&gt; string

creates a Duplicate of the selected Object (or Selection Group).
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setFillTransparency(transparency, [&quot;name&quot;])

Sets the fill transparency of the object &quot;name&quot; to transparency
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setFillBlendmode(blendmode, [&quot;name&quot;])

Sets the fill blendmode of the object &quot;name&quot; to blendmode
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLineTransparency(transparency, [&quot;name&quot;])

Sets the line transparency of the object &quot;name&quot; to transparency
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLineBlendmode(blendmode, [&quot;name&quot;])

Sets the line blendmode of the object &quot;name&quot; to blendmode
is the name of one of the defined colors. If &quot;name&quot; is not given the
currently selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setInfo(&quot;author&quot;, &quot;info&quot;, &quot;description&quot;) -&gt; bool

Sets the document information. &quot;Author&quot;, &quot;Info&quot;, &quot;Description&quot; are
strings.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getPageType() -&gt; integer

Returns the type of the Page, 0 means left Page, 1 is a middle Page and 2 is a right Page
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getTextLines([&quot;name&quot;]) -&gt; integer

Returns the number of lines of the text in the text frame &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>defineColor(&quot;name&quot;, c, m, y, k)

Defines a new color &quot;name&quot;. The color Value is defined via four components:
c = Cyan, m = Magenta, y = Yellow and k = Black. Color components should be in
the range from 0 to 255.

May raise ValueError if an invalid color name is specified.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getCornerRadius([&quot;name&quot;]) -&gt; integer

Returns the corner radius of the object &quot;name&quot;. The radius is
expressed in points. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>getPosition([&quot;name&quot;]) -&gt; (x,y)

Returns a (x, y) tuple with the position of the object &quot;name&quot;.
If &quot;name&quot; is not given the currently selected item is used.
The position is expressed in the actual measurement unit of the document
- see UNIT_&lt;type&gt; for reference.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>rotateObjectAbs(rot [, &quot;name&quot;])

Sets the rotation of the object &quot;name&quot; to &quot;rot&quot;. Positive values
mean counter clockwise rotation. If &quot;name&quot; is not given the currently
selected item is used.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>setLayerPrintable(&quot;layer&quot;, printable)

Sets the layer &quot;layer&quot; to be printable or not. If is the
printable set to false the layer won&apos;t be printed.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isLayerVisible(&quot;layer&quot;) -&gt; bool

Returns whether the layer &quot;layer&quot; is visible or not, a value of True means
that the layer &quot;layer&quot; is visible, a value of False means that the layer
&quot;layer&quot; is invisible.

May raise NotFoundError if the layer can&apos;t be found.
May raise ValueError if the layer name isn&apos;t acceptable.
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>insertText(&quot;text&quot;, pos, [&quot;name&quot;])

Inserts the text &quot;text&quot; at the position &quot;pos&quot; into the text frame &quot;name&quot;.
Text must be UTF encoded (see setText() as reference) The first character has an
index of 0. Inserting text at position -1 appends it to the frame. If &quot;name&quot; is
not given the currently selected Item is used.

May throw IndexError for an insertion out of bounds.
</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>About</name>
    <message>
        <source>Contributions from:</source>
        <translation>У співпраці з:</translation>
    </message>
    <message>
        <source>&amp;About</source>
        <translation>&amp;Про</translation>
    </message>
    <message>
        <source>A&amp;uthors</source>
        <translation>&amp;Автори</translation>
    </message>
    <message>
        <source>&amp;Translations</source>
        <translation>&amp;Перекладачі</translation>
    </message>
    <message>
        <source>&amp;Online</source>
        <translation>&amp;Веб ресурси</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>Development Team:</source>
        <translation>Команда розробників:</translation>
    </message>
    <message>
        <source>Official Documentation:</source>
        <translation>Офіційна документація:</translation>
    </message>
    <message>
        <source>Other Documentation:</source>
        <translation>Інша документація:</translation>
    </message>
    <message>
        <source>Homepage</source>
        <translation>Домашня сторінка</translation>
    </message>
    <message>
        <source>Online Reference</source>
        <translation>Документація на Інтернеті</translation>
    </message>
    <message>
        <source>Bugs and Feature Requests</source>
        <translation>Звітування про помилки в програмі та заявки на нові можливості</translation>
    </message>
    <message>
        <source>Mailing List</source>
        <translation>Список розсилки</translation>
    </message>
    <message>
        <source>Official Translations and Translators:</source>
        <translation>Офіційні переклади та перекладачі:</translation>
    </message>
    <message>
        <source>Previous Translation Contributors:</source>
        <translation>Попередні учасники перекладання:</translation>
    </message>
    <message>
        <source>About Scribus %1</source>
        <translation>Про Scribus %1</translation>
    </message>
    <message>
        <source>Wiki</source>
        <translation>Вікі</translation>
    </message>
    <message>
        <source>%1 %2 %3</source>
        <translation>%1 %2 %3</translation>
    </message>
    <message>
        <source>%3-%2-%1 %4 %5</source>
        <translation>%3-%2-%1 %4 %5</translation>
    </message>
    <message>
        <source>Using Ghostscript version %1</source>
        <translation>Використовує Ghostscript версії %1</translation>
    </message>
    <message>
        <source>No Ghostscript version available</source>
        <translation>Не знайдено жодної версії Ghostscript</translation>
    </message>
    <message>
        <source>&lt;b&gt;Scribus Version %1&lt;/b&gt;&lt;p&gt;%2&lt;br/&gt;%3 %4&lt;br/&gt;%5&lt;/p&gt;</source>
        <translation>&lt;b&gt;Scribus версії %1&lt;/b&gt;&lt;p&gt;%2&lt;br/&gt;%3 %4&lt;br/&gt;%5&lt;/p&gt;</translation>
    </message>
    <message>
        <source>Build ID:</source>
        <translation>Збірка:</translation>
    </message>
    <message>
        <source>This panel shows the version, build date and compiled in library support in Scribus. The C-C-T-F equates to C=littlecms C=CUPS T=TIFF support F=Fontconfig support. Last Letter is the renderer C=cairo or A=libart Missing library support is indicated by a *. This also indicates the version of Ghostscript which Scribus has detected.</source>
        <translation type="obsolete">Ця панель показує версію, дату збірки та вбудовану підтримку бібліотек в Scribus. C-C-T-F означає слідуюче: C=littlecms (кольорові профілі) C=CUPS (система друку) T=TIFF (підтримка растрового формту тіфф) F=Fontconfig (система конфігурування шрифтів). Остання літера
визначає систему рендеринку - C=cairo (Кайро) або A=libart (лібарт). Відсутність підтримки
певної бібліотеки позначається зірочкою (*). На цій панелі також показано версію Ghostscript знайдену Scribus.</translation>
    </message>
    <message>
        <source>Mac OS&amp;#174; X Aqua Port:</source>
        <translation>Мак ОС&amp;#174; Х Аква Порт:</translation>
    </message>
    <message>
        <source>Windows&amp;#174; Port:</source>
        <translation>Віндоус&amp;#174; Порт:</translation>
    </message>
    <message>
        <source>March</source>
        <translation type="obsolete">Березень</translation>
    </message>
    <message>
        <source>Tango Project Icons:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Updates</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Check for &amp;Updates</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This panel shows the version, build date and compiled in library support in Scribus. The C-C-T-F equates to C=littlecms C=CUPS T=TIFF support F=Fontconfig support. Last Letter is the renderer C=cairo or A=libart Missing library support is indicated by a *. This also indicates the version of Ghostscript which Scribus has detected. The Windows version does not use fontconfig or CUPS libraries.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Check for updates to Scribus. No data from your machine will be transferred off it.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>OS/2&amp;#174;/eComStation&amp;#8482; Port:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>AboutPlugins</name>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="obsolete">Ні</translation>
    </message>
    <message>
        <source>Filename:</source>
        <translation>Назва файла:</translation>
    </message>
    <message>
        <source>Version:</source>
        <translation>Версія:</translation>
    </message>
    <message>
        <source>Enabled:</source>
        <translation>Ввімкнено:</translation>
    </message>
    <message>
        <source>Release Date:</source>
        <translation>Дата випуску:</translation>
    </message>
    <message>
        <source>Description:</source>
        <translation>Опис:</translation>
    </message>
    <message>
        <source>Author(s):</source>
        <translation>Автор(и):</translation>
    </message>
    <message>
        <source>Copyright:</source>
        <translation>Авторські права:</translation>
    </message>
    <message>
        <source>License:</source>
        <translation>Ліцензія:</translation>
    </message>
</context>
<context>
    <name>AboutPluginsBase</name>
    <message>
        <source>Scribus: About Plug-ins</source>
        <translation>Scribus: Про модулі</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
</context>
<context>
    <name>ActionManager</name>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Open...</source>
        <translation>&amp;Відчинити...</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>Save &amp;As...</source>
        <translation>Записати &amp;як...</translation>
    </message>
    <message>
        <source>Re&amp;vert to Saved</source>
        <translation>Повернутися до за&amp;писаного</translation>
    </message>
    <message>
        <source>Collect for O&amp;utput...</source>
        <translation>Зібрати для в&amp;иводу...</translation>
    </message>
    <message>
        <source>Get Text...</source>
        <translation>Вставити текст...</translation>
    </message>
    <message>
        <source>Append &amp;Text...</source>
        <translation>Додати &amp;текст...</translation>
    </message>
    <message>
        <source>Get Image...</source>
        <translation>Вставити зображення...</translation>
    </message>
    <message>
        <source>Save &amp;Text...</source>
        <translation>Записати &amp;текст...</translation>
    </message>
    <message>
        <source>Save Page as &amp;EPS...</source>
        <translation type="obsolete">Записати сторінку як &amp;ЕPS...</translation>
    </message>
    <message>
        <source>Save as P&amp;DF...</source>
        <translation>Записати як &amp;РDF...</translation>
    </message>
    <message>
        <source>Document &amp;Setup...</source>
        <translation>Установки &amp;Документа...</translation>
    </message>
    <message>
        <source>&amp;Print...</source>
        <translation>&amp;Друк...</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Вихід</translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation>&amp;Відміна</translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation>&amp;Повтор</translation>
    </message>
    <message>
        <source>&amp;Item Action Mode</source>
        <translation>&amp;Режим дії Об&apos;єкта</translation>
    </message>
    <message>
        <source>Cu&amp;t</source>
        <translation>Ви&amp;різати</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
    <message>
        <source>Select &amp;All</source>
        <translation>Виді&amp;лити все</translation>
    </message>
    <message>
        <source>&amp;Deselect All</source>
        <translation>&amp;Убрати всі виділення</translation>
    </message>
    <message>
        <source>&amp;Search/Replace...</source>
        <translation>&amp;Пошук/Заміна...</translation>
    </message>
    <message>
        <source>Edit Image...</source>
        <translation>Редагувати зображення...</translation>
    </message>
    <message>
        <source>C&amp;olors...</source>
        <translation>&amp;Кольори...</translation>
    </message>
    <message>
        <source>&amp;Paragraph Styles...</source>
        <translation>&amp;Стилі абзаців...</translation>
    </message>
    <message>
        <source>&amp;Line Styles...</source>
        <translation>Стилі &amp;ліній...</translation>
    </message>
    <message>
        <source>&amp;Master Pages...</source>
        <translation>&amp;Головні сторінки...</translation>
    </message>
    <message>
        <source>P&amp;references...</source>
        <translation>&amp;Установки...</translation>
    </message>
    <message>
        <source>%1 pt</source>
        <translation>%1 тчк</translation>
    </message>
    <message>
        <source>&amp;Other...</source>
        <translation>&amp;Інше...</translation>
    </message>
    <message>
        <source>&amp;Left</source>
        <translation>&amp;Ліве</translation>
    </message>
    <message>
        <source>&amp;Center</source>
        <translation>По &amp;центру</translation>
    </message>
    <message>
        <source>&amp;Right</source>
        <translation>&amp;Праве</translation>
    </message>
    <message>
        <source>&amp;Block</source>
        <translation>&amp;Блок</translation>
    </message>
    <message>
        <source>&amp;Forced</source>
        <translation>&amp;Вимушене</translation>
    </message>
    <message>
        <source>&amp;%1 %</source>
        <translation>&amp;%1 %</translation>
    </message>
    <message>
        <source>&amp;Normal</source>
        <translation>&amp;Звичайне</translation>
    </message>
    <message>
        <source>&amp;Underline</source>
        <translation>&amp;Підкреслення</translation>
    </message>
    <message>
        <source>Underline &amp;Words</source>
        <translation>Підкреслення &amp;Слів</translation>
    </message>
    <message>
        <source>&amp;Strike Through</source>
        <translation>&amp;Перекреслення</translation>
    </message>
    <message>
        <source>&amp;All Caps</source>
        <translation>Всі ве&amp;ликі літери</translation>
    </message>
    <message>
        <source>Small &amp;Caps</source>
        <translation>Ка&amp;пітель</translation>
    </message>
    <message>
        <source>Su&amp;perscript</source>
        <translation>В&amp;ерхній індекс</translation>
    </message>
    <message>
        <source>Su&amp;bscript</source>
        <translation>Ни&amp;жній індекс</translation>
    </message>
    <message>
        <source>S&amp;hadow</source>
        <translation>Т&amp;інь</translation>
    </message>
    <message>
        <source>&amp;Image Effects</source>
        <translation>Ефекти зо&amp;браження</translation>
    </message>
    <message>
        <source>&amp;Tabulators...</source>
        <translation>&amp;Табулятори...</translation>
    </message>
    <message>
        <source>D&amp;uplicate</source>
        <translation>&amp;Дублювати</translation>
    </message>
    <message>
        <source>&amp;Multiple Duplicate</source>
        <translation>&amp;Багаторазове дублювання</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Group</source>
        <translation>З&amp;групувати</translation>
    </message>
    <message>
        <source>&amp;Ungroup</source>
        <translation>&amp;Розгрупувати</translation>
    </message>
    <message>
        <source>Is &amp;Locked</source>
        <translation>&amp;Замкнуті</translation>
    </message>
    <message>
        <source>Si&amp;ze is Locked</source>
        <translation>&amp;Розмір замкнутий</translation>
    </message>
    <message>
        <source>Lower to &amp;Bottom</source>
        <translation>Опустити на &amp;дно</translation>
    </message>
    <message>
        <source>Raise to &amp;Top</source>
        <translation>Підняти на&amp;гору</translation>
    </message>
    <message>
        <source>&amp;Lower</source>
        <translation>&amp;Опустити</translation>
    </message>
    <message>
        <source>&amp;Raise</source>
        <translation>&amp;Підняти</translation>
    </message>
    <message>
        <source>Send to S&amp;crapbook</source>
        <translation>Послат в &amp;чорновик</translation>
    </message>
    <message>
        <source>&amp;Attributes...</source>
        <translation>&amp;Атрибути...</translation>
    </message>
    <message>
        <source>I&amp;mage Visible</source>
        <translation>&amp;Зображення видиме</translation>
    </message>
    <message>
        <source>&amp;Update Image</source>
        <translation>По&amp;новити зображення</translation>
    </message>
    <message>
        <source>Adjust Frame to Image</source>
        <translation>Установити розмір рамки по розміру зображення</translation>
    </message>
    <message>
        <source>Extended Image Properties</source>
        <translation>Додаткові властивості зображення</translation>
    </message>
    <message>
        <source>&amp;Low Resolution</source>
        <translation>&amp;Низьке розрішення</translation>
    </message>
    <message>
        <source>&amp;Normal Resolution</source>
        <translation>&amp;Звичайне розрішення</translation>
    </message>
    <message>
        <source>&amp;Full Resolution</source>
        <translation>&amp;Повне розрішення</translation>
    </message>
    <message>
        <source>Is PDF &amp;Bookmark</source>
        <translation>&amp;Закладка PDF</translation>
    </message>
    <message>
        <source>Is PDF A&amp;nnotation</source>
        <translation>&amp;Аннотація PDF</translation>
    </message>
    <message>
        <source>Annotation P&amp;roperties</source>
        <translation>В&amp;ластивості аннотації</translation>
    </message>
    <message>
        <source>Field P&amp;roperties</source>
        <translation>Властивості &amp;поля</translation>
    </message>
    <message>
        <source>&amp;Edit Shape...</source>
        <translation>&amp;Редагувати форму...</translation>
    </message>
    <message>
        <source>&amp;Attach Text to Path</source>
        <translation>При&amp;єднати текст до шляху</translation>
    </message>
    <message>
        <source>&amp;Detach Text from Path</source>
        <translation>В&amp;ідєднати текст від шляху</translation>
    </message>
    <message>
        <source>&amp;Combine Polygons</source>
        <translation>Скомбінув&amp;ати полігони</translation>
    </message>
    <message>
        <source>Split &amp;Polygons</source>
        <translation>Розділ&amp;ити полігони</translation>
    </message>
    <message>
        <source>&amp;Bezier Curve</source>
        <translation>Крива &amp;Безьє</translation>
    </message>
    <message>
        <source>&amp;Image Frame</source>
        <translation>Рамка &amp;зображення</translation>
    </message>
    <message>
        <source>&amp;Polygon</source>
        <translation>Полі&amp;гон</translation>
    </message>
    <message>
        <source>&amp;Text Frame</source>
        <translation>&amp;Текстова рамка</translation>
    </message>
    <message>
        <source>&amp;Glyph...</source>
        <translation>&amp;Символ...</translation>
    </message>
    <message>
        <source>Sample Text</source>
        <translation>Зразковий текст</translation>
    </message>
    <message>
        <source>&amp;Insert...</source>
        <translation>&amp;Вставити...</translation>
    </message>
    <message>
        <source>Im&amp;port...</source>
        <translation>&amp;Імпортувати...</translation>
    </message>
    <message>
        <source>&amp;Delete...</source>
        <translation>&amp;Видалити...</translation>
    </message>
    <message>
        <source>&amp;Copy...</source>
        <translation>&amp;Скопіювати...</translation>
    </message>
    <message>
        <source>&amp;Move...</source>
        <translation>&amp;Перемістити...</translation>
    </message>
    <message>
        <source>&amp;Apply Master Page...</source>
        <translation>&amp;Застосувати головну сторінку...</translation>
    </message>
    <message>
        <source>Manage &amp;Guides...</source>
        <translation>Установка роз&amp;мітки...</translation>
    </message>
    <message>
        <source>&amp;Fit in window</source>
        <translation type="obsolete">&amp;Змінити до розміру вікна</translation>
    </message>
    <message>
        <source>&amp;50%</source>
        <translation>&amp;50%</translation>
    </message>
    <message>
        <source>&amp;75%</source>
        <translation>&amp;75%</translation>
    </message>
    <message>
        <source>&amp;100%</source>
        <translation>&amp;100%</translation>
    </message>
    <message>
        <source>&amp;200%</source>
        <translation>&amp;200%</translation>
    </message>
    <message>
        <source>&amp;Thumbnails</source>
        <translation>&amp;Мініатюрні зображення</translation>
    </message>
    <message>
        <source>Show &amp;Margins</source>
        <translation>Показати &amp;розмітку полів</translation>
    </message>
    <message>
        <source>Show &amp;Frames</source>
        <translation>Показати ра&amp;мки</translation>
    </message>
    <message>
        <source>Show &amp;Images</source>
        <translation>&amp;Показати зображення</translation>
    </message>
    <message>
        <source>Show &amp;Grid</source>
        <translation>Показати &amp;сітку</translation>
    </message>
    <message>
        <source>Show G&amp;uides</source>
        <translation>Показати розм&amp;ітку</translation>
    </message>
    <message>
        <source>Show &amp;Baseline Grid</source>
        <translation>Показати &amp;базову сітку</translation>
    </message>
    <message>
        <source>Show &amp;Text Chain</source>
        <translation>Показати лан&amp;цюг тексту</translation>
    </message>
    <message>
        <source>Show Control Characters</source>
        <translation>Показати контрольні знаки</translation>
    </message>
    <message>
        <source>Sn&amp;ap to Grid</source>
        <translation>П&amp;ритягування до сітки</translation>
    </message>
    <message>
        <source>Sna&amp;p to Guides</source>
        <translation>Притягування до розмітк&amp;и</translation>
    </message>
    <message>
        <source>&amp;Properties</source>
        <translation>&amp;Властивості</translation>
    </message>
    <message>
        <source>&amp;Scrapbook</source>
        <translation>&amp;Чорновик</translation>
    </message>
    <message>
        <source>&amp;Layers</source>
        <translation>П&amp;лани</translation>
    </message>
    <message>
        <source>&amp;Bookmarks</source>
        <translation>&amp;Закладки</translation>
    </message>
    <message>
        <source>&amp;Measurements</source>
        <translation>&amp;Виміри</translation>
    </message>
    <message>
        <source>Action &amp;History</source>
        <translation>Покрокова &amp;історія</translation>
    </message>
    <message>
        <source>Preflight &amp;Verifier</source>
        <translation>&amp;Попередня перевірка</translation>
    </message>
    <message>
        <source>&amp;Align and Distribute</source>
        <translation>&amp;Розташувати/Вирівняти</translation>
    </message>
    <message>
        <source>&amp;Tools</source>
        <translation>&amp;Інструменти</translation>
    </message>
    <message>
        <source>P&amp;DF Tools</source>
        <translation>PDF &amp;Інструменти</translation>
    </message>
    <message>
        <source>Select Item</source>
        <translation>Вибрати об&apos;єкт</translation>
    </message>
    <message>
        <source>T&amp;able</source>
        <translation>&amp;Таблиця</translation>
    </message>
    <message>
        <source>&amp;Shape</source>
        <translation>&amp;Фігура</translation>
    </message>
    <message>
        <source>&amp;Line</source>
        <translation>&amp;Лінія</translation>
    </message>
    <message>
        <source>&amp;Freehand Line</source>
        <translation>&amp;Вільна лінія</translation>
    </message>
    <message>
        <source>Rotate Item</source>
        <translation>Повернути об&apos;єкт</translation>
    </message>
    <message>
        <source>Zoom in or out</source>
        <translation>Змінити масштаб зображення</translation>
    </message>
    <message>
        <source>Zoom in</source>
        <translation>Збільшити масштаб зображення</translation>
    </message>
    <message>
        <source>Zoom out</source>
        <translation>Зменшити масштаб зображення</translation>
    </message>
    <message>
        <source>Edit Contents of Frame</source>
        <translation>Редагувати зміст рамки</translation>
    </message>
    <message>
        <source>Edit Text...</source>
        <translation>Редагувати текст...</translation>
    </message>
    <message>
        <source>Link Text Frames</source>
        <translation>Установити зв&apos;язок між текстовими рамками</translation>
    </message>
    <message>
        <source>Unlink Text Frames</source>
        <translation>Розірвати зв&apos;язок між текстовими рамками</translation>
    </message>
    <message>
        <source>&amp;Eye Dropper</source>
        <translation>&amp;Селектор кольору</translation>
    </message>
    <message>
        <source>Copy Item Properties</source>
        <translation>Копіювати властивості об&apos;єкта</translation>
    </message>
    <message>
        <source>Edit the text with the Story Editor</source>
        <translation>Редагувати текст вбудованим редактором</translation>
    </message>
    <message>
        <source>Insert Text Frame</source>
        <translation>Вставити текстову рамку</translation>
    </message>
    <message>
        <source>Insert Image Frame</source>
        <translation>Вставити рамку для зображення</translation>
    </message>
    <message>
        <source>Insert Table</source>
        <translation>Вставити таблицю</translation>
    </message>
    <message>
        <source>Insert Shape</source>
        <translation>Вставити геометричну форму</translation>
    </message>
    <message>
        <source>Insert Polygon</source>
        <translation>Вставити полігон</translation>
    </message>
    <message>
        <source>Insert Line</source>
        <translation>Вставити лінію</translation>
    </message>
    <message>
        <source>Insert Bezier Curve</source>
        <translation>Вставити криву Безье</translation>
    </message>
    <message>
        <source>Insert Freehand Line</source>
        <translation>Вставити вільно рисовану лінію</translation>
    </message>
    <message>
        <source>&amp;Manage Pictures</source>
        <translation>Керування &amp;зображеннями</translation>
    </message>
    <message>
        <source>&amp;Hyphenate Text</source>
        <translation>Пе&amp;ренос тексту</translation>
    </message>
    <message>
        <source>&amp;Generate Table Of Contents</source>
        <translation>&amp;Генерувати зміст</translation>
    </message>
    <message>
        <source>&amp;About Scribus</source>
        <translation>&amp;Про програму Scribus</translation>
    </message>
    <message>
        <source>About &amp;Qt</source>
        <translation>Про &amp;систему Qt</translation>
    </message>
    <message>
        <source>Toolti&amp;ps</source>
        <translation>Пі&amp;дказки</translation>
    </message>
    <message>
        <source>Scribus &amp;Manual...</source>
        <translation>&amp;Довідка по Scribus...</translation>
    </message>
    <message>
        <source>Smart &amp;Hyphen</source>
        <translation>Розумний знак &amp;переносу</translation>
    </message>
    <message>
        <source>Non Breaking Dash</source>
        <translation>Непереносне тире</translation>
    </message>
    <message>
        <source>Non Breaking &amp;Space</source>
        <translation>Непереносний промі&amp;жок</translation>
    </message>
    <message>
        <source>Page &amp;Number</source>
        <translation>Номер &amp;сторінки</translation>
    </message>
    <message>
        <source>New Line</source>
        <translation>Нова лінія</translation>
    </message>
    <message>
        <source>Frame Break</source>
        <translation>Розрив рамки</translation>
    </message>
    <message>
        <source>Column Break</source>
        <translation>Розрив колонки</translation>
    </message>
    <message>
        <source>Copyright</source>
        <translation>Копірайт</translation>
    </message>
    <message>
        <source>Registered Trademark</source>
        <translation>Зареєстрована торгова марка</translation>
    </message>
    <message>
        <source>Trademark</source>
        <translation>Торгова марка</translation>
    </message>
    <message>
        <source>Bullet</source>
        <translation>Куля</translation>
    </message>
    <message>
        <source>Em Dash</source>
        <translation>Ем риска</translation>
    </message>
    <message>
        <source>En Dash</source>
        <translation>Ен риска</translation>
    </message>
    <message>
        <source>Figure Dash</source>
        <translation>Фігурна риска</translation>
    </message>
    <message>
        <source>Quotation Dash</source>
        <translation>Цитатна риска</translation>
    </message>
    <message>
        <source>Apostrophe</source>
        <translation>Апостроф</translation>
    </message>
    <message>
        <source>Straight Double</source>
        <translation>Пряма подвійна</translation>
    </message>
    <message>
        <source>Single Left</source>
        <translation>Пряма ліва</translation>
    </message>
    <message>
        <source>Single Right</source>
        <translation>Пряма права</translation>
    </message>
    <message>
        <source>Double Left</source>
        <translation>Подвійна ліва</translation>
    </message>
    <message>
        <source>Double Right</source>
        <translation>Подвійна права</translation>
    </message>
    <message>
        <source>Single Reversed</source>
        <translation>Одинарна зворотня</translation>
    </message>
    <message>
        <source>Double Reversed</source>
        <translation>Подвійна зворотня</translation>
    </message>
    <message>
        <source>Single Left Guillemet</source>
        <translation>Одинарний лівий Гуілемет</translation>
    </message>
    <message>
        <source>Single Right Guillemet</source>
        <translation>Одинарний правий Гуілемет</translation>
    </message>
    <message>
        <source>Double Left Guillemet</source>
        <translation>Подвійний лівий Гуілемет</translation>
    </message>
    <message>
        <source>Double Right Guillemet</source>
        <translation>Подвійний правий Гуілемет</translation>
    </message>
    <message>
        <source>Low Single Comma</source>
        <translation>Низька одинарна кома</translation>
    </message>
    <message>
        <source>Low Double Comma</source>
        <translation>Низька подвійна кома</translation>
    </message>
    <message>
        <source>CJK Single Left</source>
        <translation>CJK одинарний лівий</translation>
    </message>
    <message>
        <source>CJK Single Right</source>
        <translation>CJK одинарний правий</translation>
    </message>
    <message>
        <source>CJK Double Left</source>
        <translation>CJK подвійний лівий</translation>
    </message>
    <message>
        <source>CJK Double Right</source>
        <translation>CJK подвійний правий</translation>
    </message>
    <message>
        <source>Toggle Palettes</source>
        <translation>Переключити палітри</translation>
    </message>
    <message>
        <source>Toggle Guides</source>
        <translation>Переключити направляючі</translation>
    </message>
    <message>
        <source>Manage Page Properties...</source>
        <translation>Керування установками сторінки...</translation>
    </message>
    <message>
        <source>Rulers relative to Page</source>
        <translation>Лінійки відносні до сторінки</translation>
    </message>
    <message>
        <source>&amp;Arrange Pages</source>
        <translation>&amp;Розмістити сторінки</translation>
    </message>
    <message>
        <source>Dehyphenate Text</source>
        <translation>Видалити переноси тексту</translation>
    </message>
    <message>
        <source>Print Previe&amp;w</source>
        <translation>Перегляд перед д&amp;руком</translation>
    </message>
    <message>
        <source>&amp;JavaScripts...</source>
        <translation>&amp;JavaScript сценарії...</translation>
    </message>
    <message>
        <source>Convert to Master Page...</source>
        <translation>Конвертувати в головну сторінку...</translation>
    </message>
    <message>
        <source>&amp;Cascade</source>
        <translation>&amp;Каскадне розміщення</translation>
    </message>
    <message>
        <source>&amp;Tile</source>
        <translation>&amp;Мозаїчне розміщення</translation>
    </message>
    <message>
        <source>&amp;About Plug-ins</source>
        <translation>&amp;Про модулі</translation>
    </message>
    <message>
        <source>More Info...</source>
        <translation>Додаткова інформація...</translation>
    </message>
    <message>
        <source>&amp;Printing Enabled</source>
        <translation>&amp;Друк ввімкнено</translation>
    </message>
    <message>
        <source>&amp;Flip Horizontally</source>
        <translation>&amp;Перевернути по горизонталі</translation>
    </message>
    <message>
        <source>&amp;Flip Vertically</source>
        <translation>&amp;Перевернути по вертикалі</translation>
    </message>
    <message>
        <source>Show Rulers</source>
        <translation>Показати лінійки</translation>
    </message>
    <message>
        <source>&amp;Outline</source>
        <comment>Document Outline Palette</comment>
        <translation>С&amp;хема</translation>
    </message>
    <message>
        <source>Solidus</source>
        <translation>Солідус</translation>
    </message>
    <message>
        <source>Middle Dot</source>
        <translation>Середня точка</translation>
    </message>
    <message>
        <source>En Space</source>
        <translation>Ен проміжок</translation>
    </message>
    <message>
        <source>Em Space</source>
        <translation>Ем проміжок</translation>
    </message>
    <message>
        <source>Thin Space</source>
        <translation>Вузький проміжок</translation>
    </message>
    <message>
        <source>Thick Space</source>
        <translation>Широкий проміжок</translation>
    </message>
    <message>
        <source>Mid Space</source>
        <translation>Середній проміжок</translation>
    </message>
    <message>
        <source>Hair Space</source>
        <translation>Волосинний проміжок</translation>
    </message>
    <message>
        <source>Insert Smart Hyphen</source>
        <translation>Вставити розумний знак переносу</translation>
    </message>
    <message>
        <source>Insert Non Breaking Dash</source>
        <translation>Вставити непереносне тире</translation>
    </message>
    <message>
        <source>Insert Non Breaking Space</source>
        <translation>Вставити непереносний проміжок</translation>
    </message>
    <message>
        <source>Insert Page Number</source>
        <translation>Вставити номер сторінки</translation>
    </message>
    <message>
        <source>ff</source>
        <translation>Лігатура ff</translation>
    </message>
    <message>
        <source>fi</source>
        <translation>Лігатура fi</translation>
    </message>
    <message>
        <source>fl</source>
        <translation>Лігатура fl</translation>
    </message>
    <message>
        <source>ffi</source>
        <translation>Лігатура ffi</translation>
    </message>
    <message>
        <source>ffl</source>
        <translation>Лігатура ffl</translation>
    </message>
    <message>
        <source>ft</source>
        <translation>Лігатура ft</translation>
    </message>
    <message>
        <source>st</source>
        <translation>Лігатура st</translation>
    </message>
    <message>
        <source>S&amp;tyles...</source>
        <translation>С&amp;тилі...</translation>
    </message>
    <message>
        <source>&amp;Outline</source>
        <comment>type effect</comment>
        <translation>С&amp;хема документу</translation>
    </message>
    <message>
        <source>&amp;Outlines</source>
        <comment>Convert to oulines</comment>
        <translation>&amp;Контури</translation>
    </message>
    <message>
        <source>Paste (&amp;Absolute)</source>
        <translation>Вставка (&amp;Абсолютна)</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>Insert PDF Push Button</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert PDF Text Field</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert PDF Check Box</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert PDF Combo Box</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert PDF List Box</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert Text Annotation</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert Link Annotation</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Save as &amp;EPS...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Text Frame Columns</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Frame...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Preview Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Layer Indicators</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Patterns...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Send to Patterns</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sticky Tools</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Fit to Height</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fit to Width</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Zero Width Space</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Zero Width NB Space</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>AlignDistributeBase</name>
    <message>
        <source>Align and Distribute</source>
        <translation type="unfinished">Розташувати/Вирівняти</translation>
    </message>
    <message>
        <source>Align</source>
        <translation type="unfinished">Вирівняти</translation>
    </message>
    <message>
        <source>&amp;Selected Guide:</source>
        <translation type="unfinished">&amp;Вибрана направляюча:</translation>
    </message>
    <message>
        <source>&amp;Relative To:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distribute</source>
        <translation type="unfinished">Розсередити</translation>
    </message>
    <message>
        <source>&amp;Distance:</source>
        <translation type="unfinished">&amp;Відстань:</translation>
    </message>
</context>
<context>
    <name>AlignDistributePalette</name>
    <message>
        <source>Align and Distribute</source>
        <translation>Розташувати/Вирівняти</translation>
    </message>
    <message>
        <source>Align</source>
        <translation type="unfinished">Вирівняти</translation>
    </message>
    <message>
        <source>&amp;Relative to:</source>
        <translation>В&amp;ідносно до:</translation>
    </message>
    <message>
        <source>First Selected</source>
        <translation>Перший вибраний</translation>
    </message>
    <message>
        <source>Last Selected</source>
        <translation>Останній вибраний</translation>
    </message>
    <message>
        <source>Page</source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Margins</source>
        <translation>Поля</translation>
    </message>
    <message>
        <source>Selection</source>
        <translation>Вибірка</translation>
    </message>
    <message>
        <source>Align right sides of objects to left side of anchor</source>
        <translation type="obsolete">Вирівняти праві краї об&quot;єктів по лівій стороні якоря</translation>
    </message>
    <message>
        <source>Align left sides of objects to right side of anchor</source>
        <translation type="obsolete">Вирівняти ліві краї об&quot;єктів по правій стороні якоря</translation>
    </message>
    <message>
        <source>Align bottoms</source>
        <translation>Вирівняти нижні сторони</translation>
    </message>
    <message>
        <source>Align right sides</source>
        <translation>Вирівняти по правому краю</translation>
    </message>
    <message>
        <source>Align tops of objects to bottom of anchor</source>
        <translation type="obsolete">Вирівняти об&quot;єкти по низу якоря</translation>
    </message>
    <message>
        <source>Center on vertical axis</source>
        <translation>Центрувати по вертикальній вісі</translation>
    </message>
    <message>
        <source>Align left sides</source>
        <translation>Вирівняти по лівому краю</translation>
    </message>
    <message>
        <source>Center on horizontal axis</source>
        <translation>Центрувати по горизонтальній вісі</translation>
    </message>
    <message>
        <source>Align bottoms of objects to top of anchor</source>
        <translation type="obsolete">Вирівняти низи об&quot;єктів по верху якоря</translation>
    </message>
    <message>
        <source>Align tops</source>
        <translation>Вирівняти верхи</translation>
    </message>
    <message>
        <source>Distribute</source>
        <translation type="unfinished">Розсередити</translation>
    </message>
    <message>
        <source>Make horizontal gaps between objects equal</source>
        <translation type="obsolete">Зробити одинаковими горизонтальні проміжки між об&quot;єктами</translation>
    </message>
    <message>
        <source>Make horizontal gaps between objects equal to the value specified</source>
        <translation type="obsolete">Установити задані горизонтальні проміжки між об&quot;єктами</translation>
    </message>
    <message>
        <source>Distribute right sides equidistantly</source>
        <translation>Рівномірно розподілити об&quot;єкти по правому краю</translation>
    </message>
    <message>
        <source>Distribute bottoms equidistantly</source>
        <translation>Рівномірно розподілити об&quot;єкти по нижньому краю</translation>
    </message>
    <message>
        <source>Distribute centers equidistantly horizontally</source>
        <translation> Рівномірно розподілити об&quot;єкти по центрах</translation>
    </message>
    <message>
        <source>Make vertical gaps between objects equal</source>
        <translation type="obsolete">Зробити одинаковими вертикальні проміжки між об&quot;єктами</translation>
    </message>
    <message>
        <source>Make vertical gaps between objects equal to the value specified</source>
        <translation type="obsolete">Установити задані вертикальні проміжки між об&quot;єктами</translation>
    </message>
    <message>
        <source>Distribute left sides equidistantly</source>
        <translation>Рівномірно розподілити об&quot;єкти по лівому краю</translation>
    </message>
    <message>
        <source>Distribute centers equidistantly vertically</source>
        <translation> Рівномірно розподілити об&quot;єкти по центрах по вертикалі</translation>
    </message>
    <message>
        <source>Distribute tops equidistantly</source>
        <translation>Рівномірно розподілити об&quot;єкти по верхньому краю</translation>
    </message>
    <message>
        <source>&amp;Distance:</source>
        <translation>&amp;Відстань:</translation>
    </message>
    <message>
        <source>Distribute the items with the distance specified</source>
        <translation>Розподілити об&quot;єкти на вказану відстань</translation>
    </message>
    <message>
        <source>Some objects are locked.</source>
        <translation type="obsolete">Деякі об&quot;єкти - замкнені.</translation>
    </message>
    <message>
        <source>&amp;Unlock All</source>
        <translation type="obsolete">&amp;Розімкнути всі об&quot;єкти</translation>
    </message>
    <message>
        <source>Guide</source>
        <translation>Направляюча</translation>
    </message>
    <message>
        <source>&amp;Selected Guide:</source>
        <translation>&amp;Вибрана направляюча:</translation>
    </message>
    <message>
        <source>None Selected</source>
        <translation>Нічого не було вибрано</translation>
    </message>
    <message>
        <source>Y: %1%2</source>
        <translation>Y: %1%2</translation>
    </message>
    <message>
        <source>X: %1%2</source>
        <translation>X: %1%2</translation>
    </message>
    <message>
        <source>Align right sides of items to left side of anchor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Align left sides of items to right side of anchor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Align tops of items to bottom of anchor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Align bottoms of items to top of anchor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make horizontal gaps between items equal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make horizontal gaps between items equal to the value specified</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make vertical gaps between items equal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make vertical gaps between items equal to the value specified</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make horizontal gaps between items and sides of page equal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make vertical gaps between items and the top and bottom of page margins equal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make horizontal gaps between items and sides of page margins equal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make vertical gaps between items and the top and bottom of page equal</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>AlignSelect</name>
    <message>
        <source>Align Text Left</source>
        <translation>Вирівняти текст по лівому краю</translation>
    </message>
    <message>
        <source>Align Text Right</source>
        <translation>Вирівняти текст по правому краю</translation>
    </message>
    <message>
        <source>Align Text Center</source>
        <translation>Вирівняти текст по центру</translation>
    </message>
    <message>
        <source>Align Text Justified</source>
        <translation>Вирівняти текст з обох сторін</translation>
    </message>
    <message>
        <source>Align Text Forced Justified</source>
        <translation>Змусити вирівняти текст з обох сторін</translation>
    </message>
</context>
<context>
    <name>Annot</name>
    <message>
        <source>Field Properties</source>
        <translation>Властивості поля</translation>
    </message>
    <message>
        <source>Type:</source>
        <translation>Тип:</translation>
    </message>
    <message>
        <source>Properties</source>
        <translation>Властивості</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>Ім&apos;я:</translation>
    </message>
    <message>
        <source>Tool-Tip:</source>
        <translation type="obsolete">Підказка по інструменту:</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Текст</translation>
    </message>
    <message>
        <source>Border</source>
        <translation>Рамка</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation>Колір:</translation>
    </message>
    <message>
        <source>None</source>
        <translation>Нічого немає</translation>
    </message>
    <message>
        <source>Width:</source>
        <translation>Товщина:</translation>
    </message>
    <message>
        <source>Thin</source>
        <translation>Тонка</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation>Звичайна</translation>
    </message>
    <message>
        <source>Wide</source>
        <translation>Широка</translation>
    </message>
    <message>
        <source>Style:</source>
        <translation>Стиль:</translation>
    </message>
    <message>
        <source>Solid</source>
        <translation>Суцільна</translation>
    </message>
    <message>
        <source>Dashed</source>
        <translation>Переривчаста</translation>
    </message>
    <message>
        <source>Underline</source>
        <translation>Підкреслена</translation>
    </message>
    <message>
        <source>Beveled</source>
        <translation>Фасочна</translation>
    </message>
    <message>
        <source>Inset</source>
        <translation>Вкладка</translation>
    </message>
    <message>
        <source>Other</source>
        <translation>Інша</translation>
    </message>
    <message>
        <source>Read Only</source>
        <translation>Лише для читання</translation>
    </message>
    <message>
        <source>Required</source>
        <translation>Необхідне</translation>
    </message>
    <message>
        <source>Don&apos;t Export Value</source>
        <translation type="obsolete">Не експортувати значення</translation>
    </message>
    <message>
        <source>Visibility:</source>
        <translation>Видимість:</translation>
    </message>
    <message>
        <source>Visible</source>
        <translation>Видима</translation>
    </message>
    <message>
        <source>Hidden</source>
        <translation>Схована</translation>
    </message>
    <message>
        <source>No Print</source>
        <translation>Не друкувати</translation>
    </message>
    <message>
        <source>No View</source>
        <translation>Не показувати</translation>
    </message>
    <message>
        <source>Appearance</source>
        <translation>Зовнішній вигляд</translation>
    </message>
    <message>
        <source>Text for Button Down</source>
        <translation>Текста для натиснутої кнопки</translation>
    </message>
    <message>
        <source>Text for Roll Over</source>
        <translation>Текст для зображення, розміщеного поверх</translation>
    </message>
    <message>
        <source>Icons</source>
        <translation>Іконки</translation>
    </message>
    <message>
        <source>Use Icons</source>
        <translation>Використовувати іконки</translation>
    </message>
    <message>
        <source>Remove</source>
        <translation>Видалити</translation>
    </message>
    <message>
        <source>Pressed</source>
        <translation>Натиснута</translation>
    </message>
    <message>
        <source>Roll Over</source>
        <translation>Розміщення поверх</translation>
    </message>
    <message>
        <source>Icon Placement...</source>
        <translation>Розміщення іконок...</translation>
    </message>
    <message>
        <source>Highlight</source>
        <translation>Виділення</translation>
    </message>
    <message>
        <source>Invert</source>
        <translation>Негатив</translation>
    </message>
    <message>
        <source>Outlined</source>
        <translation>Обведена</translation>
    </message>
    <message>
        <source>Push</source>
        <translation>Натиснути</translation>
    </message>
    <message>
        <source>Multi-Line</source>
        <translation>Багаторядкова</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>Пароль</translation>
    </message>
    <message>
        <source>Limit of</source>
        <translation>Обмеження на</translation>
    </message>
    <message>
        <source>Characters</source>
        <translation>Знаки</translation>
    </message>
    <message>
        <source>Do Not Scroll</source>
        <translation>Не прокручувати</translation>
    </message>
    <message>
        <source>Do Not Spell Check</source>
        <translation>Не перевіряти написання</translation>
    </message>
    <message>
        <source>Check Style:</source>
        <translation>Перевірити Стиль:</translation>
    </message>
    <message>
        <source>Default is Checked</source>
        <translation>Вибране значення по умовчанню</translation>
    </message>
    <message>
        <source>Editable</source>
        <translation>Можна редагувати</translation>
    </message>
    <message>
        <source>Options</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>Event:</source>
        <translation>Подія:</translation>
    </message>
    <message>
        <source>Script:</source>
        <translation>Сценарій:</translation>
    </message>
    <message>
        <source>Edit...</source>
        <translation>Редагування...</translation>
    </message>
    <message>
        <source>Submit to URL:</source>
        <translation>Відправити на URL:</translation>
    </message>
    <message>
        <source>Submit Data as HTML</source>
        <translation>Послати дані як HTML</translation>
    </message>
    <message>
        <source>Import Data from:</source>
        <translation>Імпортувати дані з:</translation>
    </message>
    <message>
        <source>Destination</source>
        <translation>Призначення</translation>
    </message>
    <message>
        <source>To File:</source>
        <translation>Зберегти:</translation>
    </message>
    <message>
        <source>Change...</source>
        <translation>Змінити...</translation>
    </message>
    <message>
        <source>Page:</source>
        <translation>Сторінка:</translation>
    </message>
    <message>
        <source>X-Pos:</source>
        <translation>Поз. Х:</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source>Y-Pos:</source>
        <translation>Поз. У:</translation>
    </message>
    <message>
        <source>Action</source>
        <translation>Дія</translation>
    </message>
    <message>
        <source>Field is formatted as:</source>
        <translation>Поле відформатоване як:</translation>
    </message>
    <message>
        <source>Number Format</source>
        <translation>Формат числа</translation>
    </message>
    <message>
        <source>Decimals:</source>
        <translation>Десяткові:</translation>
    </message>
    <message>
        <source>Use Currency Symbol</source>
        <translation>Використовувати знак валюти</translation>
    </message>
    <message>
        <source>Prepend Currency Symbol</source>
        <translation>Розмістити спереду символ валюти</translation>
    </message>
    <message>
        <source>Formatting</source>
        <translation>Формати</translation>
    </message>
    <message>
        <source>Percent Format</source>
        <translation>Формат процентів</translation>
    </message>
    <message>
        <source>Date Format</source>
        <translation>Формат дати</translation>
    </message>
    <message>
        <source>Time Format</source>
        <translation>Формат часу</translation>
    </message>
    <message>
        <source>Custom Scripts</source>
        <translation>Зовнішні сценарії</translation>
    </message>
    <message>
        <source>Format:</source>
        <translation>Формат:</translation>
    </message>
    <message>
        <source>Keystroke:</source>
        <translation>Клавіша:</translation>
    </message>
    <message>
        <source>Format</source>
        <translation>Формат</translation>
    </message>
    <message>
        <source>Value is not validated</source>
        <translation>Значення не перевірене</translation>
    </message>
    <message>
        <source>Value must be greater than or equal to:</source>
        <translation>Значення має бути білье або рівне:</translation>
    </message>
    <message>
        <source>and less or equal to:</source>
        <translation>і менше або рівне:</translation>
    </message>
    <message>
        <source>Custom validate script:</source>
        <translation>Зовнішній сценарій перевірки:</translation>
    </message>
    <message>
        <source>Validate</source>
        <translation>Перевірити</translation>
    </message>
    <message>
        <source>Value is not calculated</source>
        <translation>Значення не вирахуване</translation>
    </message>
    <message>
        <source>Value is the</source>
        <translation>Значення дорівнює</translation>
    </message>
    <message>
        <source>sum</source>
        <translation>Сумма</translation>
    </message>
    <message>
        <source>product</source>
        <translation>помножене</translation>
    </message>
    <message>
        <source>average</source>
        <translation>середнє арифметичне</translation>
    </message>
    <message>
        <source>minimum</source>
        <translation>мінімум</translation>
    </message>
    <message>
        <source>maximum</source>
        <translation>максимум</translation>
    </message>
    <message>
        <source>of the following fields:</source>
        <translation>з наступих полів:</translation>
    </message>
    <message>
        <source>Pick...</source>
        <translation>Вибрати...</translation>
    </message>
    <message>
        <source>Custom calculation script:</source>
        <translation>Зовнішній сценарій обчислення:</translation>
    </message>
    <message>
        <source>Calculate</source>
        <translation>Обчислити</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>Enter a comma separated list of fields here</source>
        <translation>Введіть список полів, розділений комами</translation>
    </message>
    <message>
        <source>You need at least the Icon for Normal to use Icons for Buttons</source>
        <translation>Вам потрібна, як мінімум, іконка для Нормального, щоб використовувати іконки для кнопок</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Example:</source>
        <translation>Приклад:</translation>
    </message>
    <message>
        <source>Selection Change</source>
        <translation>Зміни вибірки</translation>
    </message>
    <message>
        <source>Button</source>
        <translation>Кнопка</translation>
    </message>
    <message>
        <source>Text Field</source>
        <translation>Текстове поле</translation>
    </message>
    <message>
        <source>Check Box</source>
        <translation>Вибіркове поле</translation>
    </message>
    <message>
        <source>Combo Box</source>
        <translation>Комбінований випадаючий список</translation>
    </message>
    <message>
        <source>List Box</source>
        <translation>Випадаючий список</translation>
    </message>
    <message>
        <source>Check</source>
        <translation>Галочка</translation>
    </message>
    <message>
        <source>Cross</source>
        <translation>Хрест</translation>
    </message>
    <message>
        <source>Diamond</source>
        <translation>Ромб</translation>
    </message>
    <message>
        <source>Circle</source>
        <translation>Коло</translation>
    </message>
    <message>
        <source>Star</source>
        <translation>Зірка</translation>
    </message>
    <message>
        <source>Square</source>
        <translation>Квадрат</translation>
    </message>
    <message>
        <source>Go To</source>
        <translation>Перейти до</translation>
    </message>
    <message>
        <source>Submit Form</source>
        <translation>Відправити форму</translation>
    </message>
    <message>
        <source>Reset Form</source>
        <translation>Очистити форму</translation>
    </message>
    <message>
        <source>Import Data</source>
        <translation>Імпортувати дані</translation>
    </message>
    <message>
        <source>Mouse Up</source>
        <translation>Миша вгору</translation>
    </message>
    <message>
        <source>Mouse Down</source>
        <translation>Миша вниз</translation>
    </message>
    <message>
        <source>Mouse Enter</source>
        <translation>Миша вхід</translation>
    </message>
    <message>
        <source>Mouse Exit</source>
        <translation>Миша вихід</translation>
    </message>
    <message>
        <source>On Focus</source>
        <translation>На фокусування</translation>
    </message>
    <message>
        <source>On Blur</source>
        <translation>На розмивання</translation>
    </message>
    <message>
        <source>Plain</source>
        <translation>Звичайний</translation>
    </message>
    <message>
        <source>Number</source>
        <translation>Номер</translation>
    </message>
    <message>
        <source>Percentage</source>
        <translation>Частка</translation>
    </message>
    <message>
        <source>Date</source>
        <translation>Дата</translation>
    </message>
    <message>
        <source>Time</source>
        <translation>Час</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation>Нестандартний</translation>
    </message>
    <message>
        <source>Font for use with PDF 1.3:</source>
        <translation>Шрифт для використання в PDF 1.3:</translation>
    </message>
    <message>
        <source>Flag is ignored for PDF 1.3</source>
        <translation>Установка ігнорується в PDF 1.3</translation>
    </message>
    <message>
        <source>PDF Files (*.pdf);;All Files (*)</source>
        <translation>PDF файли (*.pdf);;Всі файли (*)</translation>
    </message>
    <message>
        <source>JavaScript</source>
        <translation>JavaScript</translation>
    </message>
    <message>
        <source>Images (*.tif *.png *.jpg *.xpm);;PostScript (*.eps);;All Files (*)</source>
        <translation type="obsolete">Зображення (*.tif *.png *.jpg *.xpm);;PostScript (*.eps);;Всі файли (*)</translation>
    </message>
    <message>
        <source>None</source>
        <comment>highlight</comment>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>None</source>
        <comment>action</comment>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>Tooltip:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Do Not Export Value</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Images (*.tif *.png *.jpg *.xpm);;PostScript (*.eps *.epsi);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Annota</name>
    <message>
        <source>Annotation Properties</source>
        <translation>Властивості аннотації</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Текст</translation>
    </message>
    <message>
        <source>Link</source>
        <translation>Ссилка</translation>
    </message>
    <message>
        <source>External Link</source>
        <translation>Зовнішня ссилка</translation>
    </message>
    <message>
        <source>External Web-Link</source>
        <translation>Зовнішня ссилка на світову мережу</translation>
    </message>
    <message>
        <source>Destination</source>
        <translation>Призначення</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> точок</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>PDF-Documents (*.pdf);;All Files (*)</source>
        <translation>Документи PDF (*.pdf);;Всі файли (*)</translation>
    </message>
    <message>
        <source>&amp;Type:</source>
        <translation>&amp;Тип:</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation>З&amp;мінити...</translation>
    </message>
    <message>
        <source>&amp;Page:</source>
        <translation>&amp;Сторінка:</translation>
    </message>
    <message>
        <source>&amp;X-Pos</source>
        <translation>Поз. &amp;Х</translation>
    </message>
    <message>
        <source>&amp;Y-Pos:</source>
        <translation>Поз. &amp;У:</translation>
    </message>
</context>
<context>
    <name>ApplyMasterPageDialog</name>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайна</translation>
    </message>
    <message>
        <source>Apply Master Page</source>
        <translation>Застосувати головну сторінку</translation>
    </message>
    <message>
        <source>&amp;Master Page:</source>
        <translation>&amp;Головна сторінка:</translation>
    </message>
    <message>
        <source>Apply To</source>
        <translation>Застосувати до</translation>
    </message>
    <message>
        <source>Current &amp;page</source>
        <translation>Активна &amp;сторінка</translation>
    </message>
    <message>
        <source>Alt+P</source>
        <translation>Alt+P</translation>
    </message>
    <message>
        <source>&amp;Even pages</source>
        <translation>&amp;Парні сторінки</translation>
    </message>
    <message>
        <source>Alt+E</source>
        <translation>Alt+E</translation>
    </message>
    <message>
        <source>O&amp;dd pages</source>
        <translation>&amp;Непарні сторінки</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>&amp;All pages</source>
        <translation>&amp;Всі сторінки</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Within range</source>
        <translation>В д&amp;іапазоні</translation>
    </message>
    <message>
        <source>Alt+W</source>
        <translation>Alt+W</translation>
    </message>
    <message>
        <source>to</source>
        <translation>до</translation>
    </message>
    <message>
        <source>Alt+O</source>
        <translation>Alt+O</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
    <message>
        <source>Apply the selected master page to even, odd or all pages within the following range</source>
        <translation>Застосувати вибрану головну сторінку до непарних, парних, чи всіх сторінок в цьому діапазоні</translation>
    </message>
</context>
<context>
    <name>ArrowChooser</name>
    <message>
        <source>None</source>
        <translation>Нічого</translation>
    </message>
</context>
<context>
    <name>Barcode</name>
    <message>
        <source>&amp;Barcode Generator...</source>
        <translation>&amp;Генератор штрих-кодів...</translation>
    </message>
    <message>
        <source>Scribus frontend for Pure Postscript Barcode Writer</source>
        <translation>Інтерфейс Scribus для самостійного генератора Postscript штрих-кодів</translation>
    </message>
</context>
<context>
    <name>BarcodeGenerator</name>
    <message>
        <source>Error opening file: %1</source>
        <translation>Відчинити файл: %1 не вдалося</translation>
    </message>
    <message>
        <source>12 or 13 digits</source>
        <translation>12 чи 13 цифр</translation>
    </message>
    <message>
        <source>8 digits</source>
        <translation>8 цифр</translation>
    </message>
    <message>
        <source>11 or 12 digits</source>
        <translation>11 чи 12 цифр</translation>
    </message>
    <message>
        <source>7 or 8 digits</source>
        <translation>7 чи 8 цифр</translation>
    </message>
    <message>
        <source>5 digits</source>
        <translation>5 цифр</translation>
    </message>
    <message>
        <source>2 digits</source>
        <translation>2 цифри</translation>
    </message>
    <message>
        <source>9 or 10 digits separated appropriately with dashes</source>
        <translation type="obsolete">9 чи 10 цифр відповідно розділених тире</translation>
    </message>
    <message>
        <source>Variable number of characters, digits and any of the symbols -. *$/+%.</source>
        <translation>Змінне число знаків, цифр чи символів -. *$/+%.</translation>
    </message>
    <message>
        <source>Variable number of ASCII characters and special function symbols, starting with the appropriate start character for the initial character set. UCC/EAN-128s must have a mandatory FNC 1 symbol immediately following the start character.</source>
        <translation>Змінне число ASCII знаків та особливих символів функцій починаючи з відповідного початкового знаку для початкового набору знаків. UCC/EAN-128s повинен містити обов&apos;язковий символ FNC 1 відразу після початкового знаку.</translation>
    </message>
    <message>
        <source>Variable number of digits and any of the symbols -$:/.+ABCD.</source>
        <translation>Змінне число знаків, цифр чи символів -$:/.+ABCD.</translation>
    </message>
    <message>
        <source>Variable number of digits. An ITF-14 is 14 characters and does not have a check digit</source>
        <translation>Змінне число цифр.  ITF-14 включає 14 знаків і не містить перевірочної цифри</translation>
    </message>
    <message>
        <source>Variable number of digits</source>
        <translation>Змінне число цифр</translation>
    </message>
    <message>
        <source>Variable number of digits and capital letters</source>
        <translation>Змінне число цифр та заголовних знаків</translation>
    </message>
    <message>
        <source>Variable number of hexadecimal characters</source>
        <translation>Змінне число шістнадцятеричних знаків</translation>
    </message>
    <message>
        <source>Barcode incomplete</source>
        <translation>Штрих-код неповний</translation>
    </message>
    <message>
        <source>For ISBN-10 the data should contain 9 or 10 <byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/>digits separated appropriately by dash characters.
For ISBN-13 the data should contain 12 or 13 <byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/>digits separated appropriately by dash characters.
If the last digit is not given then the ISBN <byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/><byte value="x9"/>checkdigit is calculated automatically.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>BarcodeGeneratorBase</name>
    <message>
        <source>Barcode Creator</source>
        <translation>Редактор штрих-кодів</translation>
    </message>
    <message>
        <source>Barcode</source>
        <translation>Штрих-код</translation>
    </message>
    <message>
        <source>&amp;Type:</source>
        <translation>&amp;Тип:</translation>
    </message>
    <message>
        <source>Select one of the available barcode type here</source>
        <translation>Виберіть один з усталених типів штрих-кодів</translation>
    </message>
    <message>
        <source>The numeric representation of the code itself. See the help message below</source>
        <translation>Чисельне представлення штрих-коду. Дивіться інформаційне повідомлення внизу</translation>
    </message>
    <message>
        <source>Reset the barcode samples</source>
        <translation>Перезавантажити зразки штрих-кодів</translation>
    </message>
    <message>
        <source>&amp;Include text in barcode</source>
        <translation>&amp;Включити текст в штрих-код</translation>
    </message>
    <message>
        <source>Alt+I</source>
        <translation>Alt+I</translation>
    </message>
    <message>
        <source>If checked, there will be numbers in the barcode too</source>
        <translation>Якщо вибрано, в штрих-коді будуть присутні цифри</translation>
    </message>
    <message>
        <source>&amp;Guard whitespace</source>
        <translation>&amp;Оберігати проміжки</translation>
    </message>
    <message>
        <source>Alt+G</source>
        <translation>Alt+G</translation>
    </message>
    <message>
        <source>Draw arrows to be sure of space next the code</source>
        <translation>Рисувати стрілки для явного представлення простору біля коду</translation>
    </message>
    <message>
        <source>Colors</source>
        <translation>Кольори</translation>
    </message>
    <message>
        <source>&amp;Background</source>
        <translation>&amp;Фон</translation>
    </message>
    <message>
        <source>Alt+B</source>
        <translation>Alt+B</translation>
    </message>
    <message>
        <source>Background color - under the code lines</source>
        <translation>Фоновий колір - під штрихами коду</translation>
    </message>
    <message>
        <source>&amp;Lines</source>
        <translation>&amp;Штрихи</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation>Alt+L</translation>
    </message>
    <message>
        <source>Color of the lines in barcode</source>
        <translation>Колір штрихів штрих-коду</translation>
    </message>
    <message>
        <source>&amp;Text</source>
        <translation>&amp;Текст</translation>
    </message>
    <message>
        <source>Alt+T</source>
        <translation>Alt+T</translation>
    </message>
    <message>
        <source>Color of the text and numbers</source>
        <translation>Колір тексту на цифр</translation>
    </message>
    <message>
        <source>Hints and help is shown here</source>
        <translation>Тут показуються підказки та допомога</translation>
    </message>
    <message>
        <source>Preview of the result. 72dpi sample.</source>
        <translation>Попередній перегляд результатів. 72тнд зразок.</translation>
    </message>
    <message>
        <source>Co&amp;de:</source>
        <translation>Ко&amp;д:</translation>
    </message>
    <message>
        <source>I&amp;nclude checksum</source>
        <translation>В&amp;ключити контрольну суму</translation>
    </message>
    <message>
        <source>Alt+N</source>
        <translation>Alt+N</translation>
    </message>
    <message>
        <source>Generate and include a checksum in barcode</source>
        <translation>Згенерувати та включити в штрих-код контрольну суму</translation>
    </message>
    <message>
        <source>Incl&amp;ude checksum digit</source>
        <translation>Вк&amp;лючити контрольну цифру</translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation>Alt+U</translation>
    </message>
    <message>
        <source>Include the checksum digit in the barcode text</source>
        <translation>Включити в текст штрих-коду контрольну цифру</translation>
    </message>
</context>
<context>
    <name>Biblio</name>
    <message>
        <source>Scrapbook</source>
        <translation>Чорновик</translation>
    </message>
    <message>
        <source>Delete</source>
        <translation>Видалити</translation>
    </message>
    <message>
        <source>Object</source>
        <translation>Об&apos;єкт</translation>
    </message>
    <message>
        <source>New Entry</source>
        <translation>Новий екземпляр</translation>
    </message>
    <message>
        <source>Rename</source>
        <translation>Перейменувати</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation type="obsolete">&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Load...</source>
        <translation type="obsolete">За&amp;вантажити...</translation>
    </message>
    <message>
        <source>Save &amp;As...</source>
        <translation type="obsolete">Записати &amp;як...</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation type="obsolete">&amp;Зачинити</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation type="obsolete">&amp;Файл</translation>
    </message>
    <message>
        <source>&amp;Preview</source>
        <translation type="obsolete">&amp;Попередній перегляд</translation>
    </message>
    <message>
        <source>&amp;Name:</source>
        <translation>&amp;Ім&apos;я:</translation>
    </message>
    <message>
        <source>Name &quot;%1&quot; is not unique.
Please choose another.</source>
        <translation>Ім&apos;я &quot;%1&quot; вже використане.
Будь-ласка виберіть інше.</translation>
    </message>
    <message>
        <source>Choose a Scrapbook Directory</source>
        <translation>Виберіть директорію для чорновика</translation>
    </message>
    <message>
        <source>Choose a Directory</source>
        <translation>Виберіть директорію</translation>
    </message>
    <message>
        <source>Scrapbook (*.scs)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Choose a scrapbook file to import</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Create a new scrapbook page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Load an existing scrapbook</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Save the selected scrapbook</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Import an scrapbook file from Scribus &lt;=1.3.2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Close the selected scrapbook</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Copy To:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Move To:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Main</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Copied Items</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>BookMView</name>
    <message>
        <source>Bookmarks</source>
        <translation>Закладки</translation>
    </message>
    <message>
        <source>Move Bookmark</source>
        <translation>Перемістити закладку</translation>
    </message>
    <message>
        <source>Insert Bookmark</source>
        <translation>Вставити закладку</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
</context>
<context>
    <name>BookPalette</name>
    <message>
        <source>Bookmarks</source>
        <translation>Закладки</translation>
    </message>
</context>
<context>
    <name>ButtonIcon</name>
    <message>
        <source>Icon Placement</source>
        <translation>Розміщення іконок</translation>
    </message>
    <message>
        <source>Layout:</source>
        <translation>Схема:</translation>
    </message>
    <message>
        <source>Scale:</source>
        <translation>Масштаб:</translation>
    </message>
    <message>
        <source>Always</source>
        <translation>Завжди</translation>
    </message>
    <message>
        <source>When Icon is too small</source>
        <translation>Коли іконка занадто мала</translation>
    </message>
    <message>
        <source>When Icon is too big</source>
        <translation>Коли іконка занадто велика</translation>
    </message>
    <message>
        <source>Never</source>
        <translation>Ніколи</translation>
    </message>
    <message>
        <source>Scale How:</source>
        <translation>Змінити масштаб на:</translation>
    </message>
    <message>
        <source>Proportional</source>
        <translation>Пропорційно</translation>
    </message>
    <message>
        <source>Non Proportional</source>
        <translation>Непропорційно</translation>
    </message>
    <message>
        <source>Icon</source>
        <translation>Іконка</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>Reset</source>
        <translation>Скинути значення</translation>
    </message>
    <message>
        <source>Caption only</source>
        <translation>Лише описання</translation>
    </message>
    <message>
        <source>Icon only</source>
        <translation>Лише іконка</translation>
    </message>
    <message>
        <source>Caption below Icon</source>
        <translation>Описання під іконкою</translation>
    </message>
    <message>
        <source>Caption above Icon</source>
        <translation>Описання над іконкою</translation>
    </message>
    <message>
        <source>Caption right to Icon</source>
        <translation>Описання справа від іконки</translation>
    </message>
    <message>
        <source>Caption left to Icon</source>
        <translation>Описання зліва від іконки</translation>
    </message>
    <message>
        <source>Caption overlays Icon</source>
        <translation>Описання поверх іконки</translation>
    </message>
</context>
<context>
    <name>CMSPrefs</name>
    <message>
        <source>System Profiles</source>
        <translation>Системні профілі</translation>
    </message>
    <message>
        <source>Rendering Intents</source>
        <translation>Схеми перерахунку кольорів</translation>
    </message>
    <message>
        <source>Perceptual</source>
        <translation>Уявний</translation>
    </message>
    <message>
        <source>Relative Colorimetric</source>
        <translation>Відносна кольорометрія</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation>Насичення</translation>
    </message>
    <message>
        <source>Absolute Colorimetric</source>
        <translation>Абсолютна кольорометрія</translation>
    </message>
    <message>
        <source>Default color profile for solid colors on the page</source>
        <translation type="obsolete">Стандартний кольоровий профіль для однотонних кольорів на сторінці</translation>
    </message>
    <message>
        <source>Color profile that you have generated or received from the manufacturer.
This profile should be specific to your monitor and not a generic profile (i.e. sRGB).</source>
        <translation>Кольоровий профіль побудований Вами або отриманий від виробника обладнання.
Цей профіль має точно відповідати Вашому монітору, а не бути загальним профілем (типу sRGB).</translation>
    </message>
    <message>
        <source>Color profile for your printer model from the manufacturer.
This profile should be specific to your printer and not a generic profile (i.e. sRGB).</source>
        <translation>Кольоровий профіль для Вашої моделі прінтера отриманий від виробника обладнання.
Цей профіль має точно відповідати Вашому монітору, а не бути загальним профілем (типу sRGB).</translation>
    </message>
    <message>
        <source>Default rendering intent for your monitor. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
        <translation type="obsolete">Стандартна схема перерахунку кольорів для Вашого монітора. Не змінюйте
її без необхідності. У більшості випадків краще вибрати відносну колориметричну
або перцептивну схему.</translation>
    </message>
    <message>
        <source>Default rendering intent for your printer. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
        <translation type="obsolete">Стандартна схема перерахунку кольорів для Вашого прінтера. Не змінюйте
її без необхідності. У більшості випадків краще вибрати відносну колориметричну
або перцептивну схему.</translation>
    </message>
    <message>
        <source>Enable &apos;soft proofing&apos; of how your document colors will print,
based on the chosen printer profile.</source>
        <translation>Ввімкнути імітацію друкованих кольорів на моніторі (м&apos;яка перевірка),
в залежності від вибраного профілю прінтера.</translation>
    </message>
    <message>
        <source>Method of showing colors on the screen which may not print properly.
This requires very accurate profiles and serves only as a warning.</source>
        <translation>Метод відображення на екрані тих кольорів, які не будуть правильно надруковані.
Вимагає наявності дуже точних кольорових профілів і служить лише як застереження.</translation>
    </message>
    <message>
        <source>Black Point Compensation is a method of improving contrast in photos.
It is recommended that you enable this if you have photos in your document.</source>
        <translation>Компенсація точки чорного - це метод покращення контрастності фотографічних зображень.
Її використаннярекомендується при наявності фотографічних зображень в документі.</translation>
    </message>
    <message>
        <source>&amp;Activate Color Management</source>
        <translation>Активувати &amp;керування палітрою кольорів</translation>
    </message>
    <message>
        <source>&amp;Solid Colors:</source>
        <translation type="obsolete">&amp;Однотонні кольори:</translation>
    </message>
    <message>
        <source>&amp;Monitor:</source>
        <translation>&amp;Екран:</translation>
    </message>
    <message>
        <source>P&amp;rinter:</source>
        <translation>Прин&amp;тер:</translation>
    </message>
    <message>
        <source>M&amp;onitor:</source>
        <translation type="obsolete">Екр&amp;ан:</translation>
    </message>
    <message>
        <source>Pr&amp;inter:</source>
        <translation type="obsolete">Пр&amp;интер:</translation>
    </message>
    <message>
        <source>Sim&amp;ulate Printer on the Screen</source>
        <translation>Сим&amp;улювати принтер на екрані</translation>
    </message>
    <message>
        <source>Mark Colors out of &amp;Gamut</source>
        <translation>Позначити кольори, які знаходяться &amp;поза гамутом</translation>
    </message>
    <message>
        <source>Use &amp;Blackpoint Compensation</source>
        <translation>Використовувати компенсаці&amp;ю точки чорного</translation>
    </message>
    <message>
        <source>&amp;RGB Pictures:</source>
        <translation>&amp;RGB зображення:</translation>
    </message>
    <message>
        <source>&amp;CMYK Pictures:</source>
        <translation>&amp;CMYK зображення:</translation>
    </message>
    <message>
        <source>Default color profile for imported CMYK images</source>
        <translation>Стандартний кольоровий профіль для імпортованих CMYK зображень</translation>
    </message>
    <message>
        <source>Default color profile for imported RGB images</source>
        <translation>Стандартний кольоровий профіль для імпортованих RGB зображень</translation>
    </message>
    <message>
        <source>&amp;RGB Solid Colors:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;CMYK Solid Colors:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Pictures:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sol&amp;id Colors:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Convert all colors to printer space</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Default color profile for solid RGB colors on the page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Default color profile for solid CMYK colors on the page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Default rendering intent for solid colors. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Default rendering intent for images. Unless you know why to change it,
Relative Colorimetric or Perceptual should be chosen.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Simulate a full color managed environment :
all colors, rgb or cmyk, are converted to printer color space.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CMYKChoose</name>
    <message>
        <source>Edit Color</source>
        <translation>Редагування кольору</translation>
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
        <translation>RGB для web</translation>
    </message>
    <message>
        <source>New</source>
        <translation>Новий</translation>
    </message>
    <message>
        <source>Old</source>
        <translation>Старий</translation>
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
        <translation>Динамічні кольорові полоси</translation>
    </message>
    <message>
        <source>Static Color Bars</source>
        <translation>Статичні кольорові полоси</translation>
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
        <source>HSV-Colormap</source>
        <translation>HSV (ВНЗ) Палітра кольорів</translation>
    </message>
    <message>
        <source>&amp;Name:</source>
        <translation>&amp;Ім&apos;я:</translation>
    </message>
    <message>
        <source>Color &amp;Model</source>
        <translation>Кольорова &amp;модель</translation>
    </message>
    <message>
        <source>Is Spot Color</source>
        <translation>Точковий колір</translation>
    </message>
    <message>
        <source>Is Registration Color</source>
        <translation>Реєстраційний колір</translation>
    </message>
    <message>
        <source>You cannot create a color named &quot;%1&quot;.
It is a reserved name for transparent color</source>
        <translation>Ви не можете створити колір з назвою &quot;%1&quot;.
Ця назва зарезервована для прозорого кольору</translation>
    </message>
    <message>
        <source>Name of the color is not unique</source>
        <translation type="obsolete">Назва кольору не являється неповторною</translation>
    </message>
    <message>
        <source>Choosing this will enable printing this on all plates. Registration colors are used for printer marks such as crop marks, registration marks and the like. These are not typically used in the layout itself.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>If color management is enabled, a triangle warning indicator is a warning the the color maybe outside of the color gamut of the current printer profile selected. What this means is the color may not print exactly as indicated on screen. More hints about gamut warnings are in the online help under Color Management.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The name of the color already exists,
please choose another one.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Choosing this will make this color a spot color, thus creating another spot when creating plates or separations. This is used most often when a logo or other color needs exact representation or cannot be replicated with CMYK inks. Metallic and fluorescent inks are good examples which cannot be easily replicated with CMYK inks.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CStylePBase</name>
    <message>
        <source>Form1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Parent</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CWDialog</name>
    <message>
        <source>Normal Vision</source>
        <translation type="obsolete">Нормальний зір</translation>
    </message>
    <message>
        <source>Protanopia (Red)</source>
        <translation type="obsolete">Протанопія (Червоний)</translation>
    </message>
    <message>
        <source>Deuteranopia (Green)</source>
        <translation type="obsolete">Дейтеранопія (Зелений)</translation>
    </message>
    <message>
        <source>Tritanopia (Blue)</source>
        <translation type="obsolete">Тританопія (Синій)</translation>
    </message>
    <message>
        <source>Full Color Blindness</source>
        <translation type="obsolete">Повний дальтонізм</translation>
    </message>
    <message>
        <source>Merging colors</source>
        <translation type="unfinished">Поєднання кольорів</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation type="unfinished">Помилка:</translation>
    </message>
    <message>
        <source>Color %1 exists already!</source>
        <translation type="unfinished">Колір %1 вже існує!</translation>
    </message>
    <message>
        <source>Color %1 appended.</source>
        <translation type="unfinished">Колір %1 додано.</translation>
    </message>
    <message>
        <source>Now opening the color manager.</source>
        <translation type="unfinished">Відкриття менеджера кольорів.</translation>
    </message>
    <message>
        <source>Color Merging</source>
        <translation type="unfinished">Об&quot;єднання кольорів</translation>
    </message>
    <message>
        <source>Unable to find the requested color. You have probably selected black, gray or white. There is no way to process this color.</source>
        <translation type="unfinished">Неможливо знайти зазначений колір. Ви, можливо, вибрали чорний, сірий, чи білий. Цей колір не може бути опрацьовано.</translation>
    </message>
</context>
<context>
    <name>CWDialogBase</name>
    <message>
        <source>Color Wheel</source>
        <translation type="unfinished">Колесо кольорів</translation>
    </message>
    <message>
        <source>Click the wheel to get the base color. Its color model depends on the chosen tab.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CMYK</source>
        <translation type="unfinished">CMYK</translation>
    </message>
    <message>
        <source>C:</source>
        <translation type="unfinished">C:</translation>
    </message>
    <message>
        <source>M:</source>
        <translation type="unfinished">M:</translation>
    </message>
    <message>
        <source>Y:</source>
        <translation type="unfinished">Y:</translation>
    </message>
    <message>
        <source>K:</source>
        <translation type="unfinished">K:</translation>
    </message>
    <message>
        <source>RGB:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>RGB</source>
        <translation type="unfinished">RGB</translation>
    </message>
    <message>
        <source>R:</source>
        <translation type="unfinished">R:</translation>
    </message>
    <message>
        <source>G:</source>
        <translation type="unfinished">G:</translation>
    </message>
    <message>
        <source>B:</source>
        <translation type="unfinished">B:</translation>
    </message>
    <message>
        <source>CMYK:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Document</source>
        <translation type="unfinished">Документ</translation>
    </message>
    <message>
        <source>Select one of the methods to create a color scheme. Refer to documentation for more information.</source>
        <translation type="unfinished">Виберіть один з методів для створення кольорової схеми. Зверніться до документації за додатковою інформацією.</translation>
    </message>
    <message>
        <source>Angle:</source>
        <translation type="unfinished">Кут:</translation>
    </message>
    <message>
        <source>Difference between the selected value and the counted ones. Refer to documentation for more information.</source>
        <translation type="unfinished">Різниця між вибраним значенням та вирахуваними. Зверніться до документації за додатковою інформацією.</translation>
    </message>
    <message>
        <source>Preview:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Vision Defect Type:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sample color scheme.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Colors of your chosen color scheme.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Merge</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+M</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Merge created colors into the document colors</source>
        <translation type="unfinished">Ввести створені кольори в кольори документу</translation>
    </message>
    <message>
        <source>&amp;Replace</source>
        <translation type="unfinished">&amp;Заміна</translation>
    </message>
    <message>
        <source>Alt+R</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Replace created colors in the document colors</source>
        <translation type="unfinished">Замінити кольори документу створеними кольорами</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Leave colors untouched</source>
        <translation type="unfinished">Залишити кольори без змін</translation>
    </message>
    <message>
        <source>Simulate common vision defects here. Select type of the defect.</source>
        <translation type="unfinished">Симуляція найбіль поширених недоліків зору. Виберіть тип недоліку.</translation>
    </message>
    <message>
        <source>Color Scheme Method</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source> %</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>HSV:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>HSV</source>
        <translation type="unfinished">HSV</translation>
    </message>
    <message>
        <source>H:</source>
        <translation type="unfinished">H:</translation>
    </message>
    <message>
        <source>S:</source>
        <translation type="unfinished">S:</translation>
    </message>
    <message>
        <source>V:</source>
        <translation type="unfinished">V:</translation>
    </message>
    <message>
        <source>Result Colors</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ChTable</name>
    <message>
        <source>You can see a thumbnail if you press and hold down the right mouse button. The Insert key inserts a Glyph into the Selection below and the Delete key removes the last inserted one</source>
        <translation type="obsolete">Ви можете побачити зменшене зображення, якщо Ви натиснете та будете тримати праву кнопку
миші. Клавіша &quot;Вставити&quot; вставляє знак у вибірку внизу а клавіша &quot;Видалити&quot; видаляє
останній вставлений знак</translation>
    </message>
</context>
<context>
    <name>CharSelect</name>
    <message>
        <source>Select Character:</source>
        <translation type="obsolete">Вибрати символ:</translation>
    </message>
    <message>
        <source>Font:</source>
        <translation>Шрифт:</translation>
    </message>
    <message>
        <source>Character Class:</source>
        <translation>Символьний клас:</translation>
    </message>
    <message>
        <source>&amp;Insert</source>
        <translation>&amp;Вставити</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation type="obsolete">&amp;Зачинити</translation>
    </message>
    <message>
        <source>Insert the characters at the cursor in the text</source>
        <translation>Вставити символи в текст в місці знаходження курсора</translation>
    </message>
    <message>
        <source>Delete the current selection(s).</source>
        <translation>Видалити активну вибірку.</translation>
    </message>
    <message>
        <source>Full Character Set</source>
        <translation>Повний набір символів</translation>
    </message>
    <message>
        <source>Basic Latin</source>
        <translation>Елементарна Латиниця</translation>
    </message>
    <message>
        <source>Latin-1 Supplement</source>
        <translation>Latin-1 додаток</translation>
    </message>
    <message>
        <source>Latin Extended-A</source>
        <translation>Розширена латиниця-А</translation>
    </message>
    <message>
        <source>Latin Extended-B</source>
        <translation>Розширена латиниця-B</translation>
    </message>
    <message>
        <source>General Punctuation</source>
        <translation>Основні знаки пунктуації</translation>
    </message>
    <message>
        <source>Super- and Subscripts</source>
        <translation>Верхній та нижній індекси</translation>
    </message>
    <message>
        <source>Currency Symbols</source>
        <translation>Знаки валют</translation>
    </message>
    <message>
        <source>Letterlike Symbols</source>
        <translation>Літерні символи</translation>
    </message>
    <message>
        <source>Number Forms</source>
        <translation>Числові форми</translation>
    </message>
    <message>
        <source>Arrows</source>
        <translation>Стрілки</translation>
    </message>
    <message>
        <source>Mathematical Operators</source>
        <translation>Математичні оператори</translation>
    </message>
    <message>
        <source>Box Drawing</source>
        <translation>Знаки рисування стінок</translation>
    </message>
    <message>
        <source>Block Elements</source>
        <translation>Блокові елементи</translation>
    </message>
    <message>
        <source>Geometric Shapes</source>
        <translation>Геометричні форми</translation>
    </message>
    <message>
        <source>Miscellaneous Symbols</source>
        <translation>Різні символи</translation>
    </message>
    <message>
        <source>Dingbats</source>
        <translation>Іконки</translation>
    </message>
    <message>
        <source>Small Form Variants</source>
        <translation>Зменшені варіанти</translation>
    </message>
    <message>
        <source>Ligatures</source>
        <translation>Лігатури</translation>
    </message>
    <message>
        <source>Specials</source>
        <translation>Особливі</translation>
    </message>
    <message>
        <source>Greek</source>
        <translation>Грецька</translation>
    </message>
    <message>
        <source>Greek Extended</source>
        <translation>Розширена грецька</translation>
    </message>
    <message>
        <source>Cyrillic</source>
        <translation>Кирилиця</translation>
    </message>
    <message>
        <source>Cyrillic Supplement</source>
        <translation>Розширена кирилиця</translation>
    </message>
    <message>
        <source>Arabic</source>
        <translation>Арабська</translation>
    </message>
    <message>
        <source>Arabic Extended A</source>
        <translation>Розширена арабська А</translation>
    </message>
    <message>
        <source>Arabic Extended B</source>
        <translation>Розширена арабська B</translation>
    </message>
    <message>
        <source>Hebrew</source>
        <translation>Іврит</translation>
    </message>
    <message>
        <source>&amp;Insert Code:</source>
        <translation type="obsolete">&amp;Вставити код:</translation>
    </message>
    <message>
        <source>Close this dialog and return to text editing</source>
        <translation type="obsolete">Зачинити діалогове вікно та повернутися до редагування тексту</translation>
    </message>
    <message>
        <source>Type in a four digit unicode value directly here</source>
        <translation type="obsolete">Вставте чотиризначне  значення Юнікоду прямо в цьому місці</translation>
    </message>
    <message>
        <source>You can see a thumbnail if you press and hold down the right mouse button. The Insert key inserts a Glyph into the Selection below and the Delete key removes the last inserted one</source>
        <translation type="unfinished">Ви можете побачити зменшене зображення, якщо Ви натиснете та будете тримати праву кнопку
миші. Клавіша &quot;Вставити&quot; вставляє знак у вибірку внизу а клавіша &quot;Видалити&quot; видаляє
останній вставлений знак</translation>
    </message>
    <message>
        <source>Scribus Char Palette (*.ucp);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enhanced Palette</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Quick Palette</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hide Enhanced</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Choose a filename to open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Error</source>
        <translation type="unfinished">Помилка</translation>
    </message>
    <message>
        <source>Error reading file %1 - file is corrupted propably.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Choose a filename to save under</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Cannot write file %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Clean the Palette?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>You will clean all characters from this palette. Are you sure?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Character Palette</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CharTable</name>
    <message>
        <source>Delete</source>
        <translation type="unfinished">Видалити</translation>
    </message>
</context>
<context>
    <name>CheckDocument</name>
    <message>
        <source>Glyphs missing</source>
        <translation>Відсутні знаки</translation>
    </message>
    <message>
        <source>Text overflow</source>
        <translation>Текст виходить за рамку</translation>
    </message>
    <message>
        <source>Object is not on a Page</source>
        <translation>Об&quot;єкт відсутній на сторінці</translation>
    </message>
    <message>
        <source>Missing Image</source>
        <translation>Відсутнє зображення</translation>
    </message>
    <message>
        <source>Image has a DPI-Value less than %1 DPI</source>
        <translation type="obsolete">Зображення має значення DPI менше ніж %1 DPI</translation>
    </message>
    <message>
        <source>Object has transparency</source>
        <translation>Об&quot;єкт містить прозорість</translation>
    </message>
    <message>
        <source>Object is a PDF Annotation or Field</source>
        <translation>Об&quot;єкт являється анотацією або полем PDF</translation>
    </message>
    <message>
        <source>Object is a placed PDF</source>
        <translation>Об&quot;єкт являються вміщеним PDF</translation>
    </message>
    <message>
        <source>Document</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>No Problems found</source>
        <translation>Проблем не знайдено</translation>
    </message>
    <message>
        <source>Page </source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Free Objects</source>
        <translation>Вільні об&quot;єкти</translation>
    </message>
    <message>
        <source>Problems found</source>
        <translation>Знайдено проблеми</translation>
    </message>
    <message>
        <source>Preflight Verifier</source>
        <translation>Передекспортна перевірка</translation>
    </message>
    <message>
        <source>Items</source>
        <translation>Об&quot;єкти</translation>
    </message>
    <message>
        <source>Problems</source>
        <translation>Проблеми</translation>
    </message>
    <message>
        <source>Current Profile:</source>
        <translation>Активний профіль:</translation>
    </message>
    <message>
        <source>&amp;Ignore Errors</source>
        <translation>&amp;Ігнорувати помилки</translation>
    </message>
    <message>
        <source>Check again</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Image resolution below %1 DPI, currently %2 x %3 DPI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Image resolution above %1 DPI, currently %2 x %3 DPI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Image is GIF</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>OK</source>
        <translation type="unfinished">Гаразд</translation>
    </message>
    <message>
        <source>Transparency used</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Blendmode used</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Layer &quot;%1&quot;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ChooseStyles</name>
    <message>
        <source>Choose Styles</source>
        <translation>Вибрати стилі</translation>
    </message>
    <message>
        <source>Available Styles</source>
        <translation>Доступні стилі</translation>
    </message>
</context>
<context>
    <name>CollectForOutput</name>
    <message>
        <source>Choose a Directory</source>
        <translation>Виберіть директорію</translation>
    </message>
    <message>
        <source>Collecting...</source>
        <translation>Збірка...</translation>
    </message>
    <message>
        <source>Warning</source>
        <translation type="obsolete">Застереження</translation>
    </message>
    <message>
        <source>Cannot collect all files for output for file:
%1</source>
        <translation>Неможливо зібрати всі файли для виводу для файла:
%1</translation>
    </message>
    <message>
        <source>Cannot collect the file: 
%1</source>
        <translation>Неможливо зібрати файл: 
%1</translation>
    </message>
</context>
<context>
    <name>ColorManager</name>
    <message>
        <source>Colors</source>
        <translation>Кольори</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>D&amp;uplicate</source>
        <translation>&amp;Дублювати</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Remove Unused</source>
        <translation>Видалити &amp;невикористані</translation>
    </message>
    <message>
        <source>Color Sets</source>
        <translation>Набори кольорів</translation>
    </message>
    <message>
        <source>Current Color Set:</source>
        <translation>Активний набір кольорів:</translation>
    </message>
    <message>
        <source>&amp;Save Color Set</source>
        <translation>Зберегти &amp;набір кольорів</translation>
    </message>
    <message>
        <source>Choose a color set to load</source>
        <translation>Вибрати набір кольорів для завантаження</translation>
    </message>
    <message>
        <source>Save the current color set</source>
        <translation>Записати активний набір кольорів</translation>
    </message>
    <message>
        <source>Remove unused colors from current document&apos;s color set</source>
        <translation>Видалити невикористані кольори з набору кольорів активного документа</translation>
    </message>
    <message>
        <source>Import colors to the current set from an existing document</source>
        <translation>Імпортувати кольори з існуючого документу в активний набір</translation>
    </message>
    <message>
        <source>Create a new color within the current set</source>
        <translation>Створити новий колір в активному наборі</translation>
    </message>
    <message>
        <source>Edit the currently selected color</source>
        <translation>Редагувати вибраний колір</translation>
    </message>
    <message>
        <source>Make a copy of the currently selected color</source>
        <translation>Зробити копію вибраного кольору</translation>
    </message>
    <message>
        <source>Delete the currently selected color</source>
        <translation>Видалити вибраний колір</translation>
    </message>
    <message>
        <source>Make the current colorset the default color set</source>
        <translation>Використовувати активний набір кольорів, як основний</translation>
    </message>
    <message>
        <source>&amp;Name:</source>
        <translation>&amp;Назва:</translation>
    </message>
    <message>
        <source>Choose a Name</source>
        <translation>Вибрати назву</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
        <translation type="obsolete">Документи (*.sla *.sla.gz *.scd *.scd.gz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;All Files (*)</source>
        <translation type="obsolete">Документи (*.sla *.scd);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Copy of %1</source>
        <translation>Копія %1</translation>
    </message>
    <message>
        <source>New Color</source>
        <translation>Новий колір</translation>
    </message>
    <message>
        <source>If color management is enabled, a triangle warning indicator is a warning the the color maybe outside of the color gamut of the current printer profile selected.What this means is the color may not print exactly as indicated on screen. Spot colors are indicated by a red circle. Registration colors will have a registration mark next to the color. More hints about gamut warnings are in the online help under Color Management.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;Other Files (*.eps *.epsi *.ps *.ai);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;Other Files (*.eps *.epsi *.ps *.ai);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Information</source>
        <translation type="unfinished">Інформація</translation>
    </message>
    <message>
        <source>The file %1 does not contain any new colors.
If the file was an EPS try to import it with File -&gt; Import</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ColorWheel</name>
    <message>
        <source>Monochromatic</source>
        <translation>Монохромний</translation>
    </message>
    <message>
        <source>Analogous</source>
        <translation>Аналоговий</translation>
    </message>
    <message>
        <source>Complementary</source>
        <translation>Комплементарний</translation>
    </message>
    <message>
        <source>Split Complementary</source>
        <translation>Роздільно комплементарний</translation>
    </message>
    <message>
        <source>Triadic</source>
        <translation>Тріадний</translation>
    </message>
    <message>
        <source>Tetradic (Double Complementary)</source>
        <translation>Тетраедрний (подвійно комплементарний)</translation>
    </message>
    <message>
        <source>Base Color</source>
        <translation>Основний колір</translation>
    </message>
    <message>
        <source>Monochromatic Light</source>
        <translation>Монохромне світле</translation>
    </message>
    <message>
        <source>Monochromatic Dark</source>
        <translation>Монохромне темне</translation>
    </message>
    <message>
        <source>1st. Analogous</source>
        <translation>Перше аналогове</translation>
    </message>
    <message>
        <source>2nd. Analogous</source>
        <translation>Друге аналогове</translation>
    </message>
    <message>
        <source>1st. Split</source>
        <translation>Перший розділ</translation>
    </message>
    <message>
        <source>2nd. Split</source>
        <translation>Другий розділ</translation>
    </message>
    <message>
        <source>3rd. Split</source>
        <translation>Третій розділ</translation>
    </message>
    <message>
        <source>4th. Split</source>
        <translation>Четвертий розділ</translation>
    </message>
    <message>
        <source>1st. Triadic</source>
        <translation>Перший тріадний</translation>
    </message>
    <message>
        <source>2nd. Triadic</source>
        <translation>Другий тріадний</translation>
    </message>
    <message>
        <source>1st. Tetradic (base opposite)</source>
        <translation>Перший тетраедрний (протилежно основі)</translation>
    </message>
    <message>
        <source>2nd. Tetradic (angle)</source>
        <translation>Другий тетраедрний (кут)</translation>
    </message>
    <message>
        <source>3rd. Tetradic (angle opposite)</source>
        <translation>Третій тетраедрний (протилежно куту)</translation>
    </message>
</context>
<context>
    <name>ColorWheelDialog</name>
    <message>
        <source>Color Wheel</source>
        <translation type="obsolete">Колесо кольорів</translation>
    </message>
    <message>
        <source>Color</source>
        <translation type="obsolete">Колір</translation>
    </message>
    <message>
        <source>Name</source>
        <translation type="obsolete">Ім&apos;я</translation>
    </message>
    <message>
        <source>C</source>
        <translation type="obsolete">С</translation>
    </message>
    <message>
        <source>M</source>
        <translation type="obsolete">M</translation>
    </message>
    <message>
        <source>Y</source>
        <translation type="obsolete">Y</translation>
    </message>
    <message>
        <source>K</source>
        <translation type="obsolete">K</translation>
    </message>
    <message>
        <source>Select Method:</source>
        <translation type="obsolete">Вибрати метод:</translation>
    </message>
    <message>
        <source>Angle (0 - 90 degrees):</source>
        <translation type="obsolete">Кут (0 - 90 градусів):</translation>
    </message>
    <message>
        <source>&amp;Merge Colors</source>
        <translation type="obsolete">&amp;Об&quot;єднати кольори</translation>
    </message>
    <message>
        <source>&amp;Replace Colors</source>
        <translation type="obsolete">&amp;Замінити кольори</translation>
    </message>
    <message>
        <source>Merge created colors into the document colors</source>
        <translation type="obsolete">Ввести створені кольори в кольори документу</translation>
    </message>
    <message>
        <source>Replace created colors in the document colors</source>
        <translation type="obsolete">Замінити кольори документу створеними кольорами</translation>
    </message>
    <message>
        <source>Leave colors untouched</source>
        <translation type="obsolete">Залишити кольори без змін</translation>
    </message>
    <message>
        <source>Merging colors</source>
        <translation type="obsolete">Поєднання кольорів</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation type="obsolete">Помилка:</translation>
    </message>
    <message>
        <source>Now opening the color manager.</source>
        <translation type="obsolete">Відкриття менеджера кольорів.</translation>
    </message>
    <message>
        <source>Color Merging</source>
        <translation type="obsolete">Об&quot;єднання кольорів</translation>
    </message>
    <message>
        <source>Cr&amp;eate color...</source>
        <translation type="obsolete">Ст&amp;ворити колір...</translation>
    </message>
    <message>
        <source>&amp;Import existing color...</source>
        <translation type="obsolete">&amp;Імпортувати існуючий колір...</translation>
    </message>
    <message>
        <source>&amp;Merge colors</source>
        <translation type="obsolete">&amp;Об&apos;єднати кольори</translation>
    </message>
    <message>
        <source>&amp;Replace colors</source>
        <translation type="obsolete">&amp;Замінити кольори</translation>
    </message>
    <message>
        <source>E&amp;xit</source>
        <translation type="obsolete">В&amp;ихід</translation>
    </message>
    <message>
        <source>C&amp;olor</source>
        <translation type="obsolete">&amp;Колір</translation>
    </message>
    <message>
        <source>Normal Vision</source>
        <translation type="obsolete">Нормальний зір</translation>
    </message>
    <message>
        <source>Full Color Blindness</source>
        <translation type="obsolete">Повний дальтонізм</translation>
    </message>
    <message>
        <source>Vision Defect:</source>
        <translation type="obsolete">Дефект зору:</translation>
    </message>
    <message>
        <source>Difference between the selected value and the counted ones. Refer to documentation for more information.</source>
        <translation type="obsolete">Різниця між вибраним значенням та вирахуваними. Зверніться до документації за додатковою інформацією.</translation>
    </message>
    <message>
        <source>Click the wheel to get the base color. It is hue in HSV mode.</source>
        <translation type="obsolete">Клацніть на колесі, щоб отримати основний колір. Це компонент відтінок в режимі ВНЗ.</translation>
    </message>
    <message>
        <source>Sample color scheme</source>
        <translation type="obsolete">Проста кольорова схема</translation>
    </message>
    <message>
        <source>Select one of the methods to create a color scheme. Refer to documentation for more information.</source>
        <translation type="obsolete">Виберіть один з методів для створення кольорової схеми. Зверніться до документації за додатковою інформацією.</translation>
    </message>
    <message>
        <source>Colors of your chosen color scheme</source>
        <translation type="obsolete">Кольори в вибраній Вами кольоровій схемі</translation>
    </message>
    <message>
        <source>Simulate common vision defects here. Select type of the defect.</source>
        <translation type="obsolete">Симуляція найбіль поширених недоліків зору. Виберіть тип недоліку.</translation>
    </message>
    <message>
        <source>Color %1 exists already!</source>
        <translation type="obsolete">Колір %1 вже існує!</translation>
    </message>
    <message>
        <source>Color %1 appended.</source>
        <translation type="obsolete">Колір %1 додано.</translation>
    </message>
    <message>
        <source>New Color</source>
        <translation type="obsolete">Новий колір</translation>
    </message>
    <message>
        <source>Unable to find the requested color. You have probably selected black, gray or white. There is no way to process this color.</source>
        <translation type="obsolete">Неможливо знайти зазначений колір. Ви, можливо, вибрали чорний, сірий, чи білий. Цей колір не може бути опрацьовано.</translation>
    </message>
    <message>
        <source>C&amp;olor Components...</source>
        <translation type="obsolete">Складові к&amp;ольору...</translation>
    </message>
    <message>
        <source>Protanopia (Red)</source>
        <translation type="obsolete">Протанопія (Червоний)</translation>
    </message>
    <message>
        <source>Deuteranopia (Green)</source>
        <translation type="obsolete">Дейтеранопія (Зелений)</translation>
    </message>
    <message>
        <source>Tritanopia (Blue)</source>
        <translation type="obsolete">Тританопія (Синій)</translation>
    </message>
</context>
<context>
    <name>ColorWheelPlugin</name>
    <message>
        <source>&amp;Color Wheel...</source>
        <translation>&amp;Колесо кольорів...</translation>
    </message>
    <message>
        <source>Color setting helper</source>
        <translation>Допомога для кольорових установок</translation>
    </message>
    <message>
        <source>Color selector with color theory included.</source>
        <translation>Вибір кольору з включеною теорією кольору.</translation>
    </message>
</context>
<context>
    <name>CommonStrings</name>
    <message>
        <source>&amp;Apply</source>
        <translation>&amp;Застосувати</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation>В&amp;ихід</translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation>&amp;Гаразд</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>Warning</source>
        <translation>Застереження</translation>
    </message>
    <message>
        <source>Single Page</source>
        <translation>Одна сторінка</translation>
    </message>
    <message>
        <source>Double Sided</source>
        <translation>Двохстороння</translation>
    </message>
    <message>
        <source>3-Fold</source>
        <translation>3-х сторіночна складка</translation>
    </message>
    <message>
        <source>4-Fold</source>
        <translation>4-х сторіночна складка</translation>
    </message>
    <message>
        <source>Left Page</source>
        <translation type="obsolete">Ліва сторінка</translation>
    </message>
    <message>
        <source>Middle</source>
        <translation type="obsolete">Середня</translation>
    </message>
    <message>
        <source>Middle Left</source>
        <translation type="obsolete">Середня ліва</translation>
    </message>
    <message>
        <source>Middle Right</source>
        <translation type="obsolete">Середня права</translation>
    </message>
    <message>
        <source>Right Page</source>
        <translation type="obsolete">Права сторінка</translation>
    </message>
    <message>
        <source>None</source>
        <comment>color name</comment>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>Custom</source>
        <comment>CommonStrings, custom page size</comment>
        <translation>Нестандартний</translation>
    </message>
    <message>
        <source>Monday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Tuesday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Wednesday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Thursday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Friday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Saturday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sunday</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>January</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>February</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>March</source>
        <translation type="unfinished">Березень</translation>
    </message>
    <message>
        <source>April</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>May</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>June</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>July</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>August</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>September</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>October</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>November</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>December</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="unfinished">Так</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="unfinished">Ні</translation>
    </message>
    <message>
        <source>&amp;Yes</source>
        <translation type="unfinished">&amp;Так</translation>
    </message>
    <message>
        <source>&amp;No</source>
        <translation type="unfinished">&amp;Ні</translation>
    </message>
    <message>
        <source>Left Page</source>
        <comment>Left page location</comment>
        <translation type="unfinished">Ліва сторінка</translation>
    </message>
    <message>
        <source>Middle</source>
        <comment>Middle page location</comment>
        <translation type="unfinished">Середня</translation>
    </message>
    <message>
        <source>Middle Left</source>
        <comment>Middle Left page location</comment>
        <translation type="unfinished">Середня ліва</translation>
    </message>
    <message>
        <source>Middle Right</source>
        <comment>Middle Right page location</comment>
        <translation type="unfinished">Середня права</translation>
    </message>
    <message>
        <source>Right Page</source>
        <comment>Right page location</comment>
        <translation type="unfinished">Права сторінка</translation>
    </message>
    <message>
        <source>Normal</source>
        <comment>Default single master page</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal Left</source>
        <comment>Default left master page</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal Middle</source>
        <comment>Default middle master page</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal Right</source>
        <comment>Default right master page</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal Vision</source>
        <comment>Color Blindness - Normal Vision</comment>
        <translation type="unfinished">Нормальний зір</translation>
    </message>
    <message>
        <source>Protanopia (Red)</source>
        <comment>Color Blindness - Red Color Blind</comment>
        <translation type="unfinished">Протанопія (Червоний)</translation>
    </message>
    <message>
        <source>Deuteranopia (Green)</source>
        <comment>Color Blindness - Greed Color Blind</comment>
        <translation type="unfinished">Дейтеранопія (Зелений)</translation>
    </message>
    <message>
        <source>Tritanopia (Blue)</source>
        <comment>Color Blindness - Blue Color Blind</comment>
        <translation type="unfinished">Тританопія (Синій)</translation>
    </message>
    <message>
        <source>Full Color Blindness</source>
        <comment>Color Blindness - Full Color Blindness</comment>
        <translation type="unfinished">Повний дальтонізм</translation>
    </message>
    <message>
        <source>Custom: </source>
        <comment>Custom Tab Fill Option</comment>
        <translation type="unfinished">Нестандартний: </translation>
    </message>
</context>
<context>
    <name>Cpalette</name>
    <message>
        <source>Normal</source>
        <translation>Звичайний</translation>
    </message>
    <message>
        <source>Horizontal Gradient</source>
        <translation>Горизонтальний градієнт</translation>
    </message>
    <message>
        <source>Vertical Gradient</source>
        <translation>Вертикальний градієнт</translation>
    </message>
    <message>
        <source>Diagonal Gradient</source>
        <translation>Діагональний градієнт</translation>
    </message>
    <message>
        <source>Cross Diagonal Gradient</source>
        <translation>Крос-діагональний градієнт</translation>
    </message>
    <message>
        <source>Radial Gradient</source>
        <translation>Радіальний градієнт</translation>
    </message>
    <message>
        <source>Opacity:</source>
        <translation>Непрозорість:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Shade:</source>
        <translation>Тінь:</translation>
    </message>
    <message>
        <source>Edit Line Color Properties</source>
        <translation>Редагувати установки кольору лінії</translation>
    </message>
    <message>
        <source>Edit Fill Color Properties</source>
        <translation>Редагувати установки кольору заливки</translation>
    </message>
    <message>
        <source>Saturation of color</source>
        <translation>Насиченість кольору</translation>
    </message>
    <message>
        <source>Normal or gradient fill method</source>
        <translation>Нормальний або градієнтний метод заливки</translation>
    </message>
    <message>
        <source>Set the transparency for the color selected</source>
        <translation>Зробити вибраний колір прозорим</translation>
    </message>
    <message>
        <source>Free linear Gradient</source>
        <translation>Вільний лінійний градієнт</translation>
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
        <translation> тчк</translation>
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
        <source>Free radial Gradient</source>
        <translation>Вільний радіальний градієнт</translation>
    </message>
    <message>
        <source>Move Vector</source>
        <translation>Перемістити вектор</translation>
    </message>
    <message>
        <source>Move the start of the gradient vector with the left mouse button pressed and move the end of the gradient vector with the right mouse button pressed</source>
        <translation>Перемістити початок вектора градієнта натиснувши ліву клавішу миші, або перемістити кінець вектора градієнта натиснувши праву клавішу миші</translation>
    </message>
    <message>
        <source>Transparency Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Blend Mode:</source>
        <translation type="unfinished">Режим змішування:</translation>
    </message>
    <message>
        <source>Darken</source>
        <translation type="unfinished">Затемнити</translation>
    </message>
    <message>
        <source>Lighten</source>
        <translation type="unfinished">Зробити світлішим</translation>
    </message>
    <message>
        <source>Multiply</source>
        <translation type="unfinished">Перемножити</translation>
    </message>
    <message>
        <source>Screen</source>
        <translation type="unfinished">Екран</translation>
    </message>
    <message>
        <source>Overlay</source>
        <translation type="unfinished">Перекрити</translation>
    </message>
    <message>
        <source>Hard Light</source>
        <translation type="unfinished">Різке світло</translation>
    </message>
    <message>
        <source>Soft Light</source>
        <translation type="unfinished">М&apos;яке світло</translation>
    </message>
    <message>
        <source>Difference</source>
        <translation type="unfinished">Різниця</translation>
    </message>
    <message>
        <source>Exlusion</source>
        <translation type="obsolete">Виключення</translation>
    </message>
    <message>
        <source>Color Dodge</source>
        <translation type="unfinished">Уникання кольору</translation>
    </message>
    <message>
        <source>Color Burn</source>
        <translation type="unfinished">Випалення кольором</translation>
    </message>
    <message>
        <source>Hue</source>
        <translation type="unfinished">Відтінок</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation type="unfinished">Насичення</translation>
    </message>
    <message>
        <source>Color</source>
        <translation type="unfinished">Колір</translation>
    </message>
    <message>
        <source>Luminosity</source>
        <translation type="unfinished">Яскравість</translation>
    </message>
    <message>
        <source>Offsets</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>X:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Y:</source>
        <translation type="unfinished">Y:</translation>
    </message>
    <message>
        <source>Scaling</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Rotation</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Angle</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Pattern</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Exclusion</source>
        <translation type="unfinished">Виключення</translation>
    </message>
    <message>
        <source>X-Scale:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Y-Scale:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CreateRangeBase</name>
    <message>
        <source>Create Range</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Number of Pages in Document:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Doc Page Range</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Basic Range Selection</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Add a Range of Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Consecutive Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>From:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>To:</source>
        <translation type="unfinished">До:</translation>
    </message>
    <message>
        <source>Comma Separated List</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Even Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Odd Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Add To Range</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Range of Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Move &amp;Up</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation type="unfinished">Alt+U</translation>
    </message>
    <message>
        <source>Move &amp;Down</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>De&amp;lete</source>
        <translation type="unfinished">&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Advanced Reordering</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Page Group Size:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sample Page Order:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Page Order</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished">&amp;Гаразд</translation>
    </message>
    <message>
        <source>Alt+O</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CsvDialog</name>
    <message>
        <source>CSV Importer Options</source>
        <translation>Установки імпорту csv</translation>
    </message>
    <message>
        <source>Field delimiter:</source>
        <translation>Розділювач полів:</translation>
    </message>
    <message>
        <source>(TAB)</source>
        <translation>(Таб)</translation>
    </message>
    <message>
        <source>Value delimiter:</source>
        <translation>Розділювач значень:</translation>
    </message>
    <message>
        <source>First row is a header</source>
        <translation>Перший ряд містить заголовки</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>None</source>
        <comment>delimiter</comment>
        <translation>Нічого</translation>
    </message>
</context>
<context>
    <name>CupsOptions</name>
    <message>
        <source>Printer Options</source>
        <translation>Установки принтера</translation>
    </message>
    <message>
        <source>Option</source>
        <translation>Опція</translation>
    </message>
    <message>
        <source>Value</source>
        <translation>Значення</translation>
    </message>
    <message>
        <source>Page Set</source>
        <translation>Набір сторінок</translation>
    </message>
    <message>
        <source>All Pages</source>
        <translation>Всі сторінки</translation>
    </message>
    <message>
        <source>Even Pages only</source>
        <translation>Лише парні сторінки</translation>
    </message>
    <message>
        <source>Odd Pages only</source>
        <translation>Лише непарні сторінки</translation>
    </message>
    <message>
        <source>Mirror</source>
        <translation>Дзеркальне зображення</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="obsolete">Ні</translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>Orientation</source>
        <translation>Орієнтація</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation>Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation>Горизонтальна</translation>
    </message>
    <message>
        <source>N-Up Printing</source>
        <translation>Х сторінок лицем догори</translation>
    </message>
    <message>
        <source>Page per Sheet</source>
        <translation>Сторінка на лист паперу</translation>
    </message>
    <message>
        <source>Pages per Sheet</source>
        <translation>Сторінок на лист паперу</translation>
    </message>
    <message>
        <source>This panel displays various CUPS options when printing. The exact parameters available will depend on your printer driver. You can confirm CUPS support by selecting Help &gt; About. Look for the listings: C-C-T These equate to C=CUPS C=littlecms T=TIFF support. Missing library support is indicated by a *</source>
        <translation>Ця панель показує установки CUPS під час друку. Доступність конкретних параметрів залежить
від використаного драйвера прінтера. Ви можете перевірити наявність підтримки CUPS вибравши Допомога &gt; Про. Зверніть увагу на послідовність: C-C-T Ці показники вказують на наявність підтримки C=CUPS C=littlecms T=TIFF. Відсутність підтримки певної бібліотеки вказується зірочкою (*)</translation>
    </message>
</context>
<context>
    <name>CurveWidget</name>
    <message>
        <source>Open</source>
        <translation type="unfinished">Відчинити</translation>
    </message>
    <message>
        <source>Curve Files (*.scu);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Save as</source>
        <translation type="unfinished">Записати як</translation>
    </message>
    <message>
        <source>Cannot write the file: 
%1</source>
        <translation type="unfinished">Неможливо записати файл: 
%1</translation>
    </message>
    <message>
        <source>Inverts the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Resets the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Switches between linear and cubic interpolation of the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Loads a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Saves this curve</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CustomFDialog</name>
    <message>
        <source>Encoding:</source>
        <translation>Кодування:</translation>
    </message>
    <message>
        <source>Moves to your Document Directory.
This can be set in the Preferences.</source>
        <translation>Переміщує Вас в вашу домашню директорію.
Її можна установити заздалегідь в Опціях.</translation>
    </message>
    <message>
        <source>&amp;Compress File</source>
        <translation>&amp;Стиснути файл</translation>
    </message>
    <message>
        <source>&amp;Include Fonts</source>
        <translation>Включити &amp;шрифти</translation>
    </message>
    <message>
        <source>&amp;Include ICC Profiles</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CwSetColor</name>
    <message>
        <source>Set Color Components</source>
        <translation type="obsolete">Складові набору кольорів</translation>
    </message>
    <message>
        <source>CMYK</source>
        <translation type="obsolete">CMYK</translation>
    </message>
    <message>
        <source>RGB</source>
        <translation type="obsolete">RGB</translation>
    </message>
    <message>
        <source>HSV</source>
        <translation type="obsolete">HSV</translation>
    </message>
    <message>
        <source>H:</source>
        <translation type="obsolete">H:</translation>
    </message>
    <message>
        <source>S:</source>
        <translation type="obsolete">S:</translation>
    </message>
    <message>
        <source>V:</source>
        <translation type="obsolete">V:</translation>
    </message>
    <message>
        <source>R:</source>
        <translation type="obsolete">R:</translation>
    </message>
    <message>
        <source>G:</source>
        <translation type="obsolete">G:</translation>
    </message>
    <message>
        <source>B:</source>
        <translation type="obsolete">B:</translation>
    </message>
    <message>
        <source>C:</source>
        <translation type="obsolete">C:</translation>
    </message>
    <message>
        <source>M:</source>
        <translation type="obsolete">M:</translation>
    </message>
    <message>
        <source>Y:</source>
        <translation type="obsolete">Y:</translation>
    </message>
    <message>
        <source>K:</source>
        <translation type="obsolete">K:</translation>
    </message>
    <message>
        <source>Set &amp;RGB</source>
        <translation type="obsolete">Набір &amp;RGB</translation>
    </message>
    <message>
        <source>Set C&amp;MYK</source>
        <translation type="obsolete">Набір C&amp;MYK</translation>
    </message>
    <message>
        <source>Set &amp;HSV</source>
        <translation type="obsolete">Набір &amp;HSV</translation>
    </message>
</context>
<context>
    <name>DeferredTask</name>
    <message>
        <source>Cancelled by user</source>
        <translation>Відмінено користувачем</translation>
    </message>
</context>
<context>
    <name>DelColor</name>
    <message>
        <source>Delete Color</source>
        <translation>Видалити колір</translation>
    </message>
    <message>
        <source>Delete Color:</source>
        <translation>Видалити колір:</translation>
    </message>
    <message>
        <source>Replace With:</source>
        <translation>Замінити на:</translation>
    </message>
</context>
<context>
    <name>DelPages</name>
    <message>
        <source>Delete Pages</source>
        <translation>Видалення сторінок</translation>
    </message>
    <message>
        <source>to:</source>
        <translation>до:</translation>
    </message>
    <message>
        <source>Delete From:</source>
        <translation>Видалити з:</translation>
    </message>
</context>
<context>
    <name>DelStyle</name>
    <message>
        <source>Delete Style</source>
        <translation>Видалити стиль</translation>
    </message>
    <message>
        <source>Delete Style:</source>
        <translation>Видалити стиль:</translation>
    </message>
    <message>
        <source>Replace With:</source>
        <translation>Замінити на:</translation>
    </message>
    <message>
        <source>No Style</source>
        <translation>Стиль відсутній</translation>
    </message>
</context>
<context>
    <name>DocIm</name>
    <message>
        <source>Importing failed</source>
        <translation>Імпорт не вдався</translation>
    </message>
    <message>
        <source>Importing Word document failed 
%1</source>
        <translation>Імпортувати документ Ворда %1 не вдалося</translation>
    </message>
</context>
<context>
    <name>DocInfos</name>
    <message>
        <source>Document Information</source>
        <translation>Інформація про документ</translation>
    </message>
    <message>
        <source>&amp;Title:</source>
        <translation>&amp;Заголовок:</translation>
    </message>
    <message>
        <source>&amp;Author:</source>
        <translation>&amp;Автор:</translation>
    </message>
    <message>
        <source>&amp;Keywords:</source>
        <translation>&amp;Ключові слова:</translation>
    </message>
    <message>
        <source>Descri&amp;ption:</source>
        <translation>&amp;Опис:</translation>
    </message>
    <message>
        <source>P&amp;ublisher:</source>
        <translation>&amp;Видавник:</translation>
    </message>
    <message>
        <source>&amp;Contributors:</source>
        <translation>&amp;Співробітники:</translation>
    </message>
    <message>
        <source>Dat&amp;e:</source>
        <translation>&amp;Дата:</translation>
    </message>
    <message>
        <source>T&amp;ype:</source>
        <translation>&amp;Тип:</translation>
    </message>
    <message>
        <source>F&amp;ormat:</source>
        <translation>&amp;Формат:</translation>
    </message>
    <message>
        <source>Identi&amp;fier:</source>
        <translation>В&amp;изначник:</translation>
    </message>
    <message>
        <source>&amp;Source:</source>
        <translation>Д&amp;жерело:</translation>
    </message>
    <message>
        <source>&amp;Language:</source>
        <translation>&amp;Мова:</translation>
    </message>
    <message>
        <source>&amp;Relation:</source>
        <translation>В&amp;ідношення:</translation>
    </message>
    <message>
        <source>Co&amp;verage:</source>
        <translation>&amp;Покриття:</translation>
    </message>
    <message>
        <source>Ri&amp;ghts:</source>
        <translation>П&amp;рава:</translation>
    </message>
    <message>
        <source>Further &amp;Information</source>
        <translation>Д&amp;одаткова інформація</translation>
    </message>
    <message>
        <source>A person or organisation responsible for making the document available</source>
        <translation>Людина чи організаця відповідальна за випуск документа в загальний доступ</translation>
    </message>
    <message>
        <source>A person or organisation responsible for making contributions to the content of the document</source>
        <translation>Людина чи організація відповідальна за вклад в зміст документа</translation>
    </message>
    <message>
        <source>A date associated with an event in the life cycle of the document, in YYYY-MM-DD format, as per ISO 8601</source>
        <translation>Дата зв&apos;язана з подією в життєвому  циклі документа в форматі РРРР-ММ-ДД, як вказано в ISO 8601</translation>
    </message>
    <message>
        <source>The nature or genre of the content of the document, eg. categories, functions, genres, etc</source>
        <translation>Жанр змісту документа - наприклад категорії, функції, жанри і так далі</translation>
    </message>
    <message>
        <source>An unambiguous reference to the document within a given context such as ISBN or URI</source>
        <translation>Безумовна ссилка на документ у даному контексті, такому як ISBN чи URI</translation>
    </message>
    <message>
        <source>A reference to a related document, possibly using a formal identifier such as a ISBN or URI</source>
        <translation>Ссилка на споріднений документ, можливо використовуючи ідентифікатор формату, такий як ISBN чи URI</translation>
    </message>
    <message>
        <source>The extent or scope of the content of the document, possibly including location, time and jurisdiction ranges</source>
        <translation>Масштаб чи протяжність документа, можливо включаючи розміщення, час та діапазони юрисдикції</translation>
    </message>
    <message>
        <source>Information about rights held in and over the document, eg. copyright, patent or trademark</source>
        <translation>Інформація про права на документ. Наприклад копірайт, патент, чи торгова марка</translation>
    </message>
    <message>
        <source>A reference to a document from which the present document is derived, eg. ISBN or URI</source>
        <translation>Ссилка на документ який послужив основою для данного документа, напр. ISBN чи URI</translation>
    </message>
    <message>
        <source>Documen&amp;t</source>
        <translation>Докумен&amp;т</translation>
    </message>
    <message>
        <source>The person or organisation primarily responsible for making the content of the document. This field can be embedded in the Scribus document for reference, as well as in the metadata of a PDF</source>
        <translation>Людина чи організація відповідальна за створення вмісту документа. Це поле може бути вбудоване в документ Scribus і в метадані PDF документа для довідки</translation>
    </message>
    <message>
        <source>A name given to the document. This field can be embedded in the Scribus document for reference, as well as in the metadata of a PDF</source>
        <translation>Ім&quot;я задане в документі. Це поле може бути вбудоване в документ Scribus і в метадані PDF документа для довідки</translation>
    </message>
    <message>
        <source>An account of the content of the document. This field is for a brief description or abstract of the document. It is embedded in the PDF on export</source>
        <translation>Зміст документа. Це поле призначене для короткого опису чи абстракта документа. Вбудовується в PDF документ при експортуванні</translation>
    </message>
    <message>
        <source>The topic of the content of the document. This field is for document keywords you wish to embed in a PDF, to assist searches and indexing of PDF files</source>
        <translation>Заголовок змісту документа. Це поле для ключових слів, які будуть вбудовані в PDF для полегшення пошуку та індексування PDF файлів</translation>
    </message>
    <message>
        <source>The physical or digital manifestation of the document. Media type and dimensions would be worth noting. RFC2045,RFC2046 for MIME types are also useful here</source>
        <translation>Фізичне чи цифрове представлення документа, такі як тип носія та його розмір. RFC2045 та RFC2046 для типів MIME також можуть бути корисними</translation>
    </message>
    <message>
        <source>The language in which the content of the document is written, usually a ISO-639 language code optionally suffixed with a hypen and an ISO-3166 country code, eg. en-GB, fr-CH</source>
        <translation>Мова на якій написано вміст документа. Звичайно це код ISO-639 з необов&quot;язковим суфіксом через тире - код країни по ISO-3166. Наприклад en-GB, fr-CH</translation>
    </message>
</context>
<context>
    <name>DocSections</name>
    <message>
        <source>Add a page numbering section to the document. The new section will be added after the currently selected section.</source>
        <translation>Додати розділ для нумерування сторінок до документа. Новий розділ буде додано за вибраним розділом.</translation>
    </message>
    <message>
        <source>Delete the currently selected section.</source>
        <translation>Видалити вибраний розділ.</translation>
    </message>
    <message>
        <source>1, 2, 3, ...</source>
        <translation>1, 2, 3, ...</translation>
    </message>
    <message>
        <source>i, ii, iii, ...</source>
        <translation>i, ii, iii, ...</translation>
    </message>
    <message>
        <source>I, II, III, ...</source>
        <translation>I, II, III, ...</translation>
    </message>
    <message>
        <source>a, b, c, ...</source>
        <translation>a, b, c, ...</translation>
    </message>
    <message>
        <source>A, B, C, ...</source>
        <translation>A, B, C, ...</translation>
    </message>
    <message>
        <source>Page Number Out Of Bounds</source>
        <translation>Число сторінок виходить за межі</translation>
    </message>
    <message>
        <source>The value you have entered is outside the range of page numbers in the current document (%1-%2).</source>
        <translation>Введене Вами значення виходить за діапазон номерів сторінок активного документа (%1-%2).</translation>
    </message>
    <message>
        <source>&lt;b&gt;Name:&lt;/b&gt; Optional name for section eg. Index&lt;br/&gt;&lt;b&gt;Shown:&lt;/b&gt; Select to show the page numbers in this section if there is one or more text frames setup to do so.&lt;br/&gt;&lt;b&gt;From:&lt;/b&gt; The page index for this section to start at.&lt;br/&gt;&lt;b&gt;To:&lt;/b&gt; The page index for this section to stop at.&lt;br/&gt;&lt;b&gt;Style:&lt;/b&gt; Select the page number style to be used.&lt;br/&gt;&lt;b&gt;Start:&lt;/b&gt; The index within the Style&apos;s range to star at. Eg. If Start=2 and Style=a,b,c, ..., the numbers will begin at b. For the first section in the document this replaces the older First Page Number in the new file window.</source>
        <translation>&lt;b&gt;Назва:&lt;/b&gt; Необов&apos;язкова назва розділу, напр. Індекс &lt;br/&gt;&lt;b&gt;Показ:&lt;/b&gt; Виберіть, щоб показати номери сторінок в цьому розділі, якщо необхідні для цього текстові рамки присутні. &lt;br/&gt;&lt;b&gt;Від:&lt;/b&gt; Початковий індекс для цього розділу.&lt;br/&gt;&lt;b&gt;До:&lt;/b&gt; Індекс кінця р&lt;br/&gt;&lt;b&gt;Стиль:&lt;/b&gt; Виберіть для використання стиль нумерації сторінок. &lt;br/&gt;&lt;b&gt;Старт:&lt;/b&gt; Початковий індекс в діапазоні стилю. Напр., якщо Старт=2 і Стиль=а,б,в..., то нумерація сторінок почнеться з б. Для першого розділу документа це заміщує старий номер першої сторінки у діалоговому вікні нового файла.</translation>
    </message>
</context>
<context>
    <name>DocSectionsBase</name>
    <message>
        <source>Document Sections</source>
        <translation>Розділи документа</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Назва</translation>
    </message>
    <message>
        <source>From</source>
        <translation>Від</translation>
    </message>
    <message>
        <source>To</source>
        <translation>До</translation>
    </message>
    <message>
        <source>Style</source>
        <translation>Стиль</translation>
    </message>
    <message>
        <source>Start</source>
        <translation>Початок</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation>&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>Shown</source>
        <translation>Показаний</translation>
    </message>
</context>
<context>
    <name>DocumentItemAttributes</name>
    <message>
        <source>Relates To</source>
        <translation>Відноситься до</translation>
    </message>
    <message>
        <source>Is Parent Of</source>
        <translation>Батько</translation>
    </message>
    <message>
        <source>Is Child Of</source>
        <translation>Дитина</translation>
    </message>
    <message>
        <source>Text Frames</source>
        <translation>Текстові рамки</translation>
    </message>
    <message>
        <source>Image Frames</source>
        <translation>Рамки для зображень</translation>
    </message>
    <message>
        <source>Boolean</source>
        <translation>Булеве</translation>
    </message>
    <message>
        <source>Integer</source>
        <translation>Ціле</translation>
    </message>
    <message>
        <source>String</source>
        <translation>Строкова величина</translation>
    </message>
    <message>
        <source>Real Number</source>
        <translation>Дійсне число</translation>
    </message>
    <message>
        <source>None</source>
        <comment>relationship</comment>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>None</source>
        <comment>auto add</comment>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>None</source>
        <comment>types</comment>
        <translation>Нічого</translation>
    </message>
</context>
<context>
    <name>DocumentItemAttributesBase</name>
    <message>
        <source>Document Item Attributes</source>
        <translation>Атрибути об&apos;єкта документа</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Назва</translation>
    </message>
    <message>
        <source>Type</source>
        <translation>Тип</translation>
    </message>
    <message>
        <source>Value</source>
        <translation>Значення</translation>
    </message>
    <message>
        <source>Parameter</source>
        <translation>Параметр</translation>
    </message>
    <message>
        <source>Relationship</source>
        <translation>Зв&apos;язок</translation>
    </message>
    <message>
        <source>Relationship To</source>
        <translation>Зв&apos;язок з</translation>
    </message>
    <message>
        <source>Auto Add To</source>
        <translation>Автоматично додати до</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation>&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation>Alt+L</translation>
    </message>
</context>
<context>
    <name>Druck</name>
    <message>
        <source>Setup Printer</source>
        <translation>Налаштування принтера</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Options</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>All</source>
        <translation>Всі кольори</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>Cyan</source>
        <translation>Салатовий</translation>
    </message>
    <message>
        <source>Magenta</source>
        <translation>Малиновий</translation>
    </message>
    <message>
        <source>Yellow</source>
        <translation>Жовтий</translation>
    </message>
    <message>
        <source>Black</source>
        <translation>Чорний</translation>
    </message>
    <message>
        <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
        <translation>Вмістити список елементів, розділений комами де елемент
може &quot;бути для всіх сторінок, 1-5 для діапазона сторінок, або
номер окремої сторінки.</translation>
    </message>
    <message>
        <source>Print Destination</source>
        <translation>Призначення для друку</translation>
    </message>
    <message>
        <source>&amp;Options...</source>
        <translation>&amp;Установки...</translation>
    </message>
    <message>
        <source>&amp;File:</source>
        <translation>&amp;Файл:</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation>З&amp;мінити...</translation>
    </message>
    <message>
        <source>A&amp;lternative Printer Command</source>
        <translation>&amp;Альтернативна команда для принтера</translation>
    </message>
    <message>
        <source>Co&amp;mmand:</source>
        <translation>&amp;Команда:</translation>
    </message>
    <message>
        <source>Range</source>
        <translation>Діапазон</translation>
    </message>
    <message>
        <source>Print &amp;All</source>
        <translation>Друкувати &amp;все</translation>
    </message>
    <message>
        <source>Print Current Pa&amp;ge</source>
        <translation>Друкувати активну &amp;сторінку</translation>
    </message>
    <message>
        <source>Print &amp;Range</source>
        <translation>Друкувати &amp;діапазон</translation>
    </message>
    <message>
        <source>N&amp;umber of Copies:</source>
        <translation>Число ко&amp;пій:</translation>
    </message>
    <message>
        <source>&amp;Print</source>
        <translation>&amp;Друк</translation>
    </message>
    <message>
        <source>Print Normal</source>
        <translation>Звичайний друк</translation>
    </message>
    <message>
        <source>Print Separations</source>
        <translation>Друкувати окремі кольори</translation>
    </message>
    <message>
        <source>Print in Color if Available</source>
        <translation>Друкувати в кольорі, якщо можливо</translation>
    </message>
    <message>
        <source>Print in Grayscale</source>
        <translation>Друкувати у відтінках сірого кольору</translation>
    </message>
    <message>
        <source>PostScript Level 1</source>
        <translation>Постскрипт 1-го рівня</translation>
    </message>
    <message>
        <source>PostScript Level 2</source>
        <translation>Постскрипт 2-го рівня</translation>
    </message>
    <message>
        <source>PostScript Level 3</source>
        <translation>Постскрипт 3-го рівня</translation>
    </message>
    <message>
        <source>Page</source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Mirror Page(s) Horizontal</source>
        <translation>Віддзеркалити сторінку(и) горизонтально</translation>
    </message>
    <message>
        <source>Mirror Page(s) Vertical</source>
        <translation>Віддзеркалити сторінку(и) вертикально</translation>
    </message>
    <message>
        <source>Set Media Size</source>
        <translation>Установити розмір паперу</translation>
    </message>
    <message>
        <source>Color</source>
        <translation>Колір</translation>
    </message>
    <message>
        <source>Apply Under Color Removal</source>
        <translation>Виконати видалення кольорів</translation>
    </message>
    <message>
        <source>Convert Spot Colors to Process Colors</source>
        <translation>Конвертувати точкові кольори в процесні кольори</translation>
    </message>
    <message>
        <source>Apply ICC Profiles</source>
        <translation>Застосувати ICC профілі</translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>Додаткові установки</translation>
    </message>
    <message>
        <source>Preview...</source>
        <translation>Попередній перегляд...</translation>
    </message>
    <message>
        <source>Sets the PostScript Level.
 Setting to Level 1 or 2 can create huge files</source>
        <translation>Установлює рівень Постскрипту.
 Вибір 1-го чи 2-го рівня може призвести
до створення дуже великих файлів</translation>
    </message>
    <message>
        <source>PostScript Files (*.ps);;All Files (*)</source>
        <translation>Постскрипт файли (*.ps);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Use an alternative print manager, such as kprinter or gtklp, to utilize additional printing options</source>
        <translation>Використовуйте альтернативний менеджер друку, такий як kprinter чи gtklp, щоб мати 
доступ до додаткових установок друку</translation>
    </message>
    <message>
        <source>A way of switching off some of the gray shades which are composed of cyan, yellow and magenta and using black instead. UCR most affects parts of images which are neutral and/or dark tones which are close to the gray. Use of this may improve printing some images and some experimentation and testing is need on a case by case basis.UCR reduces the possibility of over saturation with CMY inks.</source>
        <translation>Метод заміни деяких відтінків сірого, які насправді складаються з салатового, жовтого та фуксинового кольорів, на 
чорний колір. UCR найбільше впливає на частини зображень з нейтральними та або темними відтінками близькими до
сірого. Використання цього методу може покращити якість друку деяких зображень. У певних випадках потребується
експериментальний підбір варіантів. UCR знижує ймовірність перенасичення паперу СЖФ чорнилами.</translation>
    </message>
    <message>
        <source>Enables Spot Colors to be converted to composite colors. Unless you are planning to print spot colors at a commercial printer, this is probably best left enabled.</source>
        <translation>Дозволяє конвертування реєстрових кольорів в композитні. Якщо Ви не збираєтеся друкувати Ваш документ в
комерційній друкарні реєстровими кольорами, краще залиште цю установку ввімкненою.</translation>
    </message>
    <message>
        <source>Allows you to embed ICC profiles in the print stream when color management is enabled</source>
        <translation>Дозволяє вставку кольорових профілів в потік даних для друку при ввімкненому управлінні кольорами</translation>
    </message>
    <message>
        <source>This enables you to explicitely set the media size of the PostScript file. Not recommended unless requested by your printer.</source>
        <translation>Дозволяє явну установку розміру паперу для ПостСкрипт файла. Не рекомендується без запиту від професійного друкаря.</translation>
    </message>
    <message>
        <source>Failed to retrieve printer settings</source>
        <translation>Не вдалося отримати установки прінтера</translation>
    </message>
    <message>
        <source>Clip to Page Margins</source>
        <translation>Обрізати по полях сторінки</translation>
    </message>
    <message>
        <source>Do not show objects outside the margins on the printed page</source>
        <translation>Не показувати об&apos;єкти за полями на друкованій сторінці</translation>
    </message>
    <message>
        <source>Force Overprint Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enables global Overprint Mode for this document, overrides object settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Printer Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Crop Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Registration Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color Bars</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Offset:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bottom:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Left:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Right:</source>
        <translation type="unfinished">Праве:</translation>
    </message>
    <message>
        <source>Use Document Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Inside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Outside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distance for bleed from the top of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з верхньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the bottom of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з нижньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the left of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з лівої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the right of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з правої сторони фізичної сторінки</translation>
    </message>
</context>
<context>
    <name>EPSPlug</name>
    <message>
        <source>Importing File:
%1
failed!</source>
        <translation>Імпортувати файл:
%1
не вдалося!</translation>
    </message>
    <message>
        <source>Fatal Error</source>
        <translation>Фатальна помилка</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Помилка</translation>
    </message>
    <message>
        <source>Generating Items</source>
        <translation>Генерація об&apos;єктів</translation>
    </message>
    <message>
        <source>Importing PostScript</source>
        <translation type="obsolete">Імпортування постскрипту</translation>
    </message>
    <message>
        <source>Analyzing PostScript:</source>
        <translation>Аналіз постскрипту:</translation>
    </message>
    <message>
        <source>Converting of %1 images failed!</source>
        <translation>Конвертувати зображення %1 не вдалося!</translation>
    </message>
    <message>
        <source>Group%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Importing: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>EditStyle</name>
    <message>
        <source>Edit Style</source>
        <translation>Редагування стилю</translation>
    </message>
    <message>
        <source>Character</source>
        <translation>Символ</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source>Line Spacing</source>
        <translation>Інтервал між рядками</translation>
    </message>
    <message>
        <source>Name of your paragraph style</source>
        <translation>Назвіть Ваш стиль абзаца</translation>
    </message>
    <message>
        <source>Font of selected text or object</source>
        <translation>Шрифт вибраного тексту чи об&apos;єкту</translation>
    </message>
    <message>
        <source>Font Size</source>
        <translation>Розмір шрифта</translation>
    </message>
    <message>
        <source>Color of text fill</source>
        <translation>Колір заповнення знаків</translation>
    </message>
    <message>
        <source>Color of text stroke</source>
        <translation>Колір знакових силуетів</translation>
    </message>
    <message>
        <source>Determines the overall height, in line numbers, of the Drop Caps</source>
        <translation>Визначає загальну висоту буквиці числом рядків тексту</translation>
    </message>
    <message>
        <source>Spacing above the paragraph</source>
        <translation>Проміжок над абзацом</translation>
    </message>
    <message>
        <source>Spacing below the paragraph</source>
        <translation>Проміжок під абзацом</translation>
    </message>
    <message>
        <source>Tabulators and Indentation</source>
        <translation>Табулятори та відступи</translation>
    </message>
    <message>
        <source>&amp;Name:</source>
        <translation>&amp;Ім&apos;я:</translation>
    </message>
    <message>
        <source>&amp;Lines:</source>
        <translation>&amp;Лінії:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Distances</source>
        <translation>Відстані</translation>
    </message>
    <message>
        <source>Fixed Linespacing</source>
        <translation>Фіксований міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Automatic Linespacing</source>
        <translation>Автоматичний міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Align to Baseline Grid</source>
        <translation>Вирівняти по базовій сітці</translation>
    </message>
    <message>
        <source>Drop Caps</source>
        <translation>Буквиця</translation>
    </message>
    <message>
        <source>Distance from Text:</source>
        <translation>Відстань від тексту:</translation>
    </message>
    <message>
        <source>Preview of the Paragraph Style</source>
        <translation>Попередній перегляд стилю абзаца</translation>
    </message>
    <message>
        <source>Determines the gap between the DropCaps and the Text</source>
        <translation>Встановлює проміжок між буквицею та текстом</translation>
    </message>
    <message>
        <source>Toggles sample text of this paragraph style</source>
        <translation>Переключає зразковий текст для цього стилю абзаца</translation>
    </message>
    <message>
        <source>Name of the style is not unique</source>
        <translation>Назва стилю не являється неповторною</translation>
    </message>
    <message>
        <source>Background</source>
        <translation>Фон</translation>
    </message>
    <message>
        <source>Select for easier reading of light coloured text styles</source>
        <translation type="obsolete">Виберіть для зручнішого читання стилів тексту з світлими кольорами</translation>
    </message>
    <message>
        <source>Manual Tracking</source>
        <translation>Трекінг вручну</translation>
    </message>
    <message>
        <source>Offset to baseline of characters</source>
        <translation>Відступ від основи знаків</translation>
    </message>
    <message>
        <source>Click to select the line spacing mode</source>
        <translation>Кляцніть для вибору режиму установки міжрядкових проміжків</translation>
    </message>
    <message>
        <source>Select for easier reading of light colored text styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Auto</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Editor</name>
    <message>
        <source>Editor</source>
        <translation>Редактор</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Open...</source>
        <translation>&amp;Відчинити...</translation>
    </message>
    <message>
        <source>Save &amp;As...</source>
        <translation>Записати &amp;як...</translation>
    </message>
    <message>
        <source>&amp;Save and Exit</source>
        <translation>&amp;Записати і вийти</translation>
    </message>
    <message>
        <source>&amp;Exit without Saving</source>
        <translation>&amp;Вийти без запису</translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation>&amp;Відмінити</translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation>&amp;Повторити</translation>
    </message>
    <message>
        <source>Cu&amp;t</source>
        <translation>Ви&amp;різати</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>&amp;Get Field Names</source>
        <translation>&amp;Визначити назви полів</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагування</translation>
    </message>
    <message>
        <source>JavaScripts (*.js);;All Files (*)</source>
        <translation>Сценарії JavaScript (*.js);;Всі файли (*)</translation>
    </message>
</context>
<context>
    <name>EffectsDialog</name>
    <message>
        <source>Image Effects</source>
        <translation>Ефекти зображення</translation>
    </message>
    <message>
        <source>Options:</source>
        <translation>Установки:</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation>Колір:</translation>
    </message>
    <message>
        <source>Shade:</source>
        <translation>Тінь:</translation>
    </message>
    <message>
        <source>Brightness:</source>
        <translation>Яскравість:</translation>
    </message>
    <message>
        <source>Contrast:</source>
        <translation>Контраст:</translation>
    </message>
    <message>
        <source>Radius:</source>
        <translation>Радіус:</translation>
    </message>
    <message>
        <source>Value:</source>
        <translation>Значення:</translation>
    </message>
    <message>
        <source>Posterize:</source>
        <translation>Спростити набір кольорів:</translation>
    </message>
    <message>
        <source>Available Effects</source>
        <translation>Доступні ефекти</translation>
    </message>
    <message>
        <source>Blur</source>
        <translation>Розмивання</translation>
    </message>
    <message>
        <source>Brightness</source>
        <translation>Яскравість</translation>
    </message>
    <message>
        <source>Colorize</source>
        <translation>Замінити карту кольорів зображення</translation>
    </message>
    <message>
        <source>Contrast</source>
        <translation>Контраст</translation>
    </message>
    <message>
        <source>Grayscale</source>
        <translation>Конвертувати в тони сірого кольору</translation>
    </message>
    <message>
        <source>Invert</source>
        <translation>Негатив</translation>
    </message>
    <message>
        <source>Posterize</source>
        <translation>Спростити набір кольорів</translation>
    </message>
    <message>
        <source>Sharpen</source>
        <translation>Збільшити чіткість</translation>
    </message>
    <message>
        <source>&gt;&gt;</source>
        <translation>&gt;&gt;</translation>
    </message>
    <message>
        <source>&lt;&lt;</source>
        <translation>&lt;&lt;</translation>
    </message>
    <message>
        <source>Effects in use</source>
        <translation>Активні ефекти</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>Color 1:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color 2:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color 3:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color 4:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Duotone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Tritone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Quadtone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Curves</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ExportBitmap</name>
    <message>
        <source>File exists. Overwrite?</source>
        <translation type="unfinished">Файл вже існує. Переписати поверх?</translation>
    </message>
    <message>
        <source>exists already. Overwrite?</source>
        <translation type="unfinished">вже існує. Переписати поверх?</translation>
    </message>
    <message>
        <source>All</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ExportForm</name>
    <message>
        <source>Choose a Export Directory</source>
        <translation>Виберіть директорію для експортування</translation>
    </message>
    <message>
        <source>&amp;All pages</source>
        <translation>&amp;Всі сторінки</translation>
    </message>
    <message>
        <source>Change the output directory</source>
        <translation>Змінити вихідну директорію</translation>
    </message>
    <message>
        <source>The output directory - the place to store your images.
Name of the export file will be &apos;documentname-pagenumber.filetype&apos;</source>
        <translation>Вихідна директорія - місце в яке будуть записані Ваші
зображення. Назва експортованого файла буде у формі
&apos;імядокумента-номерсторінки.типфайла&apos;</translation>
    </message>
    <message>
        <source>Export only the current page</source>
        <translation>Експортувати лише активну сторінку</translation>
    </message>
    <message>
        <source>Available export formats</source>
        <translation>Доступні формати експортування</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation>З&amp;мінити...</translation>
    </message>
    <message>
        <source>&amp;Export to Directory:</source>
        <translation>&amp;Еспортувати в директорію:</translation>
    </message>
    <message>
        <source>Image &amp;Type:</source>
        <translation>Тип &amp;зображення:</translation>
    </message>
    <message>
        <source>&amp;Quality:</source>
        <translation>&amp;Якість:</translation>
    </message>
    <message>
        <source>Export as Image(s)</source>
        <translation>Експортувати, як зображення</translation>
    </message>
    <message>
        <source>Options</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>&amp;Resolution:</source>
        <translation>&amp;Розрішення:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source> dpi</source>
        <translation>тнд</translation>
    </message>
    <message>
        <source>Range</source>
        <translation>Діапазон</translation>
    </message>
    <message>
        <source>&amp;Current page</source>
        <translation>Активна &amp;сторінка</translation>
    </message>
    <message>
        <source>&amp;Range</source>
        <translation>&amp;Діапазон</translation>
    </message>
    <message>
        <source>C</source>
        <translation>С</translation>
    </message>
    <message>
        <source>Export a range of pages</source>
        <translation>Експортувати діапазон сторінок</translation>
    </message>
    <message>
        <source>Insert a comma separated list of tokens where
a token can be * for all the pages, 1-5 for
a range of pages or a single page number.</source>
        <translation>Вмістити список елементів, розділених комами, де елемент
може бути * для всіх сторінок, 1-5 для діапазона сторінок, або
номер окремої сторінки.</translation>
    </message>
    <message>
        <source>Export all pages</source>
        <translation>Експортувати всі сторінки</translation>
    </message>
    <message>
        <source>Resolution of the Images
Use 72 dpi for Images intended for the Screen</source>
        <translation>Розрішення зображень
Використовуйте 72 тнд для зображень, 
призначених для виводу на екран</translation>
    </message>
    <message>
        <source>The quality of your images - 100% is the best, 1% the lowest quality</source>
        <translation>Якість зображень - 100% - найвища, 1% - найнижча якість</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation>&amp;Розмір:</translation>
    </message>
    <message>
        <source>Size of the images. 100% for no changes, 200% for two times larger etc.</source>
        <translation>Розмір зображень. 100% - без зміни, 200% для подвійного збільшення, і.т.д.</translation>
    </message>
    <message>
        <source>Image size in Pixels</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ExtImageProps</name>
    <message>
        <source>Extended Image Properties</source>
        <translation>Додаткові властивості зображення</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation>Звичайний</translation>
    </message>
    <message>
        <source>Darken</source>
        <translation>Затемнити</translation>
    </message>
    <message>
        <source>Lighten</source>
        <translation>Зробити світлішим</translation>
    </message>
    <message>
        <source>Hue</source>
        <translation>Відтінок</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation>Насичення</translation>
    </message>
    <message>
        <source>Color</source>
        <translation>Колір</translation>
    </message>
    <message>
        <source>Luminosity</source>
        <translation>Яскравість</translation>
    </message>
    <message>
        <source>Multiply</source>
        <translation>Перемножити</translation>
    </message>
    <message>
        <source>Screen</source>
        <translation>Екран</translation>
    </message>
    <message>
        <source>Dissolve</source>
        <translation>Розбавити</translation>
    </message>
    <message>
        <source>Overlay</source>
        <translation>Перекрити</translation>
    </message>
    <message>
        <source>Hard Light</source>
        <translation>Різке світло</translation>
    </message>
    <message>
        <source>Soft Light</source>
        <translation>М&apos;яке світло</translation>
    </message>
    <message>
        <source>Difference</source>
        <translation>Різниця</translation>
    </message>
    <message>
        <source>Exclusion</source>
        <translation>Виключення</translation>
    </message>
    <message>
        <source>Color Dodge</source>
        <translation>Уникання кольору</translation>
    </message>
    <message>
        <source>Color Burn</source>
        <translation>Випалення кольором</translation>
    </message>
    <message>
        <source>Exlusion</source>
        <translation type="obsolete">Виключення</translation>
    </message>
    <message>
        <source>Blend Mode:</source>
        <translation>Режим змішування:</translation>
    </message>
    <message>
        <source>Opacity:</source>
        <translation>Непрозорість:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Background</source>
        <translation type="obsolete">Фон</translation>
    </message>
    <message>
        <source>Layers</source>
        <translation>Плани</translation>
    </message>
    <message>
        <source>Don&apos;t use any Path</source>
        <translation>Не використовуйте ніякий шлях</translation>
    </message>
    <message>
        <source>Paths</source>
        <translation>Шляхи</translation>
    </message>
</context>
<context>
    <name>FDialogPreview</name>
    <message>
        <source>Size:</source>
        <translation>Розмір:</translation>
    </message>
    <message>
        <source>Title:</source>
        <translation>Заголовок:</translation>
    </message>
    <message>
        <source>No Title</source>
        <translation>Немає заголовка</translation>
    </message>
    <message>
        <source>Author:</source>
        <translation>Автор:</translation>
    </message>
    <message>
        <source>Unknown</source>
        <translation>Невідомий</translation>
    </message>
    <message>
        <source>Scribus Document</source>
        <translation>Документ Scribus</translation>
    </message>
    <message>
        <source>Resolution:</source>
        <translation>Розрішення:</translation>
    </message>
    <message>
        <source>DPI</source>
        <translation>DPI</translation>
    </message>
    <message>
        <source>RGB</source>
        <translation>RGB</translation>
    </message>
    <message>
        <source>CMYK</source>
        <translation>CMYK</translation>
    </message>
    <message>
        <source>Grayscale</source>
        <translation>Відтінки сірого</translation>
    </message>
    <message>
        <source>Colorspace:</source>
        <translation>Кольоровий простір:</translation>
    </message>
    <message>
        <source>Duotone</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>FileLoader</name>
    <message>
        <source>Some fonts used by this document have been substituted:</source>
        <translation>Деякі шрифти, використані в цьому документі, були підмінені:</translation>
    </message>
    <message>
        <source> was replaced by: </source>
        <translation>був підмінений на:</translation>
    </message>
</context>
<context>
    <name>FontPrefs</name>
    <message>
        <source>Available Fonts</source>
        <translation>Доступні шрифти</translation>
    </message>
    <message>
        <source>Font Substitutions</source>
        <translation>Підміна шрифтів</translation>
    </message>
    <message>
        <source>Additional Paths</source>
        <translation>Додаткові шляхи</translation>
    </message>
    <message>
        <source>Font Name</source>
        <translation>Ім&apos;я шрифта</translation>
    </message>
    <message>
        <source>Replacement</source>
        <translation>Підміна</translation>
    </message>
    <message>
        <source>Choose a Directory</source>
        <translation>Вибрати директорію</translation>
    </message>
    <message>
        <source>&amp;Available Fonts</source>
        <translation>&amp;Доступні шрифти</translation>
    </message>
    <message>
        <source>Font &amp;Substitutions</source>
        <translation>&amp;Підміна шрифтів</translation>
    </message>
    <message>
        <source>Additional &amp;Paths</source>
        <translation>Д&amp;одаткові шляхи до шрифтів</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation>З&amp;мінити...</translation>
    </message>
    <message>
        <source>A&amp;dd...</source>
        <translation>&amp;Додати...</translation>
    </message>
    <message>
        <source>&amp;Remove</source>
        <translation>Ви&amp;далити</translation>
    </message>
    <message>
        <source>Font Name</source>
        <comment>font preview</comment>
        <translation>Ім&apos;я шрифта</translation>
    </message>
    <message>
        <source>Use Font</source>
        <comment>font preview</comment>
        <translation>Використовувати шрифт</translation>
    </message>
    <message>
        <source>Embed in:</source>
        <comment>font preview</comment>
        <translation type="obsolete">Вбудувати в:</translation>
    </message>
    <message>
        <source>Subset</source>
        <comment>font preview</comment>
        <translation>Вибірка</translation>
    </message>
    <message>
        <source>Path to Font File</source>
        <comment>font preview</comment>
        <translation>Шлях до файла шрифта</translation>
    </message>
    <message>
        <source>PostScript</source>
        <translation type="obsolete">Постскрипт</translation>
    </message>
    <message>
        <source>Font search paths can only be set in Preferences, and only when there is no document currently open. Close any open documents, then use Edit-&gt;Settings to change the font search path.</source>
        <translation type="obsolete">Шляхи пошуку шрифтів лише можуть бути установлені в Установках і тільки при відсутності відчиненого документа.
Зачиніть усі відчинені документи і зайдіть в Редагувати&gt;Установки, щоб змінити шлях пошуку шрифтів.</translation>
    </message>
    <message>
        <source>Embed in PostScript</source>
        <comment>font preview</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Font search paths can only be set in File &gt; Preferences, and only when there is no document currently open. Close any open documents, then use File &gt; Preferences &gt; Fonts to change the font search path.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>FontPreview</name>
    <message>
        <source>Append selected font into Style, Font menu</source>
        <comment>font preview</comment>
        <translation>Додати вибраний шрифт в меню Стиль, Шрифт</translation>
    </message>
    <message>
        <source>Leave preview</source>
        <comment>font preview</comment>
        <translation>Вихід з попереднього перегляду</translation>
    </message>
    <message>
        <source>Start searching</source>
        <translation>Почати пошук</translation>
    </message>
    <message>
        <source>Size of the selected font</source>
        <translation>Розмір вибраного шрифта</translation>
    </message>
    <message>
        <source>Woven silk pyjamas exchanged for blue quartz</source>
        <comment>font preview</comment>
        <translation>Реве та стогне Дніпр широкий, сердитий вітер завива</translation>
    </message>
    <message>
        <source>User</source>
        <comment>font preview</comment>
        <translation>Користувач</translation>
    </message>
    <message>
        <source>System</source>
        <comment>font preview</comment>
        <translation>Система</translation>
    </message>
    <message>
        <source>Sample will be shown after key release</source>
        <translation>Зразок буде показано після відпускання клавіші</translation>
    </message>
    <message>
        <source>Typing the text here provides quick searching in the font names. Searching is case insensitive. You can provide a common wild cards (*, ?, [...]) in your phrase. Examples: t* will list all fonts starting with t or T. *bold* will list all fonts with word bold, bolder etc. in the name.</source>
        <translation>Друкування тексту тут дозволяє проводити швидкий пошук імен шрифтів. Пошук залежить від реєстру літер. Ви можете задавати розповсюджені шаблони (*, ?, [...]) у фразі для пошуку. Наприклад т* покаже всі шрифти, назви яких починаються з т чи Т. *жирн* покаже всі шрифти з жирний чи жирніший і т.п. в назві.</translation>
    </message>
</context>
<context>
    <name>FontPreviewBase</name>
    <message>
        <source>Fonts Preview</source>
        <translation>Попередній перегляд шрифтів</translation>
    </message>
    <message>
        <source>&amp;Quick Search:</source>
        <translation>&amp;Швидкий пошук:</translation>
    </message>
    <message>
        <source>&amp;Search</source>
        <translation>&amp;Пошук</translation>
    </message>
    <message>
        <source>Alt+S</source>
        <translation>Alt+S</translation>
    </message>
    <message>
        <source>Font Name</source>
        <translation>Назва шрифта</translation>
    </message>
    <message>
        <source>Doc</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>Type</source>
        <translation>Тип</translation>
    </message>
    <message>
        <source>Subset</source>
        <translation>Вибірка</translation>
    </message>
    <message>
        <source>Access</source>
        <translation>Доступ</translation>
    </message>
    <message>
        <source>&amp;Font Size:</source>
        <translation>&amp;Розмір шрифта:</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Текст</translation>
    </message>
    <message>
        <source>Sample text to display</source>
        <translation>Зразок тексту для показу</translation>
    </message>
    <message>
        <source>Se&amp;t</source>
        <translation>На&amp;бір</translation>
    </message>
    <message>
        <source>Alt+T</source>
        <translation>Alt+T</translation>
    </message>
    <message>
        <source>Reset the text</source>
        <translation>Перезавантажити текст</translation>
    </message>
    <message>
        <source>&amp;Append</source>
        <translation>&amp;Добавити</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
</context>
<context>
    <name>FontPreviewPlugin</name>
    <message>
        <source>&amp;Font Preview...</source>
        <translation>&amp;Попередній перегляд шрифта...</translation>
    </message>
    <message>
        <source>Font Preview dialog</source>
        <translation>Діалогове вікно для попереднього перегляду шрифта</translation>
    </message>
    <message>
        <source>Sorting, searching and browsing available fonts.</source>
        <translation>Сортування, пошук, та перегляд доступних шрифтів.</translation>
    </message>
</context>
<context>
    <name>FontReplaceDialog</name>
    <message>
        <source>Font Substitution</source>
        <translation>Підміна шрифта</translation>
    </message>
    <message>
        <source>Original Font</source>
        <translation>Оригінальний шрифт</translation>
    </message>
    <message>
        <source>Substitution Font</source>
        <translation>Новий шрифт</translation>
    </message>
    <message>
        <source>Make these substitutions permanent</source>
        <translation>Зробити ці заміни постійними</translation>
    </message>
    <message>
        <source>This document contains some fonts that are not installed on your system, please choose a suitable replacement for them. Cancel will stop the document from loading.</source>
        <translation>У цьому документі присутні шрифти, які не встановлені на Вашій системі. Будь-ласка виберіть
для них заміну. Відміна процесу приведе до відміни завантаження документа.</translation>
    </message>
    <message>
        <source>Cancels these font substitutions and stops loading the document.</source>
        <translation>Відмінює заміни шрифтів та завантаження документа.</translation>
    </message>
    <message>
        <source>Enabling this tells Scribus to use these replacements for missing fonts permanently in all future layouts. This can be reverted or changed in Edit &gt; Preferences &gt; Fonts.</source>
        <translation>Ввімкнення цієї установки змусить Scribus використовувати ці заміни відсутніх шрифтів в майбутньому. Цей результат може бути відмінено чи змінено в Редагувати&gt;Установки&gt;Шрифти.</translation>
    </message>
    <message>
        <source>If you select OK, then save, these substitutions are made permanent in the document.</source>
        <translation>Якщо Ви виберете Гаразд і запишете документ, то ці заміни будуть у ньому зафіксовані.</translation>
    </message>
</context>
<context>
    <name>GradientEditor</name>
    <message>
        <source>Position:</source>
        <translation>Позиція:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Add, change or remove color stops here</source>
        <translation>Додати, змінити, чи видалити кольорові зупинки тут</translation>
    </message>
</context>
<context>
    <name>GuideManager</name>
    <message>
        <source>Manage Guides</source>
        <translation type="obsolete">Керування направляючими</translation>
    </message>
    <message>
        <source>Horizontal Guides</source>
        <translation type="obsolete">Горизонтальні направляючі</translation>
    </message>
    <message>
        <source>Vertical Guides</source>
        <translation type="obsolete">Вертикальні направляючі</translation>
    </message>
    <message>
        <source>&amp;Y-Pos:</source>
        <translation type="obsolete">Поз. &amp;У:</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation type="obsolete">&amp;Додати</translation>
    </message>
    <message>
        <source>D&amp;elete</source>
        <translation type="obsolete">&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;X-Pos:</source>
        <translation type="obsolete">Поз. &amp;Х:</translation>
    </message>
    <message>
        <source>A&amp;dd</source>
        <translation type="obsolete">&amp;Додати</translation>
    </message>
    <message>
        <source>De&amp;lete</source>
        <translation type="obsolete">&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Lock Guides</source>
        <translation type="obsolete">&amp;Замкнути направляючі</translation>
    </message>
    <message>
        <source>Rows and Columns - Automatic Guides</source>
        <translation type="obsolete">Рядки і колонки - автоматичні направляючі</translation>
    </message>
    <message>
        <source>&amp;Rows:</source>
        <translation type="obsolete">&amp;Рядки:</translation>
    </message>
    <message>
        <source>C&amp;olumns:</source>
        <translation type="obsolete">К&amp;олонки:</translation>
    </message>
    <message>
        <source>Row &amp;Gap</source>
        <translation type="obsolete">Міжрядковий &amp;Проміжок</translation>
    </message>
    <message>
        <source>Colum&amp;n Gap</source>
        <translation type="obsolete">Міжколонковий П&amp;роміжок</translation>
    </message>
    <message>
        <source>Refer to:</source>
        <translation type="obsolete">Зверніться до:</translation>
    </message>
    <message>
        <source>&amp;Page</source>
        <translation type="obsolete">С&amp;торінка</translation>
    </message>
    <message>
        <source>&amp;Margins</source>
        <translation type="obsolete">По&amp;ля</translation>
    </message>
    <message>
        <source>&amp;Selection</source>
        <translation type="obsolete">&amp;Вибірка</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation type="obsolete">&amp;Зачинити</translation>
    </message>
    <message>
        <source>&amp;Update</source>
        <translation type="obsolete">&amp;Поновити</translation>
    </message>
    <message>
        <source>Set the guides in document. Guide manager is still opened but the changes are persistant</source>
        <comment>guide manager</comment>
        <translation type="obsolete">Установити направляючі в документі. Менеджер направляючих залишиться відчиненим, але зміни стануть постійними</translation>
    </message>
    <message>
        <source>&amp;Apply to All Pages</source>
        <translation type="obsolete">&amp;Застосувати до всіх сторінок</translation>
    </message>
    <message>
        <source>Guide</source>
        <translation type="obsolete">Направляюча</translation>
    </message>
    <message>
        <source>Unit</source>
        <translation type="obsolete">Одиниця виміру</translation>
    </message>
    <message>
        <source>Preview</source>
        <translation type="obsolete">Попередній перегляд</translation>
    </message>
    <message>
        <source>There is empty (0.0) guide already</source>
        <translation type="obsolete">Пуста направляюча (0.0) вже існує</translation>
    </message>
    <message>
        <source>Edit Guide</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enter a position:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>New Guide</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>GuideManagerBase</name>
    <message>
        <source>Manage Guides</source>
        <translation type="unfinished">Керування направляючими</translation>
    </message>
    <message>
        <source>Horizontals</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Guide</source>
        <translation type="unfinished">Направляюча</translation>
    </message>
    <message>
        <source>Unit</source>
        <translation type="obsolete">Одиниця виміру</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation type="unfinished">&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>D&amp;elete</source>
        <translation type="unfinished">&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+E</source>
        <translation type="unfinished">Alt+E</translation>
    </message>
    <message>
        <source>Verticals</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>A&amp;dd</source>
        <translation type="unfinished">&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>De&amp;lete</source>
        <translation type="unfinished">&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Lock Guides</source>
        <translation type="unfinished">&amp;Замкнути направляючі</translation>
    </message>
    <message>
        <source>Appl&amp;y to All Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+Y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Number:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>U&amp;se Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+S</source>
        <translation type="unfinished">Alt+S</translation>
    </message>
    <message>
        <source>Nu&amp;mber:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Use &amp;Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+G</source>
        <translation type="unfinished">Alt+G</translation>
    </message>
    <message>
        <source>Refer To</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Page</source>
        <translation type="unfinished">С&amp;торінка</translation>
    </message>
    <message>
        <source>Alt+P</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>M&amp;argins</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>S&amp;election</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Misc</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete all guides from the current page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete all guides from the current document</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Single</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Column/Row</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete Guides from Current &amp;Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete Guides from &amp;All Pages</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>HelpBrowser</name>
    <message>
        <source>Sorry, no manual available! Please see: http://docs.scribus.net for updated docs
and www.scribus.net for downloads.</source>
        <translation>Вибачте - довідка відсутня! Будь-ласка зверніться на http://docs.scribus.net за поновленою документацією та yf ww.scribus.net для зкачування.</translation>
    </message>
    <message>
        <source>Contents</source>
        <translation>Зміст</translation>
    </message>
    <message>
        <source>Link</source>
        <translation>Ссилка</translation>
    </message>
    <message>
        <source>Scribus Online Help</source>
        <translation>Допомога по Scribus на вебі</translation>
    </message>
    <message>
        <source>&amp;Contents</source>
        <translation>&amp;Зміст</translation>
    </message>
    <message>
        <source>&amp;Search</source>
        <translation>&amp;Пошук</translation>
    </message>
    <message>
        <source>Find</source>
        <translation>Шукати</translation>
    </message>
    <message>
        <source>Search Term:</source>
        <translation>Термін для пошуку:</translation>
    </message>
    <message>
        <source>Se&amp;arch</source>
        <translation>По&amp;шук</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>De&amp;lete All</source>
        <translation>Вид&amp;алити Все</translation>
    </message>
    <message>
        <source>Book&amp;marks</source>
        <translation>Заклад&amp;ки</translation>
    </message>
    <message>
        <source>&amp;Print...</source>
        <translation>&amp;Друк...</translation>
    </message>
    <message>
        <source>E&amp;xit</source>
        <translation>В&amp;ихід</translation>
    </message>
    <message>
        <source>Searching is case unsensitive</source>
        <translation>Пошук не залежить від реєстру</translation>
    </message>
    <message>
        <source>New Bookmark</source>
        <translation>Нова закладка</translation>
    </message>
    <message>
        <source>New Bookmark&apos;s Title:</source>
        <translation>Назва нової закладки:</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <source>&amp;Find...</source>
        <translation>&amp;Пошук...</translation>
    </message>
    <message>
        <source>Find &amp;Next</source>
        <translation>Знайти &amp;наступний</translation>
    </message>
    <message>
        <source>Find &amp;Previous</source>
        <translation>Знайти &amp;попередній</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>&amp;Add Bookmark</source>
        <translation>&amp;Добавити закладку</translation>
    </message>
    <message>
        <source>D&amp;elete All</source>
        <translation>Вид&amp;алити Все</translation>
    </message>
    <message>
        <source>&amp;Bookmarks</source>
        <translation>&amp;Закладки</translation>
    </message>
    <message>
        <source>Relevance</source>
        <translation>Відношення</translation>
    </message>
</context>
<context>
    <name>HyAsk</name>
    <message>
        <source>Possible Hyphenation</source>
        <translation>Можливий перенос</translation>
    </message>
    <message>
        <source>Accept</source>
        <translation>Застосувати</translation>
    </message>
    <message>
        <source>Skip</source>
        <translation>Пропустити</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
</context>
<context>
    <name>HySettings</name>
    <message>
        <source>Length of the smallest word to be hyphenated.</source>
        <translation>Довжина найкоротшого слова, яке буде розділене для переносу.</translation>
    </message>
    <message>
        <source>Maximum number of Hyphenations following each other.
A value of 0 means unlimited hyphenations.</source>
        <translation>Максимальне число послідовних переносів.
Нульове значення встановлює необмежену кількість
переносів.</translation>
    </message>
    <message>
        <source>&amp;Language:</source>
        <translation>&amp;Мова:</translation>
    </message>
    <message>
        <source>&amp;Smallest Word:</source>
        <translation>&amp;Найменше слово:</translation>
    </message>
    <message>
        <source>&amp;Hyphenation Suggestions</source>
        <translation>&amp;Пропозиції по переносу</translation>
    </message>
    <message>
        <source>Hyphenate Text Automatically &amp;During Typing</source>
        <translation>Переносити текст автоматично під &amp;час друкування</translation>
    </message>
    <message>
        <source>A dialog box showing all possible hyphens for each word will show up when you use the Extras, Hyphenate Text option.</source>
        <translation>Діалогове вікно, яке показує всі можливі переноси для кожного слова, буде показане якщо Ви виберете установку &quot;Додаткове, Переносити текст&quot;.</translation>
    </message>
    <message>
        <source>Enables automatic hyphenation of your text while typing.</source>
        <translation>Ввімкнути автоматичний переніс тексту під час друкування.</translation>
    </message>
    <message>
        <source>Consecutive Hyphenations &amp;Allowed:</source>
        <translation>&amp;Дозволити послідовні переноси:</translation>
    </message>
</context>
<context>
    <name>ImageInfoDialog</name>
    <message>
        <source>Image Info</source>
        <translation>Інформація по зображенню</translation>
    </message>
    <message>
        <source>General Info</source>
        <translation>Загальна інформація</translation>
    </message>
    <message>
        <source>Date / Time:</source>
        <translation>Дата / Час:</translation>
    </message>
    <message>
        <source>Has Embedded Profile:</source>
        <translation>Містить вбудований профіль:</translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="obsolete">Ні</translation>
    </message>
    <message>
        <source>Profile Name:</source>
        <translation>Назва профілю:</translation>
    </message>
    <message>
        <source>Has Embedded Paths:</source>
        <translation>Містить вбудовані шляхи:</translation>
    </message>
    <message>
        <source>Has Layers:</source>
        <translation>Містить плани:</translation>
    </message>
    <message>
        <source>EXIF Info</source>
        <translation>EXIF інформація</translation>
    </message>
    <message>
        <source>Artist:</source>
        <translation>Митець:</translation>
    </message>
    <message>
        <source>Comment:</source>
        <translation>Коментарій:</translation>
    </message>
    <message>
        <source>User Comment:</source>
        <translation>Коментарій користувача:</translation>
    </message>
    <message>
        <source>Camera Model:</source>
        <translation>Модель фотоапарата:</translation>
    </message>
    <message>
        <source>Camera Manufacturer:</source>
        <translation>Виробник фотоапарата:</translation>
    </message>
    <message>
        <source>Description:</source>
        <translation>Опис:</translation>
    </message>
    <message>
        <source>Copyright:</source>
        <translation>Авторські права:</translation>
    </message>
    <message>
        <source>Scanner Model:</source>
        <translation>Модель сканера:</translation>
    </message>
    <message>
        <source>Scanner Manufacturer:</source>
        <translation>Виробник сканера:</translation>
    </message>
    <message>
        <source>Exposure time</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Aperture:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>ISO equiv.:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ImportPSPlugin</name>
    <message>
        <source>Import &amp;EPS/PS...</source>
        <translation>Імпорт &amp;ЕPS/PS...</translation>
    </message>
    <message>
        <source>Imports EPS Files</source>
        <translation>Імпорт ЕPS файлів</translation>
    </message>
    <message>
        <source>Imports most EPS files into the current document,
converting their vector data into Scribus objects.</source>
        <translation>Імпортує більшість EPS файлів в активний документ,
конвертуючи їхні векторні дані в об&apos;єкти Scribus.</translation>
    </message>
    <message>
        <source>PostScript</source>
        <translation>Постскрипт</translation>
    </message>
    <message>
        <source>PDF</source>
        <translation>PDF</translation>
    </message>
</context>
<context>
    <name>InsPage</name>
    <message>
        <source>Insert Page</source>
        <translation>Вставити сторінку</translation>
    </message>
    <message>
        <source>before Page</source>
        <translation>перед цією сторінкою</translation>
    </message>
    <message>
        <source>after Page</source>
        <translation>після цієї сторінки</translation>
    </message>
    <message>
        <source>at End</source>
        <translation>в кінці документа</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайний</translation>
    </message>
    <message>
        <source>Page(s)</source>
        <translation>Сторінка(и)</translation>
    </message>
    <message>
        <source>&amp;Insert</source>
        <translation>&amp;Вставити</translation>
    </message>
    <message>
        <source>&amp;Master Page:</source>
        <translation>&amp;Головна сторінка:</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation>Розмір сторінки</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation>&amp;Розмір:</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation>&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation>Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation>Горизонтальна</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation>&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation>&amp;Висота:</translation>
    </message>
    <message>
        <source>Move Objects with their Page</source>
        <translation>Пересувати об&apos;єкти разом з їх сторінкою</translation>
    </message>
    <message>
        <source>Master Pages</source>
        <translation>Головні сторінки</translation>
    </message>
</context>
<context>
    <name>InsertAFrame</name>
    <message>
        <source>Open</source>
        <translation type="unfinished">Відчинити</translation>
    </message>
    <message>
        <source>&lt;b&gt;Insert a text frame&lt;/b&gt;&lt;br/&gt;A text frame allows you to enter any text in a defined position with the formatting you choose. You may select a text file on the Options tab if you want to immediately import a document into the frame. Scribus supports a wide variety of importable format from plain text to OpenOffice.org.&lt;br/&gt;Your text may be edited and formatted on the page directly or in the simple Story Editor.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;b&gt;Insert an image frame&lt;/b&gt;&lt;br/&gt;An image frame allows you to place an image onto your page. Various image effects may be applied or combined including transparencies, brightness, posterisation that allow retouching or the creation of interesting visual results. Image scaling and shaping is performed with the Properties Palette.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>InsertAFrameBase</name>
    <message>
        <source>Insert A Frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>T&amp;ype</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Text Frame</source>
        <translation type="unfinished">&amp;Текстова рамка</translation>
    </message>
    <message>
        <source>Alt+T</source>
        <translation type="unfinished">Alt+T</translation>
    </message>
    <message>
        <source>&amp;Image Frame</source>
        <translation type="unfinished">Рамка &amp;зображення</translation>
    </message>
    <message>
        <source>Alt+I</source>
        <translation type="unfinished">Alt+I</translation>
    </message>
    <message>
        <source>T&amp;able</source>
        <translation type="unfinished">&amp;Таблиця</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shape</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Polygon</source>
        <translation type="unfinished">Полігон</translation>
    </message>
    <message>
        <source>&amp;Location</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Page Placement</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Current Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selecting this will place the frame only on the current page.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Range of Pages:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selecting this will place frame on the selected range. </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Position of Frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top Left of Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selecting this puts the frame on the top left with postion 0,0</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top Left of Margins</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selecting this places the frame in the upper left of the page margins defined in your doc setup.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Custom Position:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Set the dimensions wished below in the X: Y: dialog below.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>X:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Y:</source>
        <translation type="unfinished">Y:</translation>
    </message>
    <message>
        <source>&amp;Size</source>
        <translation type="unfinished">&amp;Розмір</translation>
    </message>
    <message>
        <source>Same as the Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Same as the Page Margins</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Custom Size:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Height:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Width:</source>
        <translation type="unfinished">Товщина:</translation>
    </message>
    <message>
        <source>&amp;Options</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Source Image:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Select File...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+S</source>
        <translation type="unfinished">Alt+S</translation>
    </message>
    <message>
        <source>There are no options for this type of frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Source Document:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Columns:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished">&amp;Гаразд</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
    <message>
        <source>Link Created Frames</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Pages</source>
        <translation type="unfinished">Всі сторінки</translation>
    </message>
    <message>
        <source>...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top Left of Bleed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selecting this places the frame in the upper left of the page bleed defined in your doc setup.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Same as the Bleed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Same as the Imported Image</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>InsertTable</name>
    <message>
        <source>Insert Table</source>
        <translation>Вставити таблицю</translation>
    </message>
    <message>
        <source>Number of rows:</source>
        <translation>Число рядків:</translation>
    </message>
    <message>
        <source>Number of columns:</source>
        <translation>Число колонок:</translation>
    </message>
</context>
<context>
    <name>JavaDocs</name>
    <message>
        <source>New Script</source>
        <translation>Новий сценарій</translation>
    </message>
    <message>
        <source>Edit JavaScripts</source>
        <translation>Редагувати сценарії JavaScript</translation>
    </message>
    <message>
        <source>&amp;Edit...</source>
        <translation>&amp;Редагувати...</translation>
    </message>
    <message>
        <source>&amp;Add...</source>
        <translation>&amp;Додати...</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>&amp;New Script:</source>
        <translation>&amp;Новий сценарій:</translation>
    </message>
    <message>
        <source>&amp;No</source>
        <translation type="obsolete">&amp;Ні</translation>
    </message>
    <message>
        <source>&amp;Yes</source>
        <translation type="obsolete">&amp;Так</translation>
    </message>
    <message>
        <source>Do you really want to delete this script?</source>
        <translation>Ви справді бажаєте видалити цей сценарій?</translation>
    </message>
    <message>
        <source>Adds a new Script, predefines a function with the same name. If you want to use this script as an &quot;Open Action&quot; script be sure not to change the name of the function.</source>
        <translation>Додає новий сценарій та визначає одноіменну функцію. Якщо Ви бажаєте використовувати цей сценарій в &quot;Відчинити 
дію&quot; - не змінюйте назву функції.</translation>
    </message>
</context>
<context>
    <name>KeyManager</name>
    <message>
        <source>Action</source>
        <translation type="obsolete">Дія</translation>
    </message>
    <message>
        <source>Current Key</source>
        <translation type="obsolete">Активна клавіша</translation>
    </message>
    <message>
        <source>Select a Key for this Action</source>
        <translation type="obsolete">Вибрати клавішу для цієї дії</translation>
    </message>
    <message>
        <source>ALT+SHIFT+T</source>
        <translation type="obsolete">ALT+SHIFT+T</translation>
    </message>
    <message>
        <source>Alt</source>
        <translation type="obsolete">Alt</translation>
    </message>
    <message>
        <source>Ctrl</source>
        <translation type="obsolete">Ctrl</translation>
    </message>
    <message>
        <source>Shift</source>
        <translation type="obsolete">Shift</translation>
    </message>
    <message>
        <source>Shift+</source>
        <translation type="obsolete">Shift+</translation>
    </message>
    <message>
        <source>Alt+</source>
        <translation type="obsolete">Alt+</translation>
    </message>
    <message>
        <source>Ctrl+</source>
        <translation type="obsolete">Ctrl+</translation>
    </message>
    <message>
        <source>&amp;No Key</source>
        <translation type="obsolete">&amp;Без ключа</translation>
    </message>
    <message>
        <source>&amp;User Defined Key</source>
        <translation type="obsolete">Ключ визначений &amp;користувачем</translation>
    </message>
    <message>
        <source>Set &amp;Key</source>
        <translation type="obsolete">&amp;Установити ключ</translation>
    </message>
    <message>
        <source>Loadable Shortcut Sets</source>
        <translation type="obsolete">Набори гарячих клавіш</translation>
    </message>
    <message>
        <source>&amp;Load</source>
        <translation type="obsolete">За&amp;вантажити</translation>
    </message>
    <message>
        <source>&amp;Import...</source>
        <translation type="obsolete">&amp;Імпортувати...</translation>
    </message>
    <message>
        <source>&amp;Export...</source>
        <translation type="obsolete">&amp;Експортувати...</translation>
    </message>
    <message>
        <source>&amp;Reset</source>
        <translation type="obsolete">&amp;Перезавантажити</translation>
    </message>
    <message>
        <source>Keyboard shortcut sets available to load</source>
        <translation type="obsolete">Набори гарячих клавіш доступні для завантаження</translation>
    </message>
    <message>
        <source>Load the selected shortcut set</source>
        <translation type="obsolete">Завантажити вибраний набір гарячих клавіш</translation>
    </message>
    <message>
        <source>Import a shortcut set into the current configuration</source>
        <translation type="obsolete">Імпортувати набір гарячих клавіш в активну конфігурацію</translation>
    </message>
    <message>
        <source>Export the current shortcuts into an importable file</source>
        <translation type="obsolete">Експортувати активні гарячі клавіші в зовнішій файл</translation>
    </message>
    <message>
        <source>Reload the default Scribus shortcuts</source>
        <translation type="obsolete">Перезавантажити набір гарячих клавіш по умовчанню</translation>
    </message>
    <message>
        <source>Key Set XML Files (*.ksxml)</source>
        <translation type="obsolete">Файли ключового набору XML (*.ksxml)</translation>
    </message>
    <message>
        <source>This key sequence is already in use</source>
        <translation type="obsolete">Ця ключова послідовність вже використовується</translation>
    </message>
    <message>
        <source>Meta</source>
        <translation type="obsolete">Мета</translation>
    </message>
    <message>
        <source>Meta+</source>
        <translation type="obsolete">Мета+</translation>
    </message>
</context>
<context>
    <name>LayerPalette</name>
    <message>
        <source>Layers</source>
        <translation>Плани</translation>
    </message>
    <message>
        <source>Delete Layer</source>
        <translation>Видалити план</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Do you want to delete all objects on this layer too?</source>
        <translation>Ви бажаєте також видалити всі об&apos;єкти на цьому плані?</translation>
    </message>
    <message>
        <source>Add a new layer</source>
        <translation>Додати новий план</translation>
    </message>
    <message>
        <source>Delete layer</source>
        <translation>Видалити план</translation>
    </message>
    <message>
        <source>Raise layer</source>
        <translation>Підняти план на вищий рівень</translation>
    </message>
    <message>
        <source>Lower layer</source>
        <translation>Опустити план на нижчий рівень</translation>
    </message>
    <message>
        <source>Opacity:</source>
        <translation type="unfinished">Непрозорість:</translation>
    </message>
    <message>
        <source> %</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Blend Mode:</source>
        <translation type="unfinished">Режим змішування:</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Darken</source>
        <translation type="unfinished">Затемнити</translation>
    </message>
    <message>
        <source>Lighten</source>
        <translation type="unfinished">Зробити світлішим</translation>
    </message>
    <message>
        <source>Multiply</source>
        <translation type="unfinished">Перемножити</translation>
    </message>
    <message>
        <source>Screen</source>
        <translation type="unfinished">Екран</translation>
    </message>
    <message>
        <source>Overlay</source>
        <translation type="unfinished">Перекрити</translation>
    </message>
    <message>
        <source>Hard Light</source>
        <translation type="unfinished">Різке світло</translation>
    </message>
    <message>
        <source>Soft Light</source>
        <translation type="unfinished">М&apos;яке світло</translation>
    </message>
    <message>
        <source>Difference</source>
        <translation type="unfinished">Різниця</translation>
    </message>
    <message>
        <source>Exlusion</source>
        <translation type="obsolete">Виключення</translation>
    </message>
    <message>
        <source>Color Dodge</source>
        <translation type="unfinished">Уникання кольору</translation>
    </message>
    <message>
        <source>Color Burn</source>
        <translation type="unfinished">Випалення кольором</translation>
    </message>
    <message>
        <source>Exclusion</source>
        <translation type="unfinished">Виключення</translation>
    </message>
    <message>
        <source>Hue</source>
        <translation type="unfinished">Відтінок</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation type="unfinished">Насичення</translation>
    </message>
    <message>
        <source>Color</source>
        <translation type="unfinished">Колір</translation>
    </message>
    <message>
        <source>Luminosity</source>
        <translation type="unfinished">Яскравість</translation>
    </message>
    <message>
        <source>Color of the Layer Indicator - Each layer has a color assigned to display on the canvas when layer indicators are enabled. You can double click to edit the color. </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Make Layer Visible - Uncheck to hide the layer from the display </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Print Layer - Uncheck to disable printing. </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Lock or Unlock Layer - Unchecked is unlocked </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Text flows around objects in lower Layers - Enabling this forces text frames to flow around other objects, even in layers below</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Outline Mode - Toggles the &apos;wireframe&apos; display of objects to speed the display of very complex objects.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name of the Layer - Double clicking on the name of a layer enabled editing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Duplicates the current layer</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>LineFormate</name>
    <message>
        <source>Edit Line Styles</source>
        <translation>Редагування стилів ліній</translation>
    </message>
    <message>
        <source>Copy of %1</source>
        <translation>Копія %1</translation>
    </message>
    <message>
        <source>New Style</source>
        <translation>Новий стиль</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
        <translation>Документи (*.sla *.sla.gz *.scd *.scd.gz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;All Files (*)</source>
        <translation>Документи (*.sla *.scd);;Всі файли (*)</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>D&amp;uplicate</source>
        <translation>&amp;Дублювати</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>&amp;No</source>
        <translation type="obsolete">&amp;Ні</translation>
    </message>
    <message>
        <source>&amp;Yes</source>
        <translation type="obsolete">&amp;Так</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
    <message>
        <source>Do you really want to delete this style?</source>
        <translation>Ви справді бажаєте видалити цей стиль?</translation>
    </message>
</context>
<context>
    <name>LineStyleWBase</name>
    <message>
        <source>LineStyleWBase</source>
        <translation>Стиль лінії з широкою основою</translation>
    </message>
    <message>
        <source>%</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Line Width:</source>
        <translation>Товщина лінії:</translation>
    </message>
</context>
<context>
    <name>LineStyleWidget</name>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source>Flat Cap</source>
        <translation>Пласка верхівка</translation>
    </message>
    <message>
        <source>Square Cap</source>
        <translation>Квадратна верхівка</translation>
    </message>
    <message>
        <source>Round Cap</source>
        <translation>Заокруглена верхівка</translation>
    </message>
    <message>
        <source>Miter Join</source>
        <translation>Фацетне з&apos;єднання</translation>
    </message>
    <message>
        <source>Bevel Join</source>
        <translation>Фасочне з&apos;єднання</translation>
    </message>
    <message>
        <source>Round Join</source>
        <translation>Заокруглене з&apos;єднання</translation>
    </message>
    <message>
        <source>Solid Line</source>
        <translation type="obsolete">Суцільна лінія</translation>
    </message>
    <message>
        <source>Dashed Line</source>
        <translation type="obsolete">Переривчаста лінія</translation>
    </message>
    <message>
        <source>Dotted Line</source>
        <translation type="obsolete">Лінія з точок</translation>
    </message>
    <message>
        <source>Dash Dot Line</source>
        <translation type="obsolete">Переривчасто точкова лінія</translation>
    </message>
    <message>
        <source>Dash Dot Dot Line</source>
        <translation type="obsolete">Риска-точка-точка лінія</translation>
    </message>
    <message>
        <source>Add a new line</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Remove a line</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line width</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>End style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Join style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line color</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line shade</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>LoadSavePlugin</name>
    <message>
        <source>All Files (*)</source>
        <translation>Всі файли (*)</translation>
    </message>
</context>
<context>
    <name>LoremManager</name>
    <message>
        <source>Select Lorem Ipsum</source>
        <translation>Вибрати Lorem Ipsum</translation>
    </message>
    <message>
        <source>Author:</source>
        <translation>Автор:</translation>
    </message>
    <message>
        <source>Get More:</source>
        <translation>Добавити ще:</translation>
    </message>
    <message>
        <source>XML File:</source>
        <translation>Файл XML:</translation>
    </message>
    <message>
        <source>Lorem Ipsum</source>
        <translation>Lorem Ipsum</translation>
    </message>
    <message>
        <source>Paragraphs:</source>
        <translation>Абзаци:</translation>
    </message>
    <message>
        <source>Alt+O</source>
        <translation>Alt+O</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
    <message>
        <source>Standard Lorem Ipsum</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MarginDialog</name>
    <message>
        <source>Manage Page Properties</source>
        <translation>Керування властивостями сторінки</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation>Розмір сторінки</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation>&amp;Розмір:</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation>&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation>Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation>Горизонтальна</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation>&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation>&amp;Висота:</translation>
    </message>
    <message>
        <source>Move Objects with their Page</source>
        <translation>Пересувати об&apos;єкти разом з їх сторінкою</translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation>Розмітка полів</translation>
    </message>
    <message>
        <source>Type:</source>
        <translation>Тип:</translation>
    </message>
    <message>
        <source>Other Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Master Page:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MarginWidget</name>
    <message>
        <source>&amp;Bottom:</source>
        <translation>&amp;Низ:</translation>
    </message>
    <message>
        <source>&amp;Top:</source>
        <translation>&amp;Верх:</translation>
    </message>
    <message>
        <source>&amp;Right:</source>
        <translation>&amp;Правий край:</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation>&amp;Лівий край:</translation>
    </message>
    <message>
        <source>Distance between the top margin guide and the edge of the page</source>
        <translation>Відстань від границі верхнього поля сторінки до її краю</translation>
    </message>
    <message>
        <source>Distance between the bottom margin guide and the edge of the page</source>
        <translation>Відстань від границі нижнього поля сторінки до її краю</translation>
    </message>
    <message>
        <source>&amp;Inside:</source>
        <translation>&amp;Зсередини:</translation>
    </message>
    <message>
        <source>O&amp;utside:</source>
        <translation>Зз&amp;овні:</translation>
    </message>
    <message>
        <source>Preset Layouts:</source>
        <translation>Попередньо підготовлені схеми розміщення:</translation>
    </message>
    <message>
        <source>Apply margin settings to all pages</source>
        <translation type="obsolete">Застосувати установки полів до всіх сторінок</translation>
    </message>
    <message>
        <source>Apply the margin changes to all existing pages in the document</source>
        <translation>Застосувати зміни полів до всіх існуючих сторінок документа</translation>
    </message>
    <message>
        <source>Distance between the left margin guide and the edge of the page. If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
        <translation type="obsolete">Відстань між направляючою лівого поля і краєм сторінки. Якщо були вибрані дзеркальні сторінки, цей простір на полях може використовуватися для забезпечення достатніх полів для переплітання</translation>
    </message>
    <message>
        <source>Distance between the right margin guide and the edge of the page. If Facing Pages is selected, this margin space can be used to achieve the correct margins for binding</source>
        <translation type="obsolete">Відстань між направляючою правого поля і краєм сторінки. Якщо були вибрані дзеркальні сторінки, цей простір на полях може використовуватися для забезпечення достатніх полів для переплітання</translation>
    </message>
    <message>
        <source>Printer Margins...</source>
        <translation>Поля принтера...</translation>
    </message>
    <message>
        <source>Import the margins for the selected page size from the available printers.</source>
        <translation>Імпортувати поля для вибраного розміру сторінки від доступних принтерів.</translation>
    </message>
    <message>
        <source>Apply settings to:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Document Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Master Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply the margin changes to all existing master pages in the document</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation type="unfinished">Розмітка полів</translation>
    </message>
    <message>
        <source>Top:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bottom:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distance for bleed from the top of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з верхньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the bottom of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з нижньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the left of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з лівої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the right of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з правої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Inside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Outside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Left:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Right:</source>
        <translation type="unfinished">Праве:</translation>
    </message>
    <message>
        <source>Distance between the left margin guide and the edge of the page. If a double-sided, 3 or 4-fold layout is selected, this margin space can be used to achieve the correct margins for binding</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distance between the right margin guide and the edge of the page. If a double-sided, 3 or 4-fold layout is selected, this margin space can be used to achieve the correct margins for binding</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MasterPagesPalette</name>
    <message>
        <source>Edit Master Pages</source>
        <translation>Редагувати майстер сторінки</translation>
    </message>
    <message>
        <source>Do you really want to delete this master page?</source>
        <translation>Ви справді бажаєте видалити цю майстер сторінку?</translation>
    </message>
    <message>
        <source>&amp;No</source>
        <translation type="obsolete">&amp;Ні</translation>
    </message>
    <message>
        <source>&amp;Yes</source>
        <translation type="obsolete">&amp;Так</translation>
    </message>
    <message>
        <source>&amp;Name:</source>
        <translation>&amp;Ім&apos;я:</translation>
    </message>
    <message>
        <source>New Master Page</source>
        <translation>Нова майстер сторінка</translation>
    </message>
    <message>
        <source>Copy of %1</source>
        <translation type="obsolete">Копія %1</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>Ім&apos;я:</translation>
    </message>
    <message>
        <source>New MasterPage</source>
        <translation>Нова майстер сторінка</translation>
    </message>
    <message>
        <source>Copy #%1 of </source>
        <translation>Копія %1 з </translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайна</translation>
    </message>
    <message>
        <source>Duplicate the selected master page</source>
        <translation>Здублювати вибрану майстер сторінку</translation>
    </message>
    <message>
        <source>Delete the selected master page</source>
        <translation>Видалити вибрану майстер сторінку</translation>
    </message>
    <message>
        <source>Add a new master page</source>
        <translation>Додати нову майстер сторінку</translation>
    </message>
    <message>
        <source>Import master pages from another document</source>
        <translation>Імпортувати майстер сторінки з іншого документа</translation>
    </message>
    <message>
        <source>New Master Page %1</source>
        <translation>Нова майстер сторінка %1</translation>
    </message>
    <message>
        <source>Unable to Rename Master Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The Normal page is not allowed to be renamed.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Rename Master Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>New Name:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Mdup</name>
    <message>
        <source>Multiple Duplicate</source>
        <translation>Множинне дублювання</translation>
    </message>
    <message>
        <source>&amp;Number of Copies:</source>
        <translation>&amp;Число копій:</translation>
    </message>
    <message>
        <source>&amp;Horizontal Shift:</source>
        <translation>&amp;Горизонтальний зсув:</translation>
    </message>
    <message>
        <source>&amp;Vertical Shift:</source>
        <translation>&amp;Вертикальний зсув:</translation>
    </message>
</context>
<context>
    <name>Measurements</name>
    <message>
        <source>Distances</source>
        <translation>Відстані</translation>
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
        <translation>Кут:</translation>
    </message>
    <message>
        <source>Length:</source>
        <translation>Довжина:</translation>
    </message>
    <message>
        <source>pt</source>
        <translation>тчк</translation>
    </message>
</context>
<context>
    <name>MergeDoc</name>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
        <translation>Документи (*.sla *.sla.gz *.scd *.scd.gz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;All Files (*)</source>
        <translation>Документи (*.sla *.scd);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Import Page(s)</source>
        <translation>Імпортувати сторінку(и)</translation>
    </message>
    <message>
        <source> from 0</source>
        <translation>від 0</translation>
    </message>
    <message>
        <source>Create Page(s)</source>
        <translation>Створити Сторінку(и)</translation>
    </message>
    <message>
        <source> from %1</source>
        <translation>з %1</translation>
    </message>
    <message>
        <source>Import Master Page</source>
        <translation>Імпортувати Головну сторінку</translation>
    </message>
    <message>
        <source>&amp;From Document:</source>
        <translation>&amp;З документа:</translation>
    </message>
    <message>
        <source>Chan&amp;ge...</source>
        <translation>Змі&amp;нити...</translation>
    </message>
    <message>
        <source>&amp;Import Page(s):</source>
        <translation>&amp;Імпортувати сторінку(и):</translation>
    </message>
    <message>
        <source>&amp;Import Master Page</source>
        <translation>І&amp;мпортувати Головну сторінку</translation>
    </message>
    <message>
        <source>Insert a comma separated list of tokens import where a token can be * for all the pages, 1-5 for a range of pages or a single page number.</source>
        <translation>Вставити розділений комами список знаків де знаком може бути * для всіх сторінок, 1-5 для діапазону сторінок чи номер одної сторінки.</translation>
    </message>
    <message>
        <source>Before Page</source>
        <translation>Перед цією сторінкою</translation>
    </message>
    <message>
        <source>After Page</source>
        <translation>Після цієї сторінки</translation>
    </message>
    <message>
        <source>At End</source>
        <translation>В кінці документа</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
</context>
<context>
    <name>MissingFont</name>
    <message>
        <source>Missing Font</source>
        <translation>Відсутній шрифт</translation>
    </message>
    <message>
        <source>The Font %1 is not installed.</source>
        <translation>Шрифт %1 не встановлений.</translation>
    </message>
    <message>
        <source>Use</source>
        <translation>Використати</translation>
    </message>
    <message>
        <source>instead</source>
        <translation>замість</translation>
    </message>
</context>
<context>
    <name>ModeToolBar</name>
    <message>
        <source>Tools</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Properties...</source>
        <translation type="unfinished">Властивості...</translation>
    </message>
</context>
<context>
    <name>MovePages</name>
    <message>
        <source>Move Pages</source>
        <translation>Переміщення сторінок</translation>
    </message>
    <message>
        <source>Copy Page</source>
        <translation>Скопіювати сторінку</translation>
    </message>
    <message>
        <source>Move Page(s):</source>
        <translation>Перемістити сторінку(и):</translation>
    </message>
    <message>
        <source>Move Page(s)</source>
        <translation>Перемістити сторінку(и)</translation>
    </message>
    <message>
        <source>Before Page</source>
        <translation>Перед цією сторінкою</translation>
    </message>
    <message>
        <source>After Page</source>
        <translation>Після цієї сторінки</translation>
    </message>
    <message>
        <source>At End</source>
        <translation>В кінці документа</translation>
    </message>
    <message>
        <source>To:</source>
        <translation>До:</translation>
    </message>
    <message>
        <source>Number of copies:</source>
        <translation>Число копій:</translation>
    </message>
</context>
<context>
    <name>Mpalette</name>
    <message>
        <source>Properties</source>
        <translation>Властивості</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Geometry</source>
        <translation>Геометрія</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source>Basepoint:</source>
        <translation>Точка відліку:</translation>
    </message>
    <message>
        <source>Level</source>
        <translation>План</translation>
    </message>
    <message>
        <source>Shape:</source>
        <translation>Фігура:</translation>
    </message>
    <message>
        <source>Distance of Text</source>
        <translation>Відстань від тексту</translation>
    </message>
    <message>
        <source>Show Curve</source>
        <translation>Показати криву</translation>
    </message>
    <message>
        <source>Start Offset:</source>
        <translation>Почати відступ:</translation>
    </message>
    <message>
        <source>Distance from Curve:</source>
        <translation>Відстань від кривої:</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Input Profile:</source>
        <translation>Профіль вводу:</translation>
    </message>
    <message>
        <source>Rendering Intent:</source>
        <translation>Схема перерахунку кольорів:</translation>
    </message>
    <message>
        <source>Perceptual</source>
        <translation>Уявний</translation>
    </message>
    <message>
        <source>Relative Colorimetric</source>
        <translation>Відносна кольорометрія</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation>Насичення</translation>
    </message>
    <message>
        <source>Absolute Colorimetric</source>
        <translation>Абсолютна кольорометрія</translation>
    </message>
    <message>
        <source>Left Point</source>
        <translation>Ліва точка</translation>
    </message>
    <message>
        <source>End Points</source>
        <translation>Кінцеві точки</translation>
    </message>
    <message>
        <source>Miter Join</source>
        <translation>Фацеточне з&apos;єднання</translation>
    </message>
    <message>
        <source>Bevel Join</source>
        <translation>Фасочне з&apos;єднання</translation>
    </message>
    <message>
        <source>Round Join</source>
        <translation>Заокруглене з&apos;єднання</translation>
    </message>
    <message>
        <source>Flat Cap</source>
        <translation>Пласка верхівка</translation>
    </message>
    <message>
        <source>Square Cap</source>
        <translation>Квадратна верхівка</translation>
    </message>
    <message>
        <source>Round Cap</source>
        <translation>Заокруглена верхівка</translation>
    </message>
    <message>
        <source>No Style</source>
        <translation>Стиль не встановлено</translation>
    </message>
    <message>
        <source>Font Size</source>
        <translation>Розмір шрифта</translation>
    </message>
    <message>
        <source>Line Spacing</source>
        <translation>Проміжки між рядками</translation>
    </message>
    <message>
        <source>Name of selected object</source>
        <translation>Назва вибраного об&apos;єкту</translation>
    </message>
    <message>
        <source>Horizontal position of current basepoint</source>
        <translation>Горизонтальна позиція активної точки відліку</translation>
    </message>
    <message>
        <source>Vertical position of current basepoint</source>
        <translation>Вертикальна позиція активної точки відліку</translation>
    </message>
    <message>
        <source>Width</source>
        <translation>Ширина</translation>
    </message>
    <message>
        <source>Height</source>
        <translation>Висота</translation>
    </message>
    <message>
        <source>Rotation of object at current basepoint</source>
        <translation>Кут повороту об&apos;єкту від активної точки відліку</translation>
    </message>
    <message>
        <source>Point from which measurements or rotation angles are referenced</source>
        <translation>Точка, відносно якої вимірюються відстані та кути обертання</translation>
    </message>
    <message>
        <source>Select top left for basepoint</source>
        <translation>Вибрати верхній лівий кут, як точку відліку</translation>
    </message>
    <message>
        <source>Select top right for basepoint</source>
        <translation>Вибрати верхній правий кут, як точку відліку</translation>
    </message>
    <message>
        <source>Select bottom left for basepoint</source>
        <translation>Вибрати нижній лівий кут, як точку відліку</translation>
    </message>
    <message>
        <source>Select bottom right for basepoint</source>
        <translation>Вибрати нижній правий кут, як точку відліку</translation>
    </message>
    <message>
        <source>Select center for basepoint</source>
        <translation>Вибрати центр, як точку відліку</translation>
    </message>
    <message>
        <source>Flip Horizontal</source>
        <translation>Перевернути по горизонталі</translation>
    </message>
    <message>
        <source>Flip Vertical</source>
        <translation>Перевернути по вертикалі</translation>
    </message>
    <message>
        <source>Move one level up</source>
        <translation>Перемістити на один план вгору</translation>
    </message>
    <message>
        <source>Move one level down</source>
        <translation>Перемістити на один план вниз</translation>
    </message>
    <message>
        <source>Move to front</source>
        <translation>Перемістити на передній план</translation>
    </message>
    <message>
        <source>Move to back</source>
        <translation>Перемістити на задній план</translation>
    </message>
    <message>
        <source>Lock or unlock the object</source>
        <translation>Замкнути або відімкнути об&apos;єкт</translation>
    </message>
    <message>
        <source>Lock or unlock the size of the object</source>
        <translation>Закнути або відімкнути розмір об&apos;єкта</translation>
    </message>
    <message>
        <source>Enable or disable printing of the object</source>
        <translation>Дозволити або заборонити друкування об&apos;екта</translation>
    </message>
    <message>
        <source>Font of selected text or object</source>
        <translation>Шрифт вибраного тексту чи об&apos;єкта</translation>
    </message>
    <message>
        <source>Scaling width of characters</source>
        <translation>Масштабування ширини знаків</translation>
    </message>
    <message>
        <source>Saturation of color of text stroke</source>
        <translation>Насиченість кольору знакових силуетів</translation>
    </message>
    <message>
        <source>Saturation of color of text fill</source>
        <translation>Насиченість кольору заповнення знаків</translation>
    </message>
    <message>
        <source>Style of current paragraph</source>
        <translation>Стиль активного абзацу</translation>
    </message>
    <message>
        <source>Change settings for left or end points</source>
        <translation>Змінити установки для лівих та правих закінчень</translation>
    </message>
    <message>
        <source>Pattern of line</source>
        <translation>Вид лінії</translation>
    </message>
    <message>
        <source>Thickness of line</source>
        <translation>Товщина лінії</translation>
    </message>
    <message>
        <source>Type of line joins</source>
        <translation>Тип з&apos;єднань ліній</translation>
    </message>
    <message>
        <source>Type of line end</source>
        <translation>Тип закінчення лінії</translation>
    </message>
    <message>
        <source>Line style of current object</source>
        <translation>Стиль ліній активного об&apos;єкту</translation>
    </message>
    <message>
        <source>Choose the shape of frame...</source>
        <translation>Вибрати форму рамки...</translation>
    </message>
    <message>
        <source>Edit shape of the frame...</source>
        <translation>Редагувати форму рамки...</translation>
    </message>
    <message>
        <source>Set radius of corner rounding</source>
        <translation>Установити радіус заокруглення кутів</translation>
    </message>
    <message>
        <source>Number of columns in text frame</source>
        <translation>Число стовпців в текстовій рамці</translation>
    </message>
    <message>
        <source>Distance between columns</source>
        <translation>Інтервал між стовпцями</translation>
    </message>
    <message>
        <source>Distance of text from top of frame</source>
        <translation>Відстань від верхівки рамки до тексту </translation>
    </message>
    <message>
        <source>Distance of text from bottom of frame</source>
        <translation>Відстань від тексту до низу рамки</translation>
    </message>
    <message>
        <source>Distance of text from left of frame</source>
        <translation>Відстань від лівої сторони рамки до тексту</translation>
    </message>
    <message>
        <source>Distance of text from right of frame</source>
        <translation>Відстань від тексту до правої сторони рамки</translation>
    </message>
    <message>
        <source>Edit tab settings of text frame...</source>
        <translation>Редагувати установки відступів текстової рамки...</translation>
    </message>
    <message>
        <source>Allow the image to be a different size to the frame</source>
        <translation>Дозволити неспівпадання розмірів зображення та рамки</translation>
    </message>
    <message>
        <source>Horizontal offset of image within frame</source>
        <translation>Горизонтальне зміщення зображення в рамці</translation>
    </message>
    <message>
        <source>Vertical offset of image within frame</source>
        <translation>Вертикальне зміщення зображення в рамці</translation>
    </message>
    <message>
        <source>Resize the image horizontally</source>
        <translation>Змінити розмір зображення по горизонталі</translation>
    </message>
    <message>
        <source>Resize the image vertically</source>
        <translation>Змінити розмір зображення по вертикалі</translation>
    </message>
    <message>
        <source>Keep the X and Y scaling the same</source>
        <translation>Утримувати масштаб по вісях X та Y однаковим</translation>
    </message>
    <message>
        <source>Make the image fit within the size of the frame</source>
        <translation>Змусити зображення вміститися в рамку</translation>
    </message>
    <message>
        <source>Use image proportions rather than those of the frame</source>
        <translation>Використовувати відношення сторін зображення, а не рамки</translation>
    </message>
    <message>
        <source>Cell Lines</source>
        <translation>Лінії обрамлення клітин таблиці</translation>
    </message>
    <message>
        <source>Line at Top</source>
        <translation>Лінія верхньої сторони</translation>
    </message>
    <message>
        <source>Line at the Left</source>
        <translation>Лінія лівої сторони</translation>
    </message>
    <message>
        <source>Line at the Right </source>
        <translation>Лінія правої сторони</translation>
    </message>
    <message>
        <source>Line at Bottom</source>
        <translation>Лінія нижньої сторони</translation>
    </message>
    <message>
        <source>Keep the aspect ratio</source>
        <translation>Зберігати відношення сторін</translation>
    </message>
    <message>
        <source>Source profile of the image</source>
        <translation>Стартовий профіль зображення</translation>
    </message>
    <message>
        <source>Rendering intent for the image</source>
        <translation>Схема перерахунку кольорів зображення</translation>
    </message>
    <message>
        <source>Switches between Gap or Column width</source>
        <translation>Вибір між шириною стовпців або проміжком між стовпцями</translation>
    </message>
    <message>
        <source>Column width</source>
        <translation>Ширина стовпця</translation>
    </message>
    <message>
        <source>Path Text Properties</source>
        <translation>Властивості текстового шляху</translation>
    </message>
    <message>
        <source>Make text in lower frames flow around the object shape</source>
        <translation type="obsolete">Змусити текст в рамках на задніх планах обтікати форму об&apos;єкта</translation>
    </message>
    <message>
        <source>Indicates the level the object is on, 0 means the object is at the bottom</source>
        <translation>Вказує на план, на якому розташовано об&apos;єкт. Нуль означає, що об&apos;єкт знаходиться на самому нижньому плані</translation>
    </message>
    <message>
        <source>X, Y, &amp;Z</source>
        <translation>X, Y, &amp;Z</translation>
    </message>
    <message>
        <source>&amp;Shape</source>
        <translation>&amp;Фігура</translation>
    </message>
    <message>
        <source>&amp;Text</source>
        <translation>&amp;Текст</translation>
    </message>
    <message>
        <source>&amp;Image</source>
        <translation>&amp;Зображення</translation>
    </message>
    <message>
        <source>&amp;Line</source>
        <translation>&amp;Лінія</translation>
    </message>
    <message>
        <source>&amp;Colors</source>
        <translation>&amp;Кольори</translation>
    </message>
    <message>
        <source>&amp;X-Pos:</source>
        <translation>Поз. &amp;Х:</translation>
    </message>
    <message>
        <source>&amp;Y-Pos:</source>
        <translation>Поз. &amp;У:</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation>&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation>&amp;Висота:</translation>
    </message>
    <message>
        <source>&amp;Rotation:</source>
        <translation>&amp;Кут повороту:</translation>
    </message>
    <message>
        <source>&amp;Edit Shape...</source>
        <translation>&amp;Редагувати форму...</translation>
    </message>
    <message>
        <source>R&amp;ound
Corners:</source>
        <translation>З&amp;аокруглення
кутів:</translation>
    </message>
    <message>
        <source>Colu&amp;mns:</source>
        <translation>&amp;Стовпці:</translation>
    </message>
    <message>
        <source>&amp;Gap:</source>
        <translation type="obsolete">&amp;Проміжок:</translation>
    </message>
    <message>
        <source>To&amp;p:</source>
        <translation>&amp;Верх:</translation>
    </message>
    <message>
        <source>&amp;Bottom:</source>
        <translation>&amp;Низ:</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation>&amp;Лівий край:</translation>
    </message>
    <message>
        <source>&amp;Right:</source>
        <translation>&amp;Правий край:</translation>
    </message>
    <message>
        <source>T&amp;abulators...</source>
        <translation>&amp;Табулятори...</translation>
    </message>
    <message>
        <source>Text &amp;Flows Around Frame</source>
        <translation type="obsolete">Текст &amp;огинає рамку</translation>
    </message>
    <message>
        <source>Use &amp;Bounding Box</source>
        <translation>Використовувати об&amp;межуючу рамку</translation>
    </message>
    <message>
        <source>&amp;Use Contour Line</source>
        <translation>Використовувати &amp;контурну лінію</translation>
    </message>
    <message>
        <source>St&amp;yle:</source>
        <translation>&amp;Стиль:</translation>
    </message>
    <message>
        <source>Lan&amp;guage:</source>
        <translation type="obsolete">&amp;Мова:</translation>
    </message>
    <message>
        <source>&amp;Free Scaling</source>
        <translation>&amp;Вільне масштабування</translation>
    </message>
    <message>
        <source>X-Sc&amp;ale:</source>
        <translation>Масштабування по шкалі &amp;X:</translation>
    </message>
    <message>
        <source>Y-Scal&amp;e:</source>
        <translation>Масштабування по шкалі &amp;Y:</translation>
    </message>
    <message>
        <source>Scale &amp;To Frame Size</source>
        <translation>Установити масштаб по розміру &amp;рамки</translation>
    </message>
    <message>
        <source>P&amp;roportional</source>
        <translation>&amp;Пропорційно</translation>
    </message>
    <message>
        <source>&amp;Basepoint:</source>
        <translation>Точка ві&amp;дліку:</translation>
    </message>
    <message>
        <source>T&amp;ype of Line:</source>
        <translation>&amp;Тип лінії:</translation>
    </message>
    <message>
        <source>Line &amp;Width:</source>
        <translation>Тов&amp;щина лінії:</translation>
    </message>
    <message>
        <source>Ed&amp;ges:</source>
        <translation>&amp;Краї:</translation>
    </message>
    <message>
        <source>&amp;Endings:</source>
        <translation>&amp;Кінці:</translation>
    </message>
    <message>
        <source>&amp;X1:</source>
        <translation>&amp;X1:</translation>
    </message>
    <message>
        <source>X&amp;2:</source>
        <translation>&amp;X2:</translation>
    </message>
    <message>
        <source>Y&amp;1:</source>
        <translation>&amp;Y1:</translation>
    </message>
    <message>
        <source>&amp;Y2:</source>
        <translation>&amp;Y2:</translation>
    </message>
    <message>
        <source>Hyphenation language of frame</source>
        <translation type="obsolete">Установки мови переносів для рамки</translation>
    </message>
    <message>
        <source>Use a surrounding box instead of the frame&apos;s shape for text flow</source>
        <translation type="obsolete">Використовувати прямокутник замість форми рамки для огинання тексту</translation>
    </message>
    <message>
        <source>Use a second line originally based on the frame&apos;s shape for text flow</source>
        <translation type="obsolete">Використовувати другу лінію, основану на формі рамки, для огинання тексту</translation>
    </message>
    <message>
        <source>Right to Left Writing</source>
        <translation>Написання зправа наліво</translation>
    </message>
    <message>
        <source>Manual Tracking</source>
        <translation>Слідкування вручну</translation>
    </message>
    <message>
        <source>Fixed Linespacing</source>
        <translation>Фіксований міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Automatic Linespacing</source>
        <translation>Автоматичний міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Align to Baseline Grid</source>
        <translation>Вирівняти по базовій сітці</translation>
    </message>
    <message>
        <source>Actual X-DPI:</source>
        <translation>Справжні X-DPI:</translation>
    </message>
    <message>
        <source>Actual Y-DPI:</source>
        <translation>Справжні Y-DPI:</translation>
    </message>
    <message>
        <source>Start Arrow:</source>
        <translation>Початок стрілки:</translation>
    </message>
    <message>
        <source>End Arrow:</source>
        <translation>Кінець стрілки:</translation>
    </message>
    <message>
        <source>Offset to baseline of characters</source>
        <translation>Відступ від основи знаків</translation>
    </message>
    <message>
        <source>Scaling height of characters</source>
        <translation>Масштабування висоти знаків</translation>
    </message>
    <message>
        <source>Name &quot;%1&quot; isn&apos;t unique.&lt;br/&gt;Please choose another.</source>
        <translation>Назва &quot;%1&quot; не являється неповторною.&lt;br/&gt;Будь-ласка виберіть іншу.</translation>
    </message>
    <message>
        <source>Color of text stroke. Only available with &quot;outline&quot; text decoration.</source>
        <translation type="obsolete">Колір текстового контура. Доступний лише з прикрасою тексту &quot;контурний&quot;.</translation>
    </message>
    <message>
        <source>Color of text fill. Only available with &quot;outline&quot; text decoration.</source>
        <translation type="obsolete">Колір заповнення тексту. Доступний лише з прикрасою тексту &quot;контурний&quot;.</translation>
    </message>
    <message>
        <source>Fill Rule</source>
        <translation>Правило заливки</translation>
    </message>
    <message>
        <source>Even-Odd</source>
        <translation>Непарний-парний</translation>
    </message>
    <message>
        <source>Non Zero</source>
        <translation>Не нульовий</translation>
    </message>
    <message>
        <source>Click to select the line spacing mode</source>
        <translation type="obsolete">Кляцніть для вибору режиму установки міжрядкових проміжків</translation>
    </message>
    <message>
        <source>Overprinting</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Knockout</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Overprint</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color of text stroke and/or drop shadow, depending which is chosen.If both are chosen, then they share the same color.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color of selected text. If Outline text decoration is enabled, this color will be the fill color. If Drop Shadow Text is enabled, then this will be the top most color.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Width:</source>
        <translation type="unfinished">Товщина:</translation>
    </message>
    <message>
        <source>Text &amp;Flow Around Frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Disabled</source>
        <translation type="unfinished">Вимкнено</translation>
    </message>
    <message>
        <source>Use Frame &amp;Shape</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Image Effects</source>
        <translation type="unfinished">Ефекти зображення</translation>
    </message>
    <message>
        <source>Extended Image Properties</source>
        <translation type="unfinished">Додаткові властивості зображення</translation>
    </message>
    <message>
        <source>Disable text flow from lower frames around object</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Use the frame shape for text flow of text frames below the object.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Use the bounding box, which is always rectangular, instead of the frame&apos;s shape for text flow of text frames below the object. </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Transparency Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Group</source>
        <translation type="unfinished">З&amp;групувати</translation>
    </message>
    <message>
        <source>Opacity:</source>
        <translation type="unfinished">Непрозорість:</translation>
    </message>
    <message>
        <source>Blend Mode:</source>
        <translation type="unfinished">Режим змішування:</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Darken</source>
        <translation type="unfinished">Затемнити</translation>
    </message>
    <message>
        <source>Lighten</source>
        <translation type="unfinished">Зробити світлішим</translation>
    </message>
    <message>
        <source>Multiply</source>
        <translation type="unfinished">Перемножити</translation>
    </message>
    <message>
        <source>Screen</source>
        <translation type="unfinished">Екран</translation>
    </message>
    <message>
        <source>Overlay</source>
        <translation type="unfinished">Перекрити</translation>
    </message>
    <message>
        <source>Hard Light</source>
        <translation type="unfinished">Різке світло</translation>
    </message>
    <message>
        <source>Soft Light</source>
        <translation type="unfinished">М&apos;яке світло</translation>
    </message>
    <message>
        <source>Difference</source>
        <translation type="unfinished">Різниця</translation>
    </message>
    <message>
        <source>Exclusion</source>
        <translation type="unfinished">Виключення</translation>
    </message>
    <message>
        <source>Color Dodge</source>
        <translation type="unfinished">Уникання кольору</translation>
    </message>
    <message>
        <source>Color Burn</source>
        <translation type="unfinished">Випалення кольором</translation>
    </message>
    <message>
        <source>Hue</source>
        <translation type="unfinished">Відтінок</translation>
    </message>
    <message>
        <source>Color</source>
        <translation type="unfinished">Колір</translation>
    </message>
    <message>
        <source>Group the selected objects</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Destroys the selected group</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Auto</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>When chosen, the contour line can be edited with the Edit Shape Tool on the palette further above. When edited via the shape palette, this becomes a second separate line originally based on the frame&apos;s shape for text flow of text frames below the object. T</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Click and hold down to select the line spacing mode.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MultiLine</name>
    <message>
        <source>Edit Style</source>
        <translation>Редагування стилю</translation>
    </message>
    <message>
        <source>Flat Cap</source>
        <translation>Пласка верхівка</translation>
    </message>
    <message>
        <source>Square Cap</source>
        <translation>Квадратна верхівка</translation>
    </message>
    <message>
        <source>Round Cap</source>
        <translation>Заокруглена верхівка</translation>
    </message>
    <message>
        <source>Miter Join</source>
        <translation>Фацетне з&apos;єднання</translation>
    </message>
    <message>
        <source>Bevel Join</source>
        <translation>Фасочне з&apos;єднання</translation>
    </message>
    <message>
        <source>Round Join</source>
        <translation>Заокруглене з&apos;єднання</translation>
    </message>
    <message>
        <source>Line Width:</source>
        <translation>Товщина лінії:</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source> pt </source>
        <translation> тчк </translation>
    </message>
    <message>
        <source>Solid Line</source>
        <translation>Суцільна лінія</translation>
    </message>
    <message>
        <source>Dashed Line</source>
        <translation>Переривчаста лінія</translation>
    </message>
    <message>
        <source>Dotted Line</source>
        <translation>Лінія з точок</translation>
    </message>
    <message>
        <source>Dash Dot Line</source>
        <translation>Переривчасто точкова лінія</translation>
    </message>
    <message>
        <source>Dash Dot Dot Line</source>
        <translation>Риска-точка-точка лінія</translation>
    </message>
    <message>
        <source>Name &quot;%1&quot; isn&apos;t unique.&lt;br/&gt;Please choose another.</source>
        <translation>Назва &quot;%1&quot; не являється неповторною.&lt;br/&gt;Будь-ласка виберіть іншу.</translation>
    </message>
</context>
<context>
    <name>MultiProgressDialogBase</name>
    <message>
        <source>Progress</source>
        <translation>Прогрес</translation>
    </message>
    <message>
        <source>Overall Progress:</source>
        <translation>Загальний прогрес:</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation>В&amp;ихід</translation>
    </message>
</context>
<context>
    <name>MultipleDuplicate</name>
    <message>
        <source>&amp;Horizontal Shift:</source>
        <translation type="unfinished">&amp;Горизонтальний зсув:</translation>
    </message>
    <message>
        <source>&amp;Vertical Shift:</source>
        <translation type="unfinished">&amp;Вертикальний зсув:</translation>
    </message>
    <message>
        <source>&amp;Horizontal Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Vertical Gap:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MultipleDuplicateBase</name>
    <message>
        <source>Multiple Duplicate</source>
        <translation type="unfinished">Множинне дублювання</translation>
    </message>
    <message>
        <source>&amp;By Number of Copies</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Number of Copies:</source>
        <translation type="unfinished">&amp;Число копій:</translation>
    </message>
    <message>
        <source>Create &amp;Gap Between Items Of</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+G</source>
        <translation type="unfinished">Alt+G</translation>
    </message>
    <message>
        <source>&amp;Shift Created Items By</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+S</source>
        <translation type="unfinished">Alt+S</translation>
    </message>
    <message>
        <source>&amp;Horizontal Shift:</source>
        <translation type="unfinished">&amp;Горизонтальний зсув:</translation>
    </message>
    <message>
        <source>&amp;Vertical Shift:</source>
        <translation type="unfinished">&amp;Вертикальний зсув:</translation>
    </message>
    <message>
        <source>By &amp;Rows &amp;&amp; Columns</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Vertical Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Horizontal Gap:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Number of Rows:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Number of Columns:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished">&amp;Гаразд</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
</context>
<context>
    <name>MyPlugin</name>
    <message>
        <source>My &amp;Plugin</source>
        <translation>Мій &amp;модуль</translation>
    </message>
</context>
<context>
    <name>MyPluginImpl</name>
    <message>
        <source>Scribus - My Plugin</source>
        <translation>Scribus - Мій модуль</translation>
    </message>
    <message>
        <source>The plugin worked!</source>
        <translation>Модуль спрацював нормально!</translation>
    </message>
</context>
<context>
    <name>NewDoc</name>
    <message>
        <source>New Document</source>
        <translation>Новий документ</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation type="obsolete">Розмір сторінки</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation>Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation>Горизонтальна</translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation>Розмітка полів</translation>
    </message>
    <message>
        <source>Options</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>Document page size, either a standard size or a custom size</source>
        <translation>Розмір сторінки документа - стандартний чи вибраний Вами</translation>
    </message>
    <message>
        <source>Orientation of the document&apos;s pages</source>
        <translation>Орієнтація сторінок документу</translation>
    </message>
    <message>
        <source>Width of the document&apos;s pages, editable if you have chosen a custom page size</source>
        <translation>Ширина сторінок документу. Може бути змінена, якщо вибраний нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Height of the document&apos;s pages, editable if you have chosen a custom page size</source>
        <translation>Висота сторінок документу. Може бути змінена, якщо вибраний нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Default unit of measurement for document editing</source>
        <translation>Стандартна одиниця вимірювання для редагування документа</translation>
    </message>
    <message>
        <source>Create text frames automatically when new pages are added</source>
        <translation>Автоматично створювати текстові рамки на нових сторінках</translation>
    </message>
    <message>
        <source>Distance between automatically created columns</source>
        <translation>Відстань між автоматично створеними стовпцями</translation>
    </message>
    <message>
        <source>Number of columns to create in automatically created text frames</source>
        <translation>Число стовпців в автоматично створених текстових рамках</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation>&amp;Розмір:</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation>&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation>&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation>&amp;Висота:</translation>
    </message>
    <message>
        <source>&amp;Default Unit:</source>
        <translation>Одиниця виміру по &amp;умовчанню:</translation>
    </message>
    <message>
        <source>&amp;Automatic Text Frames</source>
        <translation>&amp;Автоматичні текстові рамки</translation>
    </message>
    <message>
        <source>&amp;Gap:</source>
        <translation>&amp;Проміжок:</translation>
    </message>
    <message>
        <source>Colu&amp;mns:</source>
        <translation>&amp;Стовпці:</translation>
    </message>
    <message>
        <source>Do not show this dialog again</source>
        <translation>Не показувати це діалогове вікно знову</translation>
    </message>
    <message>
        <source>Initial number of pages of the document</source>
        <translation>Початкове число сторінок документу</translation>
    </message>
    <message>
        <source>N&amp;umber of Pages:</source>
        <translation>Число сто&amp;рінок:</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>&amp;New Document</source>
        <translation>&amp;Новий документ</translation>
    </message>
    <message>
        <source>Open &amp;Existing Document</source>
        <translation>Відчинити &amp;Існуючий документ</translation>
    </message>
    <message>
        <source>Open Recent &amp;Document</source>
        <translation>Відчинити &amp;Недавно редагований документ</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Page Layout</source>
        <translation type="obsolete">Макет сторінки</translation>
    </message>
    <message>
        <source>First Page is:</source>
        <translation type="unfinished">Перша сторінка:</translation>
    </message>
    <message>
        <source>Show Document Settings After Creation</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Document Layout</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>NewFromTemplatePlugin</name>
    <message>
        <source>New &amp;from Template...</source>
        <translation>Новий з &amp;шаблона...</translation>
    </message>
    <message>
        <source>Load documents with predefined layout</source>
        <translation>Завантажити документи певного типу</translation>
    </message>
    <message>
        <source>Start a document from a template made by other users or yourself (f.e. for documents you have a constant style).</source>
        <translation>Створити документ з Вашого чи чужого шаблона (наприклад для дотримання певного стилю документа).</translation>
    </message>
</context>
<context>
    <name>NodePalette</name>
    <message>
        <source>Nodes</source>
        <translation>Вузли</translation>
    </message>
    <message>
        <source>Move Nodes</source>
        <translation>Перемістити вузли</translation>
    </message>
    <message>
        <source>Move Control Points</source>
        <translation>Перемістити контрольні точки</translation>
    </message>
    <message>
        <source>Add Nodes</source>
        <translation>Додати вузли</translation>
    </message>
    <message>
        <source>Delete Nodes</source>
        <translation>Видалити вузли</translation>
    </message>
    <message>
        <source>Reset Control Points</source>
        <translation>Повернути контрольні точки до початкового стану</translation>
    </message>
    <message>
        <source>Reset this Control Point</source>
        <translation>Повернути цю контрольну точку до початкового стану</translation>
    </message>
    <message>
        <source>&amp;Absolute Coordinates</source>
        <translation>&amp;Абсолютні координати</translation>
    </message>
    <message>
        <source>&amp;X-Pos:</source>
        <translation>Поз. &amp;Х:</translation>
    </message>
    <message>
        <source>&amp;Y-Pos:</source>
        <translation>Поз. &amp;У:</translation>
    </message>
    <message>
        <source>Edit &amp;Contour Line</source>
        <translation>Редагувати &amp;контурну лінію</translation>
    </message>
    <message>
        <source>&amp;Reset Contour Line</source>
        <translation>Повернути &amp;контурну лінію в початковий стан</translation>
    </message>
    <message>
        <source>&amp;End Editing</source>
        <translation>&amp;Закінчити редагування</translation>
    </message>
    <message>
        <source>Move Control Points Independently</source>
        <translation>Переміщати контрольні точки незалежно</translation>
    </message>
    <message>
        <source>Move Control Points Symmetrical</source>
        <translation>Переміщати контрольні точки симетрично</translation>
    </message>
    <message>
        <source>Open a Polygon or Cuts a Bezier Curve</source>
        <translation>Роз&apos;єднує полігон або розрізає криву Безьє</translation>
    </message>
    <message>
        <source>Close this Bezier Curve</source>
        <translation>З&apos;єднати кінці кривої Безьє</translation>
    </message>
    <message>
        <source>Mirror the Path Horizontally</source>
        <translation>Віддзеркалити шлях горизонтально</translation>
    </message>
    <message>
        <source>Mirror the Path Vertically</source>
        <translation>Віддзеркалити шлях вертикально</translation>
    </message>
    <message>
        <source>Shear the Path Horizontally to the Left</source>
        <translation>Зсунути шлях горизонтально вліво</translation>
    </message>
    <message>
        <source>Shear the Path Vertically Up</source>
        <translation>Зсунути шлях вертикально вверх</translation>
    </message>
    <message>
        <source>Shear the Path Vertically Down</source>
        <translation>Зсунути шлях вертикально вниз</translation>
    </message>
    <message>
        <source>Rotate the Path Counter-Clockwise</source>
        <translation>Повернути шлях проти годинної стрілки</translation>
    </message>
    <message>
        <source>Rotate the Path Clockwise</source>
        <translation>Повернути шлях по годинній стрілці</translation>
    </message>
    <message>
        <source>Enlarge the Size of the Path by shown %</source>
        <translation>Збільшити розмір шляху на вказані %</translation>
    </message>
    <message>
        <source>Angle of Rotation</source>
        <translation>Кут повороту</translation>
    </message>
    <message>
        <source>Activate Contour Line Editing Mode</source>
        <translation>Активувати режим редагування контурної лінії</translation>
    </message>
    <message>
        <source>Reset the Contour Line to the Original Shape of the Frame</source>
        <translation>Повернути контурну лінію до початкової форми рамки</translation>
    </message>
    <message>
        <source>Shear the Path Horizontally to the Right</source>
        <translation>Зсунути шлях горизонтально вправо</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>When checked use coordinates relative to the page, otherwise coordinates are relative to the Object.</source>
        <translation>Коли вибрано, використовувати координати відносно до сторінки. В іншому випадку координати відносні до об&apos;єкта.</translation>
    </message>
    <message>
        <source>Shrink the Size of the Path by shown %</source>
        <translation>Зменшити розмір шляху на вказані %</translation>
    </message>
    <message>
        <source>Reduce the Size of the Path by the shown value</source>
        <translation>Зменшити розмір шляху на показане значення</translation>
    </message>
    <message>
        <source>Enlarge the Size of the Path by the shown value</source>
        <translation>Збільшити розмір шляху на показане значення</translation>
    </message>
    <message>
        <source>% to Enlarge or Shrink By</source>
        <translation>% збільшення чи зменшення</translation>
    </message>
    <message>
        <source>Value to Enlarge or Shrink By</source>
        <translation>Значення для збільшення чи зменшення</translation>
    </message>
</context>
<context>
    <name>OODPlug</name>
    <message>
        <source>This document does not seem to be an OpenOffice Draw file.</source>
        <translation>Цей документ не схожий на файл OpenOffice Draw.</translation>
    </message>
    <message>
        <source>Group%1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>OODrawImportPlugin</name>
    <message>
        <source>Import &amp;OpenOffice.org Draw...</source>
        <translation>Імпортувати файл  &amp;OpenOffice.org Draw...</translation>
    </message>
    <message>
        <source>Imports OpenOffice.org Draw Files</source>
        <translation>Імпортує файли OpenOffice.org Draw</translation>
    </message>
    <message>
        <source>Imports most OpenOffice.org Draw files into the current document, converting their vector data into Scribus objects.</source>
        <translation>Імпортує більшість файлів OpenOffice.org Draw в активний документ, конвертуючи їхні векторні дані в об&apos;єкти
 Scribus.</translation>
    </message>
    <message>
        <source>OpenDocument 1.0 Draw</source>
        <comment>Import/export format name</comment>
        <translation>OpenDocument 1.0 Draw</translation>
    </message>
    <message>
        <source>OpenOffice.org 1.x Draw</source>
        <comment>Import/export format name</comment>
        <translation>OpenOffice.org 1.x Draw</translation>
    </message>
    <message>
        <source>This file contains some unsupported features</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>OdtDialog</name>
    <message>
        <source>Use document name as a prefix for paragraph styles</source>
        <translation>Використовувати ім&quot;я документа, як префікс для стилів абзаців</translation>
    </message>
    <message>
        <source>Do not ask again</source>
        <translation>Більше на запитувати</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>OpenDocument Importer Options</source>
        <translation>Установки імпортера документів OpenDocument</translation>
    </message>
    <message>
        <source>Enabling this will overwrite existing styles in the current Scribus document</source>
        <translation>Активація цією установки приведе до перезапису існуючих стилів
в активному документі Scribus</translation>
    </message>
    <message>
        <source>Merge Paragraph Styles</source>
        <translation>Об&apos;єднати стилі абзаців</translation>
    </message>
    <message>
        <source>Merge paragraph styles by attributes. This will result in fewer similar paragraph styles, will retain style attributes, even if the original document&apos;s styles are named differently.</source>
        <translation>Об&apos;єднати стилі абзаців по атрибутах. Це приведе до зменшення числа схожих
стилів абзаців і збереже атрибути стилів навіть якщо стилі вихідного документу
мали інші імена.</translation>
    </message>
    <message>
        <source>Prepend the document name to the paragraph style name in Scribus.</source>
        <translation>Приєднати назву документа як префікс до імені стилю абзацу в
Scribus.</translation>
    </message>
    <message>
        <source>Make these settings the default and do not prompt again when importing an OASIS OpenDocument.</source>
        <translation>Зробити ці установки установками по умовчанню і не запитувати знову під
час імпорту документу OASIS OpenDocument.</translation>
    </message>
    <message>
        <source>Overwrite Paragraph Styles</source>
        <translation>Переписати стилі абзаців</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
</context>
<context>
    <name>OldScribusFormat</name>
    <message>
        <source>Scribus Document</source>
        <translation>Документ Scribus</translation>
    </message>
    <message>
        <source>Scribus 1.2.x Document</source>
        <translation>Документ Scribus версій 1.2.x</translation>
    </message>
</context>
<context>
    <name>OneClick</name>
    <message>
        <source>Origin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Size</source>
        <translation type="unfinished">Розмір</translation>
    </message>
    <message>
        <source>Width:</source>
        <translation type="unfinished">Товщина:</translation>
    </message>
    <message>
        <source>Length:</source>
        <translation type="unfinished">Довжина:</translation>
    </message>
    <message>
        <source>Height:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Angle:</source>
        <translation type="unfinished">Кут:</translation>
    </message>
    <message>
        <source>Remember Values</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>OutlineValues</name>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Linewidth</source>
        <translation>Товщина лінії</translation>
    </message>
</context>
<context>
    <name>PDFExportDialog</name>
    <message>
        <source>Save as PDF</source>
        <translation>Записати як PDF</translation>
    </message>
    <message>
        <source>O&amp;utput to File:</source>
        <translation>За&amp;писати в файл:</translation>
    </message>
    <message>
        <source>Cha&amp;nge...</source>
        <translation>З&amp;мінити...</translation>
    </message>
    <message>
        <source>Output one file for eac&amp;h page</source>
        <translation>Експортувати окремий файл для ко&amp;жної сторінки</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>PDF Files (*.pdf);;All Files (*)</source>
        <translation>PDF файли (*.pdf);;Всі файли (*)</translation>
    </message>
    <message>
        <source>This enables exporting one individually named PDF file for each page in the document. Page numbers are added automatically. This is most useful for imposing PDF for commercial printing.</source>
        <translation>Дозволяє експортування одного індивідуально названого PDF файля для кожної сторінки документа. Номери сторінок
додаються автоматично. Цей метод найбільш корисний для імпозиції PDF для комерційного друку.</translation>
    </message>
    <message>
        <source>The save button will be disabled if you are trying to export PDF/X-3 and the info string is missing from the PDF/X-3 tab.</source>
        <translation>Кнопка запису буде недоступна, якщо Ви намагаєтеся експортувати PDF/X-3 і інформаційний рядок відсутній з закладки PDF/X-3.</translation>
    </message>
    <message>
        <source>%1 does not exists and will be created, continue?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Cannot create directory: 
%1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PDFToolBar</name>
    <message>
        <source>PDF Tools</source>
        <translation type="unfinished">PDF Інструменти</translation>
    </message>
</context>
<context>
    <name>PDFlib</name>
    <message>
        <source>Saving PDF</source>
        <translation>Запис PDF</translation>
    </message>
    <message>
        <source>Exporting Master Pages:</source>
        <translation type="obsolete">Експортування майстер сторінок:</translation>
    </message>
    <message>
        <source>Exporting Pages:</source>
        <translation type="obsolete">Експортування сторінок:</translation>
    </message>
    <message>
        <source>Exporting Items on Current Page:</source>
        <translation>Експортування об&apos;єктів з активної сторінки:</translation>
    </message>
    <message>
        <source>Exporting Master Page:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Exporting Page:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Page:</source>
        <translation type="unfinished">Сторінка:</translation>
    </message>
    <message>
        <source>Date:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PPreview</name>
    <message>
        <source>Print Preview</source>
        <translation>Перегляд перед друком</translation>
    </message>
    <message>
        <source>All</source>
        <translation>Все</translation>
    </message>
    <message>
        <source>Shows transparency and transparent items in your document. Requires Ghostscript 7.07 or later</source>
        <translation>Показує прозорість та прозорі об&apos;єкти в документі. Вимагає Ghostscript 7.07 чи новіший</translation>
    </message>
    <message>
        <source>Gives a print preview using simulations of generic CMYK inks, instead of RGB colors</source>
        <translation>Створює перегляд перед друком використовуючи симуляцію  
звичайних  CMYK чорнил замість RGB кольорів</translation>
    </message>
    <message>
        <source>Enable/disable the C (Cyan) ink plate</source>
        <translation>Ввімкнути/вимкнути C (Салатову) чорнильну пластину</translation>
    </message>
    <message>
        <source>Enable/disable the M (Magenta) ink plate</source>
        <translation>Ввімкнути/вимкнути М (Малинову) чорнильну пластину</translation>
    </message>
    <message>
        <source>Enable/disable the Y (Yellow) ink plate</source>
        <translation>Ввімкнути/вимкнути Y (Жовту) чорнильну пластину</translation>
    </message>
    <message>
        <source>Enable/disable the K (Black) ink plate</source>
        <translation>Ввімкнути/вимкнути К (Чорну) чорнильну пластину</translation>
    </message>
    <message>
        <source>Anti-alias &amp;Text</source>
        <translation type="obsolete">Антиаліасинг &amp;тексту</translation>
    </message>
    <message>
        <source>Anti-alias &amp;Graphics</source>
        <translation type="obsolete">Антиаліасинг &amp;графіки</translation>
    </message>
    <message>
        <source>Display Trans&amp;parency</source>
        <translation>Показувати п&amp;розорість</translation>
    </message>
    <message>
        <source>&amp;Display CMYK</source>
        <translation>Показувати &amp;CMYK</translation>
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
        <translation>У &amp;видаленні &amp;кольорів</translation>
    </message>
    <message>
        <source>Separation Name</source>
        <translation>Ім&apos;я кольорового розділення</translation>
    </message>
    <message>
        <source>Cyan</source>
        <translation>Салатовий</translation>
    </message>
    <message>
        <source>Magenta</source>
        <translation>Малиновий</translation>
    </message>
    <message>
        <source>Yellow</source>
        <translation>Жовтий</translation>
    </message>
    <message>
        <source>Black</source>
        <translation>Чорний</translation>
    </message>
    <message>
        <source>Scaling:</source>
        <translation>Масштабування:</translation>
    </message>
    <message>
        <source>Print...</source>
        <translation>Друк...</translation>
    </message>
    <message>
        <source>Provides a more pleasant view of text items in the viewer, at the expense of a slight slowdown in previewing. This only affects Type 1 fonts</source>
        <translation type="obsolete">Забезпечує біль приємний вигляд текстових об&apos;єктів у вікні попереднього перегляду за рахунок невеликого сповільненя процесу перегляду. Лише впливає на шрифти Type 1</translation>
    </message>
    <message>
        <source>Provides a more pleasant view of TrueType Fonts, OpenType Fonts, EPS, PDF and vector graphics in the preview, at the expense of a slight slowdown in previewing</source>
        <translation type="obsolete">Забезпечує біль приємний вигляд шрифтів TrueType та OpenType, EPS, PDF, та векторної графіки у вікні попереднього перегляду за рахунок невеликого сповільненя процесу перегляду</translation>
    </message>
    <message>
        <source>A way of switching off some of the gray shades which are composed of cyan, yellow and magenta and using black instead. UCR most affects parts of images which are neutral and/or dark tones which are close to the gray. Use of this may improve printing some images and some experimentation and testing is need on a case by case basis. UCR reduces the possibility of over saturation with CMY inks.</source>
        <translation>Метод видалення деяких відтінків сірого, скомпонованих з салатового,
жовтого та малинового кольорів, і використання чорного кольору натомість.
UCR найбільше впливає на ті частини зображень, які містять нейтральні чи
темні відтінки, близькі до сірого кольору. Використання цього методу може
покращити друк деяких зображень, але деяке експериментування та
тестування можуть бути необхідними в певних випадках. UCR зменшує
ймовірність перенасичення паперу СЖМ чорнилами.</translation>
    </message>
    <message>
        <source>Resize the scale of the page.</source>
        <translation>Змінити масштаб сторінки.</translation>
    </message>
    <message>
        <source>Close</source>
        <translation>Зачинити</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Force Overprint Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enable &amp;Antialiasing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fit to Width</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fit to Height</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fit to Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Provides a more pleasant view of Type 1 fonts, TrueType Fonts, OpenType Fonts, EPS, PDF and vector graphics in the preview, at the expense of a slight slowdown in previewing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Display Settings</source>
        <translation type="unfinished">Установки показу</translation>
    </message>
    <message>
        <source>Print Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Mirror Page(s) Horizontal</source>
        <translation type="unfinished">Віддзеркалити сторінку(и) горизонтально</translation>
    </message>
    <message>
        <source>Mirror Page(s) Vertical</source>
        <translation type="unfinished">Віддзеркалити сторінку(и) вертикально</translation>
    </message>
    <message>
        <source>Clip to Page Margins</source>
        <translation type="unfinished">Обрізати по полях сторінки</translation>
    </message>
    <message>
        <source>Print in Grayscale</source>
        <translation type="unfinished">Друкувати у відтінках сірого кольору</translation>
    </message>
    <message>
        <source>Convert Spot Colors</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply ICC Profiles</source>
        <translation type="unfinished">Застосувати ICC профілі</translation>
    </message>
    <message>
        <source>Enables Spot Colors to be converted to composite colors. Unless you are planning to print spot colors at a commercial printer, this is probably best left enabled.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enables global Overprint Mode for this document, overrides object settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Allows you to embed ICC profiles in the print stream when color management is enabled</source>
        <translation type="unfinished">Дозволяє вставку кольорових профілів в потік даних для друку при ввімкненому управлінні кольорами</translation>
    </message>
</context>
<context>
    <name>PSLib</name>
    <message>
        <source>Processing Master Pages:</source>
        <translation type="obsolete">Обробка майстер сторінок:</translation>
    </message>
    <message>
        <source>Exporting Pages:</source>
        <translation type="obsolete">Експортування сторінок:</translation>
    </message>
    <message>
        <source>Processing Master Page:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Exporting Page:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PStyleWBase</name>
    <message>
        <source>Form1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Properties</source>
        <translation type="unfinished">Властивості</translation>
    </message>
    <message>
        <source>Parent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distances and Alignment</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Drop Caps</source>
        <translation type="unfinished">Буквиця</translation>
    </message>
    <message>
        <source>Parent&apos;s Drop Cap Status</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Tabulators and Indentation</source>
        <translation type="unfinished">Табулятори та відступи</translation>
    </message>
    <message>
        <source>Ch&amp;aracter Style</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PageItem</name>
    <message>
        <source>Image</source>
        <translation>Зображення</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Текст</translation>
    </message>
    <message>
        <source>Line</source>
        <translation>Лінія</translation>
    </message>
    <message>
        <source>Polygon</source>
        <translation>Полігон</translation>
    </message>
    <message>
        <source>Polyline</source>
        <translation>Багатосегментна лінія</translation>
    </message>
    <message>
        <source>PathText</source>
        <translation>Текст на шляху</translation>
    </message>
    <message>
        <source>Copy of</source>
        <translation>Копія</translation>
    </message>
</context>
<context>
    <name>PageItemAttributes</name>
    <message>
        <source>Relates To</source>
        <translation>Відноситься до</translation>
    </message>
    <message>
        <source>Is Parent Of</source>
        <translation>Батько</translation>
    </message>
    <message>
        <source>Is Child Of</source>
        <translation>Дитина</translation>
    </message>
    <message>
        <source>None</source>
        <comment>relationship</comment>
        <translation>Ніякого</translation>
    </message>
</context>
<context>
    <name>PageItemAttributesBase</name>
    <message>
        <source>Page Item Attributes</source>
        <translation>Атрибути об&apos;єкта сторінки</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Назва</translation>
    </message>
    <message>
        <source>Type</source>
        <translation>Тип</translation>
    </message>
    <message>
        <source>Value</source>
        <translation>Значення</translation>
    </message>
    <message>
        <source>Parameter</source>
        <translation>Параметр</translation>
    </message>
    <message>
        <source>Relationship</source>
        <translation>Зв&apos;язок</translation>
    </message>
    <message>
        <source>Relationship To</source>
        <translation>Зв&apos;язок з</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation>&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+C</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation>Alt+L</translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation>&amp;Гаразд</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation>В&amp;ихід</translation>
    </message>
</context>
<context>
    <name>PageLayouts</name>
    <message>
        <source>Page Layout</source>
        <translation type="obsolete">Макет сторінки</translation>
    </message>
    <message>
        <source>First Page is:</source>
        <translation>Перша сторінка:</translation>
    </message>
    <message>
        <source>Document Layout</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PagePalette</name>
    <message>
        <source>Double sided</source>
        <translation>Двохстороння</translation>
    </message>
    <message>
        <source>Middle Right</source>
        <translation>Середня права</translation>
    </message>
    <message>
        <source>Drag pages or master pages onto the trashbin to delete them</source>
        <translation>Перетягніть сторінки або майстер сторінки на іконку сміттєвої корзини для їх видалення</translation>
    </message>
    <message>
        <source>Here are all your master pages. To create a new page, drag a master page to the page view below</source>
        <translation>Тут містяться всі Ваші майстер сторінки. Для створення нової сторінки перетягніть майстер 
сторінку в поле перегляду сторінок внизу</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайна</translation>
    </message>
    <message>
        <source>Arrange Pages</source>
        <translation>Розташувати сторінки</translation>
    </message>
    <message>
        <source>Available Master Pages:</source>
        <translation>Доступні майстер сторінки:</translation>
    </message>
    <message>
        <source>Document Pages:</source>
        <translation>Сторінки документа:</translation>
    </message>
</context>
<context>
    <name>PageSelector</name>
    <message>
        <source>%1 of %1</source>
        <translation>%1 з %1</translation>
    </message>
    <message>
        <source>%1 of %2</source>
        <translation>%1 з %2</translation>
    </message>
</context>
<context>
    <name>PageSize</name>
    <message>
        <source>Quarto</source>
        <translation type="obsolete">Кварто</translation>
    </message>
    <message>
        <source>Foolscap</source>
        <translation type="obsolete">Фулскап</translation>
    </message>
    <message>
        <source>Letter</source>
        <translation type="obsolete">Лист</translation>
    </message>
    <message>
        <source>Government Letter</source>
        <translation type="obsolete">Урядовий лист</translation>
    </message>
    <message>
        <source>Legal</source>
        <translation type="obsolete">Юридичний</translation>
    </message>
    <message>
        <source>Ledger</source>
        <translation type="obsolete">Бухгалтерський</translation>
    </message>
    <message>
        <source>Executive</source>
        <translation type="obsolete">Виконавчий</translation>
    </message>
    <message>
        <source>Post</source>
        <translation type="obsolete">Поштовий</translation>
    </message>
    <message>
        <source>Crown</source>
        <translation type="obsolete">Королівський</translation>
    </message>
    <message>
        <source>Large Post</source>
        <translation type="obsolete">Великий поштовий</translation>
    </message>
    <message>
        <source>Demy</source>
        <translation type="obsolete">Демі</translation>
    </message>
    <message>
        <source>Medium</source>
        <translation type="obsolete">Середній</translation>
    </message>
    <message>
        <source>Royal</source>
        <translation type="obsolete">Вінценосний</translation>
    </message>
    <message>
        <source>Elephant</source>
        <translation type="obsolete">Слоновий</translation>
    </message>
    <message>
        <source>Double Demy</source>
        <translation type="obsolete">Подвійний демі</translation>
    </message>
    <message>
        <source>Quad Demy</source>
        <translation type="obsolete">Четверний демі</translation>
    </message>
    <message>
        <source>STMT</source>
        <translation type="obsolete">STMT</translation>
    </message>
    <message>
        <source>A</source>
        <translation type="obsolete">A</translation>
    </message>
    <message>
        <source>B</source>
        <translation type="obsolete">B</translation>
    </message>
    <message>
        <source>C</source>
        <translation type="obsolete">С</translation>
    </message>
    <message>
        <source>D</source>
        <translation type="obsolete">D</translation>
    </message>
    <message>
        <source>E</source>
        <translation type="obsolete">E</translation>
    </message>
</context>
<context>
    <name>PatternDialog</name>
    <message>
        <source>Choose a Directory</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Loading Patterns</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Files (*)</source>
        <translation type="unfinished">Всі файли (*)</translation>
    </message>
    <message>
        <source>Open</source>
        <translation type="unfinished">Відчинити</translation>
    </message>
</context>
<context>
    <name>PicSearch</name>
    <message>
        <source>Result</source>
        <translation type="obsolete">Результат</translation>
    </message>
    <message>
        <source>Search Results for: </source>
        <translation type="obsolete">Результати пошуку для:</translation>
    </message>
    <message>
        <source>Preview</source>
        <translation type="obsolete">Попередній перегляд</translation>
    </message>
    <message>
        <source>Select</source>
        <translation type="obsolete">Вибрати</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation type="obsolete">Вихід</translation>
    </message>
</context>
<context>
    <name>PicSearchBase</name>
    <message>
        <source>Result</source>
        <translation type="unfinished">Результат</translation>
    </message>
    <message>
        <source>Search Results for: </source>
        <translation type="unfinished">Результати пошуку для:</translation>
    </message>
    <message>
        <source>&amp;Preview</source>
        <translation type="unfinished">&amp;Попередній перегляд</translation>
    </message>
    <message>
        <source>Alt+P</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Select</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+S</source>
        <translation type="unfinished">Alt+S</translation>
    </message>
</context>
<context>
    <name>PicStatus</name>
    <message>
        <source>Goto</source>
        <translation>Перейти до</translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Missing</source>
        <translation>Відсутні(й)</translation>
    </message>
    <message>
        <source>Search</source>
        <translation>Пошук</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Path</source>
        <translation>Шлях</translation>
    </message>
    <message>
        <source>Page</source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Print</source>
        <translation>Друк</translation>
    </message>
    <message>
        <source>Status</source>
        <translation>Статус</translation>
    </message>
    <message>
        <source>Cancel Search</source>
        <translation>Відмінити пошук</translation>
    </message>
    <message>
        <source>Manage Pictures</source>
        <translation>Керувати зображеннями</translation>
    </message>
    <message>
        <source>Scribus - Image Search</source>
        <translation>Scribus - пошук зображень</translation>
    </message>
    <message>
        <source>The search failed: %1</source>
        <translation>Пошук був безуспішним: %1</translation>
    </message>
    <message>
        <source>No images named &quot;%1&quot; were found.</source>
        <translation>Зображень з назвою &quot;%1&quot; не знайдено.</translation>
    </message>
    <message>
        <source>Select a base directory for search</source>
        <translation>Вибрати базову директорію для пошуку</translation>
    </message>
    <message>
        <source>Search Directory</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Close</source>
        <translation type="unfinished">Зачинити</translation>
    </message>
    <message>
        <source>Set a new location for the selected items. Useful when you may have moved the document but not the images.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Select a base directory for your selected rows</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Case insensitive search</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The filesystem will be searched for case insensitive file names when you check this on. Remember it is not default on most operating systems except MS Windows</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show thumbnails</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show/hide image thumbnails</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PixmapExportPlugin</name>
    <message>
        <source>Save as &amp;Image...</source>
        <translation>Записати, як зо&amp;браження...</translation>
    </message>
    <message>
        <source>Export As Image</source>
        <translation>Експортувати, як зображення</translation>
    </message>
    <message>
        <source>Exports selected pages as bitmap images.</source>
        <translation>Експортувати вибрані сторінки, як растрові зображення.</translation>
    </message>
    <message>
        <source>Save as Image</source>
        <translation type="unfinished">Записати, як зображення</translation>
    </message>
    <message>
        <source>Error writing the output file(s).</source>
        <translation type="unfinished">Помилка при запису вихідного файла(ів).</translation>
    </message>
    <message>
        <source>Export successful</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PluginManager</name>
    <message>
        <source>Cannot find plugin</source>
        <comment>plugin manager</comment>
        <translation>Неможливо знайти модуль</translation>
    </message>
    <message>
        <source>unknown error</source>
        <comment>plugin manager</comment>
        <translation>невідома помилка</translation>
    </message>
    <message>
        <source>Cannot find symbol (%1)</source>
        <comment>plugin manager</comment>
        <translation>Неможливо знайти символ (%1)</translation>
    </message>
    <message>
        <source>Plugin: loading %1</source>
        <comment>plugin manager</comment>
        <translation>Модуль: завантаження %1</translation>
    </message>
    <message>
        <source>init failed</source>
        <comment>plugin load error</comment>
        <translation>Ініціалізація не досягла успіху</translation>
    </message>
    <message>
        <source>unknown plugin type</source>
        <comment>plugin load error</comment>
        <translation>Невідомий тип модуля</translation>
    </message>
    <message>
        <source>Plugin: %1 loaded</source>
        <comment>plugin manager</comment>
        <translation>Модуль: %1 завантажений</translation>
    </message>
    <message>
        <source>Plugin: %1 failed to load: %2</source>
        <comment>plugin manager</comment>
        <translation>Модуль: %1 неможливо завантажити: %2</translation>
    </message>
    <message>
        <source>Plugin: %1 initialized ok </source>
        <comment>plugin manager</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Plugin: %1 failed post initialization</source>
        <comment>plugin manager</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>There is a problem loading %1 of %2 plugins. %3 This is probably caused by some kind of dependency issue or old plugins existing in your install directory. If you clean out your install directory and reinstall and this still occurs, please report it on bugs.scribus.net.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PluginManagerPrefsGui</name>
    <message>
        <source>Plugin Manager</source>
        <translation>Менеджер модулів</translation>
    </message>
    <message>
        <source>Plugin</source>
        <translation>Модуль</translation>
    </message>
    <message>
        <source>How to run</source>
        <translation>Як запустити</translation>
    </message>
    <message>
        <source>Type</source>
        <translation>Тип</translation>
    </message>
    <message>
        <source>Load it?</source>
        <translation>Завантажити?</translation>
    </message>
    <message>
        <source>Plugin ID</source>
        <translation>Ідентифікаційний код модуля</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="obsolete">Ні</translation>
    </message>
    <message>
        <source>You need to restart the application to apply the changes.</source>
        <translation>Програму необхідно перезапустити, щоб активувати зміни.</translation>
    </message>
</context>
<context>
    <name>PolygonProps</name>
    <message>
        <source>Polygon Properties</source>
        <translation>Властивості полігонів</translation>
    </message>
</context>
<context>
    <name>PolygonWidget</name>
    <message>
        <source>Corn&amp;ers:</source>
        <translation>К&amp;ути:</translation>
    </message>
    <message>
        <source>&amp;Rotation:</source>
        <translation>&amp;Кут повороту:</translation>
    </message>
    <message>
        <source>Apply &amp;Factor</source>
        <translation>Застосувати &amp;фактор</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>&amp;Factor:</source>
        <translation>&amp;Фактор:</translation>
    </message>
    <message>
        <source>Number of corners for polygons</source>
        <translation>Число кутів полігонів</translation>
    </message>
    <message>
        <source>Degrees of rotation for polygons</source>
        <translation>Кут повороту полігонів</translation>
    </message>
    <message>
        <source>Apply Convex/Concave Factor to change shape of Polygons</source>
        <translation>Застосувати випуклий/ввігнутий фактор для зміни форми полігонів</translation>
    </message>
    <message>
        <source>Sample Polygon</source>
        <translation>Зразковий полігон</translation>
    </message>
    <message>
        <source>A negative value will make the polygon concave (or star shaped), a positive value will make it convex</source>
        <translation>Негативне значення зробить полігон впуклим (або зіркоподібним), а позитивне значення зробить його випуклим</translation>
    </message>
</context>
<context>
    <name>Preferences</name>
    <message>
        <source>Preferences</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>General</source>
        <translation>Загальні</translation>
    </message>
    <message>
        <source>Document</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>Guides</source>
        <translation>Розмітка</translation>
    </message>
    <message>
        <source>Typography</source>
        <translation>Типографія</translation>
    </message>
    <message>
        <source>Tools</source>
        <translation>Інструменти</translation>
    </message>
    <message>
        <source>Display</source>
        <translation>Відображення</translation>
    </message>
    <message>
        <source>GUI</source>
        <translation type="obsolete">Графічна оболонка</translation>
    </message>
    <message>
        <source>Paths</source>
        <translation type="obsolete">Шляхи</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation type="obsolete">Розмір сторінки</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation type="obsolete">Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation type="obsolete">Горизонтальна</translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation type="obsolete">Розмітка полів</translation>
    </message>
    <message>
        <source>Autosave</source>
        <translation type="obsolete">Автоматичне збереження</translation>
    </message>
    <message>
        <source>min</source>
        <translation type="obsolete">хв</translation>
    </message>
    <message>
        <source> pt</source>
        <translation type="obsolete"> тчк</translation>
    </message>
    <message>
        <source>Choose a Directory</source>
        <translation type="obsolete">Вибрати директорію</translation>
    </message>
    <message>
        <source>External Tools</source>
        <translation>Зовнішні інструменти</translation>
    </message>
    <message>
        <source>Image Processing Tool</source>
        <translation type="obsolete">Інструмент для обробки зображень</translation>
    </message>
    <message>
        <source>Default font size for the menus and windows</source>
        <translation type="obsolete">Стандартний розмір шрифта для меню та вікон</translation>
    </message>
    <message>
        <source>Default unit of measurement for document editing</source>
        <translation type="obsolete">Стандартна одиниця вимірювання для редагування документу</translation>
    </message>
    <message>
        <source>Number of lines Scribus will scroll for each move of the mouse wheel</source>
        <translation type="obsolete">Число рядків для прокручування на кожний рух колеса мишки</translation>
    </message>
    <message>
        <source>Number of recently edited documents to show in the File menu</source>
        <translation type="obsolete">Скільки недавно редагованих документів показувати в меню Файл</translation>
    </message>
    <message>
        <source>Default documents directory</source>
        <translation type="obsolete">Стандартна директорія для документів</translation>
    </message>
    <message>
        <source>Default Scripter scripts directory</source>
        <translation type="obsolete">Стандартна директорія для сценаріїв Сценариста</translation>
    </message>
    <message>
        <source>Default page size, either a standard size or a custom size</source>
        <translation type="obsolete">Стандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Default orientation of document pages</source>
        <translation type="obsolete">Стандартна орієнтація сторінок документа</translation>
    </message>
    <message>
        <source>Width of document pages, editable if you have chosen a custom page size</source>
        <translation type="obsolete">Ширина сторінок документа. Її можна змінити, якщо Ви вибрали нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Height of document pages, editable if you have chosen a custom page size</source>
        <translation type="obsolete">Висота сторінок документа. Її можна змінити, якщо Ви вибрали нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Time period between saving automatically</source>
        <translation type="obsolete">Період часу між двома автоматичними записами файла</translation>
    </message>
    <message>
        <source>Color for paper</source>
        <translation type="obsolete">Колір паперу</translation>
    </message>
    <message>
        <source>Mask the area outside the margins in the margin color</source>
        <translation type="obsolete">Замаскувати область за полями кольором полів</translation>
    </message>
    <message>
        <source>Set the default zoom level</source>
        <translation type="obsolete">Установити стандартний масштаб зображення</translation>
    </message>
    <message>
        <source>Antialias text for EPS and PDF onscreen rendering</source>
        <translation type="obsolete">Антиаліасинг тексту для рендерингу EPS та PDF на екрані</translation>
    </message>
    <message>
        <source>Antialias graphics for EPS and PDF onscreen rendering</source>
        <translation type="obsolete">Антиаліасинг графіки для рендерингу EPS та PDF на екрані</translation>
    </message>
    <message>
        <source>&amp;Theme:</source>
        <translation type="obsolete">&amp;Тема:</translation>
    </message>
    <message>
        <source>&amp;Wheel Jump:</source>
        <translation type="obsolete">&amp;Крок колесика миші:</translation>
    </message>
    <message>
        <source>&amp;Recent Documents:</source>
        <translation type="obsolete">&amp;Недавно редаговані документи:</translation>
    </message>
    <message>
        <source>&amp;Documents:</source>
        <translation type="obsolete">Док&amp;ументи:</translation>
    </message>
    <message>
        <source>&amp;Change...</source>
        <translation type="obsolete">&amp;Замінити...</translation>
    </message>
    <message>
        <source>&amp;ICC Profiles:</source>
        <translation type="obsolete">&amp;ICC профілі:</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation type="obsolete">&amp;Замінити...</translation>
    </message>
    <message>
        <source>&amp;Scripts:</source>
        <translation type="obsolete">&amp;Сценарії:</translation>
    </message>
    <message>
        <source>Ch&amp;ange...</source>
        <translation type="obsolete">&amp;Змінити...</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation type="obsolete">&amp;Розмір:</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation type="obsolete">&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation type="obsolete">&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation type="obsolete">&amp;Висота:</translation>
    </message>
    <message>
        <source>&amp;Bottom:</source>
        <translation type="obsolete">&amp;Низ:</translation>
    </message>
    <message>
        <source>&amp;Top:</source>
        <translation type="obsolete">&amp;Верх:</translation>
    </message>
    <message>
        <source>&amp;Right:</source>
        <translation type="obsolete">&amp;Правий край:</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation type="obsolete">&amp;Лівий край:</translation>
    </message>
    <message>
        <source>&amp;Interval:</source>
        <translation type="obsolete">&amp;Інтервал:</translation>
    </message>
    <message>
        <source>Display &amp;Unprintable Area in Margin Color</source>
        <translation type="obsolete">Виділити &amp;недрукуєму область кольором поля</translation>
    </message>
    <message>
        <source>&amp;Adjust Display Size</source>
        <translation type="obsolete">Поправити &amp;розмір для показу</translation>
    </message>
    <message>
        <source>&amp;Name of Executable:</source>
        <translation type="obsolete">Назва файла про&amp;грами:</translation>
    </message>
    <message>
        <source>Antialias &amp;Text</source>
        <translation type="obsolete">Антиаліасинг &amp;тексту</translation>
    </message>
    <message>
        <source>Antialias &amp;Graphics</source>
        <translation type="obsolete">Антиаліасинг &amp;графіки</translation>
    </message>
    <message>
        <source>Name of &amp;Executable:</source>
        <translation type="obsolete">Назва файла про&amp;грами:</translation>
    </message>
    <message>
        <source>Cha&amp;nge...</source>
        <translation type="obsolete">З&amp;мінити...</translation>
    </message>
    <message>
        <source>&amp;Language:</source>
        <translation type="obsolete">&amp;Мова:</translation>
    </message>
    <message>
        <source>Document T&amp;emplates:</source>
        <translation type="obsolete">Шаблони доку&amp;ментів:</translation>
    </message>
    <message>
        <source>Units:</source>
        <translation type="obsolete">Одиниці виміру:</translation>
    </message>
    <message>
        <source>Undo/Redo</source>
        <translation type="obsolete">Відмінити/повторити</translation>
    </message>
    <message>
        <source>Action history length</source>
        <translation type="obsolete">Розмір історії подій</translation>
    </message>
    <message>
        <source>Hyphenator</source>
        <translation>Переносник</translation>
    </message>
    <message>
        <source>Fonts</source>
        <translation>Шрифти</translation>
    </message>
    <message>
        <source>Color Management</source>
        <translation>Керування кольорами</translation>
    </message>
    <message>
        <source>PDF Export</source>
        <translation>Експорт PDF</translation>
    </message>
    <message>
        <source>Document Item Attributes</source>
        <translation>Атрибути об&apos;єкта документа</translation>
    </message>
    <message>
        <source>Table of Contents and Indexes</source>
        <translation>Зміст та індекси</translation>
    </message>
    <message>
        <source>Keyboard Shortcuts</source>
        <translation>Набори гарячих клавіш</translation>
    </message>
    <message>
        <source>Page Display</source>
        <translation type="obsolete">Показ сторінки</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation type="obsolete">Колір:</translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation type="obsolete">Alt+U</translation>
    </message>
    <message>
        <source>Show Pictures</source>
        <translation type="obsolete">Показати зображення</translation>
    </message>
    <message>
        <source>Show Text Chains</source>
        <translation type="obsolete">Показати текстові ланцюги</translation>
    </message>
    <message>
        <source>Show Text Control Characters</source>
        <translation type="obsolete">Показати контрольні знаки тексту</translation>
    </message>
    <message>
        <source>Show Frames</source>
        <translation type="obsolete">Показати рамки</translation>
    </message>
    <message>
        <source>Scratch Space</source>
        <translation type="obsolete">Чорновик</translation>
    </message>
    <message>
        <source>Always ask before fonts are replaced when loading a document</source>
        <translation type="obsolete">Завжди запитувати перед заміною шрифтів при завантаженні документа</translation>
    </message>
    <message>
        <source>Preview of current Paragraph Style visible when editing Styles</source>
        <translation type="obsolete">Попередній перегляд активних стилів абзаців видимий при редагуванні стилів</translation>
    </message>
    <message>
        <source>Miscellaneous</source>
        <translation>Різне</translation>
    </message>
    <message>
        <source>Plugins</source>
        <translation>Модулі</translation>
    </message>
    <message>
        <source>Turns the display of frames on or off</source>
        <translation type="obsolete">Переключає показ рамок</translation>
    </message>
    <message>
        <source>Turns the display of pictures on or off</source>
        <translation type="obsolete">Переключає показ зображень</translation>
    </message>
    <message>
        <source>Additional directory for document templates</source>
        <translation type="obsolete">Додаткова директорія для шаблонів</translation>
    </message>
    <message>
        <source>Preflight Verifier</source>
        <translation>Передекспортна перевірка</translation>
    </message>
    <message>
        <source>Rulers relative to Page</source>
        <translation type="obsolete">Лінійки відносні до сторінки</translation>
    </message>
    <message>
        <source>Gaps between Pages</source>
        <translation type="obsolete">Проміжки між сторінками</translation>
    </message>
    <message>
        <source>Horizontal:</source>
        <translation type="obsolete">Горизонтальна:</translation>
    </message>
    <message>
        <source>Vertical:</source>
        <translation type="obsolete">Вертикальна:</translation>
    </message>
    <message>
        <source>To adjust the display drag the ruler below with the slider.</source>
        <translation type="obsolete">Для зміни видимого перетягніть лінійку внизу повзунком.</translation>
    </message>
    <message>
        <source>dpi</source>
        <translation type="obsolete">тнд</translation>
    </message>
    <message>
        <source>Resolution:</source>
        <translation type="obsolete">Розрішення:</translation>
    </message>
    <message>
        <source>Show Startup Dialog</source>
        <translation type="obsolete">Показувати стартовий діалог</translation>
    </message>
    <message>
        <source>Lorem Ipsum</source>
        <translation type="obsolete">Lorem Ipsum</translation>
    </message>
    <message>
        <source>Always use standard Lorem Ipsum</source>
        <translation type="obsolete">Завжди використовувати стандартний текст Lorem Ipsum</translation>
    </message>
    <message>
        <source>Count of the Paragraphs:</source>
        <translation type="obsolete">Число абзаців:</translation>
    </message>
    <message>
        <source>Display non-printing characters such as paragraph markers in text frames</source>
        <translation type="obsolete">Показувати недруковані знаки, такі як маркери абзаців, в текстових рамках</translation>
    </message>
    <message>
        <source>Place a ruler against your screen and drag the slider to set the zoom level so Scribus will display your pages and objects on them at the correct size</source>
        <translation type="obsolete">Притуліть лінійку до екрану та зсуньте повзунок масштаба зображення поки Scribus не почне показувати справжній розмір сторінок та об&apos;єктів на них</translation>
    </message>
    <message>
        <source>Defines amount of space left of the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="obsolete">Визначає розмір простіру на канві зліва від документа доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space right of the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="obsolete">Визначає розмір простіру на канві справа від документа доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space above the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="obsolete">Визначає розмір простіру на канві над документом доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space below the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="obsolete">Визначає розмір простіру на канві під документом доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>PostScript Interpreter</source>
        <translation type="obsolete">Інтерпретатор постскрипт</translation>
    </message>
    <message>
        <source>Enable or disable  the display of linked frames.</source>
        <translation type="obsolete">Ввімкнути або вимкнути показ поєднаних рамок.</translation>
    </message>
    <message>
        <source>Select your default language for Scribus to run with. Leave this blank to choose based on environment variables. You can still override this by passing a command line option when starting Scribus</source>
        <translation type="obsolete">Виберіть основну мову для використання в Scribus. Залиште пустим для використання перемінних робочого середовища. Ви зможете змінити цю установку за допомогою використання перемикачів командної строки при запуску Scribus</translation>
    </message>
    <message>
        <source>Locate Ghostscript</source>
        <translation type="obsolete">Знайти Ghostscript </translation>
    </message>
    <message>
        <source>Locate your image editor</source>
        <translation type="obsolete">Знайти редактор зображень</translation>
    </message>
    <message>
        <source>&amp;Font Size (Menus):</source>
        <translation type="obsolete">&amp;Розмір шрифта (Меню):</translation>
    </message>
    <message>
        <source>Font Size (&amp;Palettes):</source>
        <translation type="obsolete">Розмір шрифта (&amp;Палітри):</translation>
    </message>
    <message>
        <source>Choose the default window decoration and looks. Scribus inherits any available KDE or Qt themes, if Qt is configured to search KDE plugins.</source>
        <translation type="obsolete">Виберіть стандартні декорацію вікон та вигляд програми. Scribus має доступ до всіх наявних тем KDE та Qt, якщо Qt
сконфігурований для пошуку KDE модулів.</translation>
    </message>
    <message>
        <source>Default font size for the tool windows</source>
        <translation type="obsolete">Стандартний розмір шрифта для вікон інструментарію</translation>
    </message>
    <message>
        <source>Default ICC profiles directory. This cannot be changed with a document open. By default, Scribus will look in the System Directories under Mac OSX and Windows. On Linux and Unix, Scribus will search $home/.color/icc,/usr/share/color/icc and /usr/local/share/color/icc </source>
        <translation type="obsolete">Стандартна директорія для кольорових профілів. Ця установка не може бути змінена при відчиненому документі. По умовчанню
Scribus виконає пошук в системних директоріях під системами MacOSX та Windows. Під Linux та Unix Scribus шукатиме в
директоріях $home/.color/icc,/usr/share/color/icc та /usr/local/share/color/icc(sp)</translation>
    </message>
    <message>
        <source>When enabled, Scribus saves a backup copy of your file with the .bak extension each time the time period elapses</source>
        <translation type="obsolete">Якщо ввімкнено, Scribus зберігатиме резервну копію файла з розширенням .bak в кінці кожног заданого періода</translation>
    </message>
    <message>
        <source>Set the length of the action history in steps. If set to 0 infinite amount of actions will be stored.</source>
        <translation type="obsolete">Установити протяжність історії дій в кроках. Якщо установлено 0 (нуль) то зберігатиметься необмежена кількість кроків.</translation>
    </message>
    <message>
        <source>File system location for graphics editor. If you use gimp and your distro includes it, we recommend &apos;gimp-remote&apos;, as it allows you to edit the image in an already running instance of gimp.</source>
        <translation type="obsolete">Розміщення редактора зображень в системі. Якщо Ви використовуєте The Gimp і Ваш дистрибутив Linux його містить - ми
рекомендуємо &apos;gimp-remote&apos;, тому що це дозволяє редагувати зображення в уже запущеному редакторі.</translation>
    </message>
    <message>
        <source>Filesystem location for the Ghostscript interpreter.</source>
        <translation type="obsolete">Розміщення інтерпретатора Ghostscript в файловій системі.</translation>
    </message>
    <message>
        <source>Scrapbook</source>
        <translation type="unfinished">Чорновик</translation>
    </message>
    <message>
        <source>Printer</source>
        <translation type="unfinished">Прінтер</translation>
    </message>
</context>
<context>
    <name>PrefsDialogBase</name>
    <message>
        <source>&amp;Defaults</source>
        <translation>По &amp;умовчанню</translation>
    </message>
    <message>
        <source>Save...</source>
        <translation type="obsolete">Записати...</translation>
    </message>
    <message>
        <source>Save Preferences</source>
        <translation>Записати установки</translation>
    </message>
    <message>
        <source>Export...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Apply</source>
        <translation type="unfinished">&amp;Застосувати</translation>
    </message>
    <message>
        <source>All preferences can be reset here</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply all changes without closing the dialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Export current preferences into file</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PrefsManager</name>
    <message>
        <source>Postscript</source>
        <translation>Постскрипт</translation>
    </message>
    <message>
        <source>PDF 1.3</source>
        <translation>PDF 1.3</translation>
    </message>
    <message>
        <source>PDF 1.4</source>
        <translation>PDF 1.4</translation>
    </message>
    <message>
        <source>PDF/X-3</source>
        <translation>PDF/X-3</translation>
    </message>
    <message>
        <source>Migrate Old Scribus Settings?</source>
        <translation>Конвертувати старі установки?</translation>
    </message>
    <message>
        <source>Scribus has detected existing Scribus 1.2 preferences files.
Do you want to migrate them to the new Scribus version?</source>
        <translation>Scribus знайшов файл з установками формату Scribus 1.2.
Ви бажаєте конвертувати їх у формат нової версії Scribus?</translation>
    </message>
    <message>
        <source>PostScript</source>
        <translation>Постскрипт</translation>
    </message>
    <message>
        <source>Could not open preferences file &quot;%1&quot; for writing: %2</source>
        <translation>Неможливо відчинити файл з установками &quot;%1&quot; для запису: %2</translation>
    </message>
    <message>
        <source>Writing to preferences file &quot;%1&quot; failed: QIODevice status code %2</source>
        <translation>Запис у файл установок &quot;%1&quot; неможливий: код статуса QIODevice %2</translation>
    </message>
    <message>
        <source>Failed to open prefs file &quot;%1&quot;: %2</source>
        <translation>Неможливо відчинити файл установок &quot;%1&quot;: %2</translation>
    </message>
    <message>
        <source>Failed to read prefs XML from &quot;%1&quot;: %2 at line %3, col %4</source>
        <translation>Неможливо прочитати ХМЛ установки з &quot;%1&quot;: %2 в рядку %3, колонка %4</translation>
    </message>
    <message>
        <source>Error Writing Preferences</source>
        <translation>Помилка запису установок</translation>
    </message>
    <message>
        <source>Scribus was not able to save its preferences:&lt;br&gt;%1&lt;br&gt;Please check file and directory permissions and available disk space.</source>
        <comment>scribus app error</comment>
        <translation>Scribus не зміг записати свої установки:&lt;br&gt;%1&lt;br&gt;Будь-ласка перевірте дозволи на запис файлів та директорій та наявність вільного простіру на диску.</translation>
    </message>
    <message>
        <source>Error Loading Preferences</source>
        <translation>Помилка зчитування установок</translation>
    </message>
    <message>
        <source>Scribus was not able to load its preferences:&lt;br&gt;%1&lt;br&gt;Default settings will be loaded.</source>
        <translation>Scribus не зміг зчитати свої установки:&lt;br&gt;%1&lt;br&gt;Будуть використані стандартні установки.</translation>
    </message>
</context>
<context>
    <name>PresetLayout</name>
    <message>
        <source>Magazine</source>
        <translation>Журнал</translation>
    </message>
    <message>
        <source>Fibonacci</source>
        <translation>Фібоначчі</translation>
    </message>
    <message>
        <source>Golden Mean</source>
        <translation>Золота середина</translation>
    </message>
    <message>
        <source>Nine Parts</source>
        <translation>Дев&apos;ять частин</translation>
    </message>
    <message>
        <source>Gutenberg</source>
        <translation>Гутенберг</translation>
    </message>
    <message>
        <source>You can select predefined page layout here. &apos;None&apos; leave margins as is, Gutenberg sets margins classically. &apos;Magazine&apos; sets all margins for same value. Leading is Left/Inside value.</source>
        <translation type="obsolete">Тут ви можете вибрати попереднь визначений формат. &apos;Ніякий&apos; залишає поля в незмінному виді, Гутенберг змінює поля в
 класичному стилі. &apos;Журнальний&apos; установлює всі поля до однакового значення. Головним є ліве/внутрішнє значення.</translation>
    </message>
    <message>
        <source>None</source>
        <comment>layout type</comment>
        <translation>Ніякого</translation>
    </message>
    <message>
        <source>You can select a predefined page layout here. &apos;None&apos; leave margins as is, Gutenberg sets margins classically. &apos;Magazine&apos; sets all margins for same value. Leading is Left/Inside value.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PythonConsole</name>
    <message>
        <source>&amp;Open...</source>
        <translation>&amp;Відчинити...</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>&amp;Exit</source>
        <translation>В&amp;ийти</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <source>&amp;Run</source>
        <translation>&amp;Запустити</translation>
    </message>
    <message>
        <source>&amp;Save Output...</source>
        <translation>За&amp;писати результат...</translation>
    </message>
    <message>
        <source>&amp;Script</source>
        <translation>С&amp;ценарій</translation>
    </message>
    <message>
        <source>Script Console</source>
        <translation>Консоль сценарія</translation>
    </message>
    <message>
        <source>Write your commands here. A selection is processed as script</source>
        <translation>Пишіть Ваші команди тут. Вибірка буде виконана, як сценарій</translation>
    </message>
    <message>
        <source>Output of your script</source>
        <translation>Результат виконання сценарія</translation>
    </message>
    <message>
        <source>Python Scripts (*.py)</source>
        <translation type="obsolete">Сценарї на Пітоні (*.py)</translation>
    </message>
    <message>
        <source>Save the Python Commands in File</source>
        <translation>Записати команди на пітоні в файл</translation>
    </message>
    <message>
        <source>Warning</source>
        <translation type="obsolete">Застереження</translation>
    </message>
    <message>
        <source>Text Files (*.txt)</source>
        <translation>Текстові файли (*.txt)</translation>
    </message>
    <message>
        <source>Save Current Output</source>
        <translation>Записати активний результат</translation>
    </message>
    <message>
        <source>Save &amp;As...</source>
        <translation>Записати &amp;як...</translation>
    </message>
    <message>
        <source>Run As &amp;Console</source>
        <translation>Виконати в ко&amp;нсолі</translation>
    </message>
    <message>
        <source>Scribus Python Console</source>
        <translation>Консоль Пітону</translation>
    </message>
    <message>
        <source>This is derived from standard Python console so it contains some limitations esp. in the case of whitespaces. Please consult Scribus manual for more informations.</source>
        <translation>Модифікована з стандартної консолі Пітону, тому може містити деякі обмеження особливу у випадку проміжків. Будь-ласка зверніться до керівництва користувача Scribus за подальшою інформацією.</translation>
    </message>
    <message>
        <source>Open Python Script File</source>
        <translation>Відчинити сценарій на мові Пітон</translation>
    </message>
    <message>
        <source>Python Scripts (*.py *.PY)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line: %1 Column: %2</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>QColorDialog</name>
    <message>
        <source>Hu&amp;e:</source>
        <translation>&amp;Тон:</translation>
    </message>
    <message>
        <source>&amp;Sat:</source>
        <translation>На&amp;сиченість:</translation>
    </message>
    <message>
        <source>&amp;Val:</source>
        <translation>З&amp;начення:</translation>
    </message>
    <message>
        <source>&amp;Red:</source>
        <translation>&amp;Червоний:</translation>
    </message>
    <message>
        <source>&amp;Green:</source>
        <translation>&amp;Зелений:</translation>
    </message>
    <message>
        <source>Bl&amp;ue:</source>
        <translation>&amp;Синій:</translation>
    </message>
    <message>
        <source>A&amp;lpha channel:</source>
        <translation>&amp;Альфа канал:</translation>
    </message>
    <message>
        <source>&amp;Basic colors</source>
        <translation>&amp;Базові кольори</translation>
    </message>
    <message>
        <source>&amp;Custom colors</source>
        <translation>&amp;Власні кольори</translation>
    </message>
    <message>
        <source>&amp;Define Custom Colors &gt;&gt;</source>
        <translation>&amp;Вибрати власні кольори &gt;&gt;</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>&amp;Add to Custom Colors</source>
        <translation>&amp;Добавити у власні кольори</translation>
    </message>
    <message>
        <source>Select color</source>
        <translation>Вибрати колір</translation>
    </message>
</context>
<context>
    <name>QFileDialog</name>
    <message>
        <source>Copy or Move a File</source>
        <translation>Копіювати або перемістити файл</translation>
    </message>
    <message>
        <source>Read: %1</source>
        <translation>Зчитати: %1</translation>
    </message>
    <message>
        <source>Write: %1</source>
        <translation>Записати: %1</translation>
    </message>
    <message>
        <source>File &amp;name:</source>
        <translation>Ім&apos;я &amp;файла:</translation>
    </message>
    <message>
        <source>File &amp;type:</source>
        <translation>Тип &amp;файла:</translation>
    </message>
    <message>
        <source>One directory up</source>
        <translation>На один рівень вгору</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>All Files (*)</source>
        <translation>Всі файли (*)</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Size</source>
        <translation>Розмір</translation>
    </message>
    <message>
        <source>Type</source>
        <translation>Тип</translation>
    </message>
    <message>
        <source>Date</source>
        <translation>Дата</translation>
    </message>
    <message>
        <source>Attributes</source>
        <translation>Аттрибути</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Look &amp;in:</source>
        <translation>Шукати &amp;в:</translation>
    </message>
    <message>
        <source>Back</source>
        <translation>Назад</translation>
    </message>
    <message>
        <source>Create New Folder</source>
        <translation>Створити нову директорію</translation>
    </message>
    <message>
        <source>List View</source>
        <translation>Короткий список</translation>
    </message>
    <message>
        <source>Detail View</source>
        <translation>Детальний список</translation>
    </message>
    <message>
        <source>Preview File Info</source>
        <translation>Попередній перегляд інформації по файлу</translation>
    </message>
    <message>
        <source>Preview File Contents</source>
        <translation>Попередній перегляд вмісту файла</translation>
    </message>
    <message>
        <source>Read-write</source>
        <translation>Зчитування та запис</translation>
    </message>
    <message>
        <source>Read-only</source>
        <translation>Лише зчитування</translation>
    </message>
    <message>
        <source>Write-only</source>
        <translation>Лише запис</translation>
    </message>
    <message>
        <source>Inaccessible</source>
        <translation>Недоступний</translation>
    </message>
    <message>
        <source>Symlink to File</source>
        <translation>Символічний лінк до файла</translation>
    </message>
    <message>
        <source>Symlink to Directory</source>
        <translation>Символічний лінк до директорії</translation>
    </message>
    <message>
        <source>Symlink to Special</source>
        <translation>Символічний лінк до особливого</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Dir</source>
        <translation>Директорія</translation>
    </message>
    <message>
        <source>Special</source>
        <translation>Особливий</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Save As</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>&amp;Open</source>
        <translation>&amp;Відчинити</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>&amp;Rename</source>
        <translation>&amp;Перейменувати</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>R&amp;eload</source>
        <translation>П&amp;еречитати</translation>
    </message>
    <message>
        <source>Sort by &amp;Name</source>
        <translation>Сортувати по &amp;Імені</translation>
    </message>
    <message>
        <source>Sort by &amp;Size</source>
        <translation>Сортувати по &amp;Розміру</translation>
    </message>
    <message>
        <source>Sort by &amp;Date</source>
        <translation>Сортувати по &amp;Даті</translation>
    </message>
    <message>
        <source>&amp;Unsorted</source>
        <translation>&amp;Несортований</translation>
    </message>
    <message>
        <source>Sort</source>
        <translation>Сортувати</translation>
    </message>
    <message>
        <source>Show &amp;hidden files</source>
        <translation>Показати при&amp;ховані файли</translation>
    </message>
    <message>
        <source>the file</source>
        <translation>файл</translation>
    </message>
    <message>
        <source>the directory</source>
        <translation>директорія</translation>
    </message>
    <message>
        <source>the symlink</source>
        <translation>символічний лінк</translation>
    </message>
    <message>
        <source>Delete %1</source>
        <translation>Видалити %1</translation>
    </message>
    <message>
        <source>&lt;qt&gt;Are you sure you wish to delete %1 &quot;%2&quot;?&lt;/qt&gt;</source>
        <translation>&lt;qt&gt;Ви справді бажаєте видалити %1 &quot;%2&quot;?&lt;/qt&gt;</translation>
    </message>
    <message>
        <source>&amp;Yes</source>
        <translation type="obsolete">&amp;Так</translation>
    </message>
    <message>
        <source>&amp;No</source>
        <translation type="obsolete">&amp;Ні</translation>
    </message>
    <message>
        <source>New Folder 1</source>
        <translation>Нова директорія 1</translation>
    </message>
    <message>
        <source>New Folder</source>
        <translation>Нова директорія</translation>
    </message>
    <message>
        <source>New Folder %1</source>
        <translation>Нова директорія %1</translation>
    </message>
    <message>
        <source>Find Directory</source>
        <translation>Знайти директорію</translation>
    </message>
    <message>
        <source>Directories</source>
        <translation>Директорії</translation>
    </message>
    <message>
        <source>Save</source>
        <translation>Записати</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Помилка</translation>
    </message>
    <message>
        <source>%1
File not found.
Check path and filename.</source>
        <translation>%1
Файл не знайдено.
Перевірте шлях та ім&apos;я файла.</translation>
    </message>
    <message>
        <source>All Files (*.*)</source>
        <translation>Всі файли (*.*)</translation>
    </message>
    <message>
        <source>Select a Directory</source>
        <translation>Вибрати директорію</translation>
    </message>
    <message>
        <source>Directory:</source>
        <translation>Директорія:</translation>
    </message>
</context>
<context>
    <name>QFontDialog</name>
    <message>
        <source>&amp;Font</source>
        <translation>&amp;Шрифт</translation>
    </message>
    <message>
        <source>Font st&amp;yle</source>
        <translation>&amp;Стиль шрифта</translation>
    </message>
    <message>
        <source>&amp;Size</source>
        <translation>&amp;Розмір</translation>
    </message>
    <message>
        <source>Effects</source>
        <translation>Ефекти</translation>
    </message>
    <message>
        <source>Stri&amp;keout</source>
        <translation>Пере&amp;креслення</translation>
    </message>
    <message>
        <source>&amp;Underline</source>
        <translation>&amp;Підкреслення</translation>
    </message>
    <message>
        <source>&amp;Color</source>
        <translation>&amp;Колір</translation>
    </message>
    <message>
        <source>Sample</source>
        <translation>Зразок</translation>
    </message>
    <message>
        <source>Scr&amp;ipt</source>
        <translation>С&amp;ценарій</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Apply</source>
        <translation>Застосувати</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>Close</source>
        <translation>Зачинити</translation>
    </message>
    <message>
        <source>Select Font</source>
        <translation>Вибрати шрифт</translation>
    </message>
</context>
<context>
    <name>QLineEdit</name>
    <message>
        <source>Clear</source>
        <translation>Очистити</translation>
    </message>
    <message>
        <source>Select All</source>
        <translation>Вибрати все</translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation>&amp;Відмінити</translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation>&amp;Повторити</translation>
    </message>
    <message>
        <source>Cu&amp;t</source>
        <translation>Ви&amp;різати</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
</context>
<context>
    <name>QMainWindow</name>
    <message>
        <source>Line up</source>
        <translation>Вирівняти</translation>
    </message>
    <message>
        <source>Customize...</source>
        <translation>Свої установки...</translation>
    </message>
</context>
<context>
    <name>QMessageBox</name>
    <message>
        <source>&lt;h3&gt;About Qt&lt;/h3&gt;&lt;p&gt;This program uses Qt version %1.&lt;/p&gt;&lt;p&gt;Qt is a C++ toolkit for multiplatform GUI &amp;amp; application development.&lt;/p&gt;&lt;p&gt;Qt provides single-source portability across MS&amp;nbsp;Windows, Mac&amp;nbsp;OS&amp;nbsp;X, Linux, and all major commercial Unix variants.&lt;br&gt;Qt is also available for embedded devices.&lt;/p&gt;&lt;p&gt;Qt is a Trolltech product. See &lt;tt&gt;http://www.trolltech.com/qt/&lt;/tt&gt; for more information.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;Про Qt&lt;/h3&gt;&lt;p&gt;Ця програма використовує версію %1 Qt .&lt;/p&gt;&lt;p&gt;Qt - багатоплатформний набір для розробки графічних оболонок та програмного забезпечення в C++.&lt;/p&gt;&lt;p&gt;Qt дає можливість портативного використання коду між  MS&amp;nbsp;Windows, Mac&amp;nbsp;OS&amp;nbsp;X, Лінукс та всіма основними комерційними варіантами UNIX.&lt;br&gt;Існує версія Qt  для вбудованих пристроїв.&lt;/p&gt;&lt;p&gt;Qt - продукт компанії Trolltech. Зверніться до &lt;tt&gt;http://www.trolltech.com/qt/&lt;/tt&gt; за додатковою інформацією.&lt;/p&gt;</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <source>Initializing...</source>
        <translation>Ініціалізація...</translation>
    </message>
    <message>
        <source>Warning</source>
        <translation type="obsolete">Застереження</translation>
    </message>
    <message>
        <source>Do you really want to overwrite the File:
%1 ?</source>
        <translation>Ви справді бажаєте переписати файл:
%1 ?</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>SVG-Images (*.svg *.svgz);;All Files (*)</source>
        <translation>SVG-зображення (*.svg *.svgz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>SVG-Images (*.svg);;All Files (*)</source>
        <translation>SVG-зображення (*.svg);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Yes</source>
        <translation type="obsolete">Так</translation>
    </message>
    <message>
        <source>No</source>
        <translation type="obsolete">Ні</translation>
    </message>
    <message>
        <source>Background</source>
        <translation>Фон</translation>
    </message>
    <message>
        <source>Error writing the output file(s).</source>
        <translation type="obsolete">Помилка при запису вихідного файла(ів).</translation>
    </message>
    <message>
        <source>File exists. Overwrite?</source>
        <translation type="obsolete">Файл вже існує. Переписати поверх?</translation>
    </message>
    <message>
        <source>exists already. Overwrite?</source>
        <translation type="obsolete">вже існує. Переписати поверх?</translation>
    </message>
    <message>
        <source>Yes all</source>
        <translation type="obsolete">Гаразд для всіх</translation>
    </message>
    <message>
        <source>Save as Image</source>
        <translation type="obsolete">Записати, як зображення</translation>
    </message>
    <message>
        <source>Export successful.</source>
        <translation type="obsolete">Експорт успішний.</translation>
    </message>
    <message>
        <source>All Supported Formats (*.eps *.EPS *.ps *.PS);;</source>
        <translation type="obsolete">Всі доступні формати (*.eps *.EPS *.ps *.PS);;</translation>
    </message>
    <message>
        <source>All Files (*)</source>
        <translation>Всі файли (*)</translation>
    </message>
    <message>
        <source>Newsletters</source>
        <translation>Інформаційні бюлетні</translation>
    </message>
    <message>
        <source>Brochures</source>
        <translation>Брошури</translation>
    </message>
    <message>
        <source>Catalogs</source>
        <translation>Каталоги</translation>
    </message>
    <message>
        <source>Flyers</source>
        <translation>Листівки</translation>
    </message>
    <message>
        <source>Signs</source>
        <translation>Знаки</translation>
    </message>
    <message>
        <source>Cards</source>
        <translation>Картки</translation>
    </message>
    <message>
        <source>Letterheads</source>
        <translation>Бланки</translation>
    </message>
    <message>
        <source>Envelopes</source>
        <translation>Конверти</translation>
    </message>
    <message>
        <source>Business Cards</source>
        <translation>Візитні картки</translation>
    </message>
    <message>
        <source>Calendars</source>
        <translation>Календарі</translation>
    </message>
    <message>
        <source>Advertisements</source>
        <translation>Реклами</translation>
    </message>
    <message>
        <source>Labels</source>
        <translation>Етикетки</translation>
    </message>
    <message>
        <source>Menus</source>
        <translation>Меню</translation>
    </message>
    <message>
        <source>Programs</source>
        <translation>Програми</translation>
    </message>
    <message>
        <source>PDF Forms</source>
        <translation>PDF Форми</translation>
    </message>
    <message>
        <source>Magazines</source>
        <translation>Журнали</translation>
    </message>
    <message>
        <source>Posters</source>
        <translation>Плакати</translation>
    </message>
    <message>
        <source>Announcements</source>
        <translation>Оголошення</translation>
    </message>
    <message>
        <source>Text Documents</source>
        <translation>Текстові документи</translation>
    </message>
    <message>
        <source>Folds</source>
        <translation>Розгортки</translation>
    </message>
    <message>
        <source>Own Templates</source>
        <translation>Шаблони користувача</translation>
    </message>
    <message>
        <source>PDF Presentations</source>
        <translation>PDF презентації</translation>
    </message>
    <message>
        <source>&amp;Scribus Scripts</source>
        <translation>С&amp;ценарії Scribus</translation>
    </message>
    <message>
        <source>&amp;Execute Script...</source>
        <translation>&amp;Виконати сценарій...</translation>
    </message>
    <message>
        <source>&amp;Recent Scripts</source>
        <translation>&amp;Недавно виконані сценарії</translation>
    </message>
    <message>
        <source>Show &amp;Console</source>
        <translation>Покзати ко&amp;нсоль</translation>
    </message>
    <message>
        <source>Importing text</source>
        <translation>Імпорт тексту</translation>
    </message>
    <message>
        <source>All Supported Formats</source>
        <translation>Всі формати, що підтримуються</translation>
    </message>
    <message>
        <source>HTML Files</source>
        <translation>HTML файли</translation>
    </message>
    <message>
        <source>html</source>
        <translation>html</translation>
    </message>
    <message>
        <source>Text Files</source>
        <translation>Текстові файли</translation>
    </message>
    <message>
        <source>Comma Separated Value Files</source>
        <translation>Файли з розділеними комами полями</translation>
    </message>
    <message>
        <source>CSV_data</source>
        <translation>Дані_cvs</translation>
    </message>
    <message>
        <source>CSV_header</source>
        <translation>Заголовок_cvs</translation>
    </message>
    <message>
        <source>Font %1 is broken, discarding it</source>
        <translation>Видаляється пошкоджений шрифт %1</translation>
    </message>
    <message>
        <source>
External Links
</source>
        <translation>Зовнішні зсилки</translation>
    </message>
    <message>
        <source>Text Filters</source>
        <translation>Текстові фільтри</translation>
    </message>
    <message>
        <source>Media Cases</source>
        <translation>Футляри для мультимедійних носіїв</translation>
    </message>
    <message>
        <source>Albanian</source>
        <translation>Албанська</translation>
    </message>
    <message>
        <source>Basque</source>
        <translation>Баскська</translation>
    </message>
    <message>
        <source>Bulgarian</source>
        <translation>Болгарська</translation>
    </message>
    <message>
        <source>Brazilian</source>
        <translation type="obsolete">Бразільська</translation>
    </message>
    <message>
        <source>Catalan</source>
        <translation>Каталанська</translation>
    </message>
    <message>
        <source>Chinese</source>
        <translation>Китайська</translation>
    </message>
    <message>
        <source>Czech</source>
        <translation>Чешська</translation>
    </message>
    <message>
        <source>Danish</source>
        <translation>Датська</translation>
    </message>
    <message>
        <source>Dutch</source>
        <translation>Голландська</translation>
    </message>
    <message>
        <source>English</source>
        <translation>Англійська</translation>
    </message>
    <message>
        <source>English (British)</source>
        <translation>Англійська (Британська)</translation>
    </message>
    <message>
        <source>Esperanto</source>
        <translation>Есперанто</translation>
    </message>
    <message>
        <source>German</source>
        <translation>Німецька</translation>
    </message>
    <message>
        <source>Finnish</source>
        <translation>Фінська</translation>
    </message>
    <message>
        <source>French</source>
        <translation>Французька</translation>
    </message>
    <message>
        <source>Galician</source>
        <translation>Галицька</translation>
    </message>
    <message>
        <source>Greek</source>
        <translation>Грецька</translation>
    </message>
    <message>
        <source>Hungarian</source>
        <translation>Венгерська</translation>
    </message>
    <message>
        <source>Indonesian</source>
        <translation>Індонезійська</translation>
    </message>
    <message>
        <source>Italian</source>
        <translation>Італійська</translation>
    </message>
    <message>
        <source>Korean</source>
        <translation>Корейська</translation>
    </message>
    <message>
        <source>Lithuanian</source>
        <translation>Литовська</translation>
    </message>
    <message>
        <source>Norwegian (Bokmaal)</source>
        <translation type="obsolete">Норвезька (Букмааль)</translation>
    </message>
    <message>
        <source>Norwegian (Nnyorsk)</source>
        <translation>Норвезька (Нниорськ)</translation>
    </message>
    <message>
        <source>Norwegian</source>
        <translation>Норвезька</translation>
    </message>
    <message>
        <source>Polish</source>
        <translation>Польська</translation>
    </message>
    <message>
        <source>Russian</source>
        <translation>Російська</translation>
    </message>
    <message>
        <source>Swedish</source>
        <translation>Шведська</translation>
    </message>
    <message>
        <source>Spanish</source>
        <translation>Іспанська</translation>
    </message>
    <message>
        <source>Spanish (Latin)</source>
        <translation>Іспанська (Латинь)</translation>
    </message>
    <message>
        <source>Slovak</source>
        <translation>Словацька</translation>
    </message>
    <message>
        <source>Slovenian</source>
        <translation>Словенська</translation>
    </message>
    <message>
        <source>Serbian</source>
        <translation>Сербська</translation>
    </message>
    <message>
        <source>&amp;About Script...</source>
        <translation>&amp;Про скрипт...</translation>
    </message>
    <message>
        <source>About Script</source>
        <translation>Про скрипт</translation>
    </message>
    <message>
        <source>Cannot get font size of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити розмір шрифта в нетекстовій рамці.
</translation>
    </message>
    <message>
        <source>Cannot get font of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити шрифт в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot get text size of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити розмір тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot get column count of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити число колонок тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot get line space of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити міжрядковий інтервал в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot get column gap of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо визначити дистанцію між колонками тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot get text of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо повернути текст з нетекстової рамки.</translation>
    </message>
    <message>
        <source>Cannot set text of non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити текст в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot insert text into non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо вставити текст в нетекстову рамку.</translation>
    </message>
    <message>
        <source>Alignment out of range. Use one of the scribus.ALIGN* constants.</source>
        <comment>python error</comment>
        <translation>Вирівнювання виходить за доступний діапазон. Використайте
одну з констант ALIGN*.</translation>
    </message>
    <message>
        <source>Selection index out of bounds</source>
        <comment>python error</comment>
        <translation>Індекс вибірки виходить за доступний діапазон</translation>
    </message>
    <message>
        <source>Object is not a linked text frame, can&apos;t unlink.</source>
        <comment>python error</comment>
        <translation>Об&apos;єкт не являється зв&apos;язаною текстовою рамкою, неможливо розімкнути.</translation>
    </message>
    <message>
        <source>Object the last frame in a series, can&apos;t unlink. Unlink the previous frame instead.</source>
        <comment>python error</comment>
        <translation>Об&apos;єкт являється останньою рамкою в серії, неможливо роз&apos;єднати. Роз&apos;єднайте попередню рамку натомість.</translation>
    </message>
    <message>
        <source>Unit out of range. Use one of the scribus.UNIT_* constants.</source>
        <comment>python error</comment>
        <translation>Одиниця виходить за доступний діапазон. Використайте одну з
scribus.UNIT_* констант.</translation>
    </message>
    <message>
        <source>Target is not an image frame.</source>
        <comment>python error</comment>
        <translation>Рамка призначення не є рамкою для зображень.</translation>
    </message>
    <message>
        <source>Corner radius must be a positive number.</source>
        <comment>python error</comment>
        <translation>Радіус кута повинен бути позитивним числом.</translation>
    </message>
    <message>
        <source>Cannot get a color with an empty name.</source>
        <comment>python error</comment>
        <translation>Неможливо повернути колір з пустим ім&apos;ям.</translation>
    </message>
    <message>
        <source>Cannot change a color with an empty name.</source>
        <comment>python error</comment>
        <translation>Неможливо змінити колір з пустим ім&apos;ям.</translation>
    </message>
    <message>
        <source>Cannot create a color with an empty name.</source>
        <comment>python error</comment>
        <translation>Неможливо створити колір з пустим ім&apos;ям.</translation>
    </message>
    <message>
        <source>Cannot delete a color with an empty name.</source>
        <comment>python error</comment>
        <translation>Неможливо видалити колір з пустим ім&apos;ям.</translation>
    </message>
    <message>
        <source>Cannot replace a color with an empty name.</source>
        <comment>python error</comment>
        <translation>Неможливо замінити колір з пустим ім&apos;ям.</translation>
    </message>
    <message>
        <source>OpenOffice.org Writer Documents</source>
        <translation>Документи OpenOffice.org Writer</translation>
    </message>
    <message>
        <source>Color not found - python error</source>
        <comment>python error</comment>
        <translation>Колір не знайдено - помилка Пітону</translation>
    </message>
    <message>
        <source>Custom (optional) configuration: </source>
        <comment>short words plugin</comment>
        <translation>Нетипова (необов&apos;язкова) конфігурація:</translation>
    </message>
    <message>
        <source>Standard configuration: </source>
        <comment>short words plugin</comment>
        <translation>Стандартна конфігурація:</translation>
    </message>
    <message>
        <source>Short Words processing. Wait please...</source>
        <comment>short words plugin</comment>
        <translation>Опрацювання коротких слів. Будь-ласка почекайте...</translation>
    </message>
    <message>
        <source>Short Words processing. Done.</source>
        <comment>short words plugin</comment>
        <translation>Опрацювання коротких слів закінчено.</translation>
    </message>
    <message>
        <source>Afrikaans</source>
        <translation>Африкаанс</translation>
    </message>
    <message>
        <source>Turkish</source>
        <translation>Турецька</translation>
    </message>
    <message>
        <source>Ukranian</source>
        <translation>Українська</translation>
    </message>
    <message>
        <source>Welsh</source>
        <translation>Уельська</translation>
    </message>
    <message>
        <source>The filename must be a string.</source>
        <comment>python error</comment>
        <translation>Назва файла повинна бути строковою величиною.</translation>
    </message>
    <message>
        <source>Cannot delete image type settings.</source>
        <comment>python error</comment>
        <translation>Не можу видалити установки типу зображення.</translation>
    </message>
    <message>
        <source>The image type must be a string.</source>
        <comment>python error</comment>
        <translation>Тип зображення повинен бути строковою величиною.</translation>
    </message>
    <message>
        <source>&apos;allTypes&apos; attribute is READ-ONLY</source>
        <comment>python error</comment>
        <translation>Атрибут &apos;allTypes&apos; може бути лише зчитаним</translation>
    </message>
    <message>
        <source>Failed to export image</source>
        <comment>python error</comment>
        <translation>Не вдалося експортувати зображення</translation>
    </message>
    <message>
        <source>Color not found.</source>
        <comment>python error</comment>
        <translation>Колір не знайдено.</translation>
    </message>
    <message>
        <source>Color not found in document.</source>
        <comment>python error</comment>
        <translation>Колір не знайдено в документі.</translation>
    </message>
    <message>
        <source>Color not found in default colors.</source>
        <comment>python error</comment>
        <translation>Колір не знайдено в стандартних кольорах.</translation>
    </message>
    <message>
        <source>Cannot scale by 0%.</source>
        <comment>python error</comment>
        <translation>Змінити масштаб на 0% неможливо.</translation>
    </message>
    <message>
        <source>Specified item not an image frame.</source>
        <comment>python error</comment>
        <translation>Вказаний об&apos;єкт не являється рамкою для зображень.</translation>
    </message>
    <message>
        <source>Font not found.</source>
        <comment>python error</comment>
        <translation>Шрифт не знайдено.</translation>
    </message>
    <message>
        <source>Cannot render an empty sample.</source>
        <comment>python error</comment>
        <translation>Неможливо заповнити пустий зразок.</translation>
    </message>
    <message>
        <source>Cannot have an empty layer name.</source>
        <comment>python error</comment>
        <translation>Неможливо використати пусте ім&apos;я плану.</translation>
    </message>
    <message>
        <source>Layer not found.</source>
        <comment>python error</comment>
        <translation>План не знайдено.</translation>
    </message>
    <message>
        <source>Cannot remove the last layer.</source>
        <comment>python error</comment>
        <translation>Неможливо видалити останній план.</translation>
    </message>
    <message>
        <source>Cannot create layer without a name.</source>
        <comment>python error</comment>
        <translation>Неможливо створити план без імені.</translation>
    </message>
    <message>
        <source>Insert index out of bounds.</source>
        <comment>python error</comment>
        <translation>Індекс вставки виходить за доступний діапазон.</translation>
    </message>
    <message>
        <source>Cannot set text alignment on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо встановити вирівнювання тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Font size out of bounds - must be 1 &lt;= size &lt;= 512.</source>
        <comment>python error</comment>
        <translation>Розмір шрифта виходить за доступний діапазон - повинен бути 1 &lt;= розмір &lt;= 512.</translation>
    </message>
    <message>
        <source>Cannot set font size on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити розмір шрифта в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot set font on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити шрифт в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Line space out of bounds, must be &gt;= 0.1.</source>
        <comment>python error</comment>
        <translation>Міжрядковий інтервал виходить за межі дозволеного, має бути  &gt;= 0.1.</translation>
    </message>
    <message>
        <source>Cannot set line spacing on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити міжрядковий інтервал в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Column gap out of bounds, must be positive.</source>
        <comment>python error</comment>
        <translation>Дистанція між колонками тексту виходить за дозволений проміжок. Повинна бути позитивною.</translation>
    </message>
    <message>
        <source>Cannot set column gap on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити дистанцію між колонками тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Column count out of bounds, must be &gt; 1.</source>
        <comment>python error</comment>
        <translation>Число колонок тексту виходить за доступний діапазон - повинен бути &gt; 1.</translation>
    </message>
    <message>
        <source>Cannot set number of columns on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити число колонок тексту в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot select text in a non-text frame</source>
        <comment>python error</comment>
        <translation>Неможливо вибрати текст в нетекстовій рамці</translation>
    </message>
    <message>
        <source>Cannot delete text from a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо видалити текст в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot set text fill on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити заповнення текста в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot set text stroke on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити контур текста в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Cannot set text shade on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити тінь текста в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Can only link text frames.</source>
        <comment>python error</comment>
        <translation>Установити зв&apos;язок можна лише між текстовими рамками.</translation>
    </message>
    <message>
        <source>Target frame must be empty.</source>
        <comment>python error</comment>
        <translation>Рамка призначення повинна бути пустою.</translation>
    </message>
    <message>
        <source>Target frame links to another frame.</source>
        <comment>python error</comment>
        <translation>Рамка призначення зв&apos;язана з іншою рамкою.</translation>
    </message>
    <message>
        <source>Target frame is linked to by another frame.</source>
        <comment>python error</comment>
        <translation>Інша рамка зв&apos;язана з рамкою призначення.</translation>
    </message>
    <message>
        <source>Source and target are the same object.</source>
        <comment>python error</comment>
        <translation>Джерело та ціль є одним і тим же об&apos;єктом.</translation>
    </message>
    <message>
        <source>Cannot unlink a non-text frame.</source>
        <comment>python error</comment>
        <translation>Видалити зв&apos;язок можна лише між текстовими рамками.</translation>
    </message>
    <message>
        <source>Cannot convert a non-text frame to outlines.</source>
        <comment>python error</comment>
        <translation>Неможливо конвертувати нетекстову рамку в контур.</translation>
    </message>
    <message>
        <source>Can&apos;t set bookmark on a non-text frame</source>
        <comment>python error</comment>
        <translation>Неможливо установити закладку в нетекстовій рамці</translation>
    </message>
    <message>
        <source>Can&apos;t get info from a non-text frame</source>
        <comment>python error</comment>
        <translation>Неможливо визначити інформацію з нетекстової рамки</translation>
    </message>
    <message>
        <source>OpenDocument Text Documents</source>
        <translation>Текстові документи OpenDocument </translation>
    </message>
    <message>
        <source>Croatian</source>
        <translation>Хорватська</translation>
    </message>
    <message>
        <source>Portuguese</source>
        <translation>Португальська</translation>
    </message>
    <message>
        <source>Portuguese (BR)</source>
        <translation>Португальська (Бр)</translation>
    </message>
    <message>
        <source>Scribus Crash</source>
        <translation>Аварійний вихід Scribus</translation>
    </message>
    <message>
        <source>Scribus crashes due to Signal #%1</source>
        <translation>Аварійний вихід Scribus з приводу сигнала номер %1</translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation>&amp;Гаразд</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Page</source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Master Page </source>
        <translation>Головна сторінка</translation>
    </message>
    <message>
        <source>4A0</source>
        <translation>4A0</translation>
    </message>
    <message>
        <source>2A0</source>
        <translation>2A0</translation>
    </message>
    <message>
        <source>Comm10E</source>
        <translation>Comm10E</translation>
    </message>
    <message>
        <source>DLE</source>
        <translation>DLE</translation>
    </message>
    <message>
        <source>Could not open output file %1</source>
        <translation>Неможливо відчинити вихідний файл %1</translation>
    </message>
    <message>
        <source>Output stream not writeable</source>
        <translation>Неможливо писати у вихідний потік</translation>
    </message>
    <message>
        <source>Verification of settings failed: %1</source>
        <translation>Перевірка установок не пройшла успішно: %1</translation>
    </message>
    <message>
        <source>Could not open input file %1</source>
        <translation>Неможливо відчинити вхідний файл %1</translation>
    </message>
    <message>
        <source>Unable to read settings XML:</source>
        <translation>Неможливо зчитати установки ХМЛ:</translation>
    </message>
    <message>
        <source>%1 (line %2 col %3)</source>
        <comment>Load PDF settings</comment>
        <translation>%1 (рядок %2 колонка %3)</translation>
    </message>
    <message>
        <source>Unable to read settings XML: %1</source>
        <translation>Неможливо зчитати установки ХМЛ: %1</translation>
    </message>
    <message>
        <source>null root node</source>
        <comment>Load PDF settings</comment>
        <translation>Нульовий корневий вузол</translation>
    </message>
    <message>
        <source>&lt;pdfVersion&gt; invalid</source>
        <comment>Load PDF settings</comment>
        <translation>&lt;pdfVersion&gt; невірна</translation>
    </message>
    <message>
        <source>found %1 &lt;%2&gt; nodes, need 1.</source>
        <comment>Load PDF settings</comment>
        <translation>знайдено %1 &lt;%2&gt; вузлів, повинен бути 1.</translation>
    </message>
    <message>
        <source>unexpected null &lt;%2&gt; node</source>
        <comment>Load PDF settings</comment>
        <translation>неочікуваний нульовий &lt;%2&gt; вузол</translation>
    </message>
    <message>
        <source>node &lt;%1&gt; not an element</source>
        <comment>Load PDF settings</comment>
        <translation>вузол &lt;%1&gt; не являється елементом</translation>
    </message>
    <message>
        <source>element &lt;%1&gt; lacks `value&apos; attribute</source>
        <comment>Load PDF settings</comment>
        <translation>елемент &lt;%1&gt; не містить атрибут `value&apos;</translation>
    </message>
    <message>
        <source>element &lt;%1&gt; value must be `true&apos; or `false&apos;</source>
        <comment>Load PDF settings</comment>
        <translation>значення елемента &lt;%1&gt; повинне бути `true&apos; або `false&apos;</translation>
    </message>
    <message>
        <source>element &lt;lpiSettingsEntry&gt; lacks `name&apos; attribute</source>
        <comment>Load PDF settings</comment>
        <translation>елемент &lt;lpiSettingsEntry&gt; не містить атрибут `name&apos; </translation>
    </message>
    <message>
        <source>Freetype2 library not available</source>
        <translation>Бібліотека Freetype2 недоступна</translation>
    </message>
    <message>
        <source>Font %1 is broken, no embedding</source>
        <translation type="obsolete">Шрифт %1 містить помилку - вставка недоступна</translation>
    </message>
    <message>
        <source>Font %1 is broken (read stream), no embedding</source>
        <translation>Шрифт %1 містить помилку (вхідний потік) - вставка недоступна</translation>
    </message>
    <message>
        <source>Font %1 is broken (FreeType2), discarding it</source>
        <translation type="obsolete">Шрифт %1 містить помилку (FreeType2) і буде видалено</translation>
    </message>
    <message>
        <source>Font %1 is broken (no Face), discarding it</source>
        <translation type="unfinished">Шрифт %1 містить помилку (відсутній тип) і буде видалено</translation>
    </message>
    <message>
        <source>Font %1 has broken glyph %2 (charcode %3)</source>
        <translation>Шрифт %1 містить помилковий символ %2 (код символа %3)</translation>
    </message>
    <message>
        <source>Font %1 is broken and will be discarded</source>
        <translation type="obsolete">Шрифт %1 містить помилку і буде видалено</translation>
    </message>
    <message>
        <source>Font %1 cannot be read, no embedding</source>
        <translation>Шрифт %1 неможливо зчитати - вставка недоступна</translation>
    </message>
    <message>
        <source>Failed to load font %1 - font type unknown</source>
        <translation>Неможливо завантажити шрифт %1 - невідомий тип шрифта</translation>
    </message>
    <message>
        <source>Font %1 loaded from %2(%3)</source>
        <translation>Шрифт %1 завантажено з %2(%3)</translation>
    </message>
    <message>
        <source>Font %1(%2) is duplicate of %3</source>
        <translation>Шрифт %1(%2) являється копією %3</translation>
    </message>
    <message>
        <source>Loading font %1 (found using fontconfig)</source>
        <translation>Завантажується шрифт %1 (знайдений за допомогою fontconfig)</translation>
    </message>
    <message>
        <source>Font %1 (found using fontconfig) is broken, discarding it</source>
        <translation type="obsolete">Шрифт %1 (знайдений за допомогою fontconfig) містить помилку і буде видалено</translation>
    </message>
    <message>
        <source>Failed to load a font - freetype2 couldn&apos;t find the font file</source>
        <translation>Неможливо завантажити шрифт - freetype2 не може знайти файл шрифта</translation>
    </message>
    <message>
        <source>Font %1 is broken (FreeType), discarding it</source>
        <translation type="obsolete">Шрифт %1 містить помилку (FreeType) і буде видалено</translation>
    </message>
    <message>
        <source>Font %1  has invalid glyph %2 (charcode %3), discarding it</source>
        <translation type="obsolete">Шрифт %1 містить помилковий символ %2 (код символа %3) і буде видалено</translation>
    </message>
    <message>
        <source>extracting face %1 from font %2 (offset=%3, nTables=%4)</source>
        <translation>Екстракція типу %1 з шрифта %2 (offset=%3, nTables=%4)</translation>
    </message>
    <message>
        <source>memcpy header: %1 %2 %3</source>
        <translation>заголовок memcpy: %1 %2 %3</translation>
    </message>
    <message>
        <source>table &apos;%1&apos;</source>
        <translation>таблиця &apos;%1&apos;</translation>
    </message>
    <message>
        <source>memcpy table: %1 %2 %3</source>
        <translation>таблиця memcpy: %1 %2 %3</translation>
    </message>
    <message>
        <source>memcpy offset: %1 %2 %3</source>
        <translation>зміщення memcpy: %1 %2 %3</translation>
    </message>
    <message>
        <source>Scribus Development Version</source>
        <translation>Версія Scribus в стадії розробки</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source> mm</source>
        <translation> мм</translation>
    </message>
    <message>
        <source> in</source>
        <translation> д</translation>
    </message>
    <message>
        <source> p</source>
        <translation> п</translation>
    </message>
    <message>
        <source> cm</source>
        <translation> см</translation>
    </message>
    <message>
        <source>pt</source>
        <translation>тчк</translation>
    </message>
    <message>
        <source>mm</source>
        <translation>мм</translation>
    </message>
    <message>
        <source>in</source>
        <translation>д</translation>
    </message>
    <message>
        <source>p</source>
        <translation>п</translation>
    </message>
    <message>
        <source>cm</source>
        <translation>см</translation>
    </message>
    <message>
        <source>Points (pt)</source>
        <translation>Точки (тчк)</translation>
    </message>
    <message>
        <source>Millimeters (mm)</source>
        <translation>Мілліметри (мм)</translation>
    </message>
    <message>
        <source>Inches (in)</source>
        <translation>Дюйми (д)</translation>
    </message>
    <message>
        <source>Picas (p)</source>
        <translation>Піки (п)</translation>
    </message>
    <message>
        <source>Centimeters (cm)</source>
        <translation>Сентиметри (см)</translation>
    </message>
    <message>
        <source>File exists</source>
        <translation>Файл вже існує</translation>
    </message>
    <message>
        <source>&amp;Replace</source>
        <translation>&amp;Заміна</translation>
    </message>
    <message>
        <source>All</source>
        <translation>Всі</translation>
    </message>
    <message>
        <source>Document Template: </source>
        <translation>Шаблон документа: </translation>
    </message>
    <message>
        <source>Failed to open document.</source>
        <comment>python error</comment>
        <translation>Неможливо відчинити документ.</translation>
    </message>
    <message>
        <source>Failed to save document.</source>
        <comment>python error</comment>
        <translation>Неможливо записати документ.</translation>
    </message>
    <message>
        <source>Argument must be page item name, or PyCObject instance</source>
        <translation>Аргументом може бути ім&apos;я об&apos;єкта сторінки або примірник PyCObject</translation>
    </message>
    <message>
        <source>Property not found</source>
        <translation>Властивість не знайдено</translation>
    </message>
    <message>
        <source>Child not found</source>
        <translation>Дитячий об&apos;єкт не знайдено</translation>
    </message>
    <message>
        <source>Couldn&apos;t convert result type &apos;%1&apos;.</source>
        <translation>Неможливо конвертувати тип результату &apos;%1&apos;.</translation>
    </message>
    <message>
        <source>Property type &apos;%1&apos; not supported</source>
        <translation>Тип властивості &apos;%1&apos; не підтримується</translation>
    </message>
    <message>
        <source>Couldn&apos;t convert &apos;%1&apos; to property type &apos;%2&apos;</source>
        <translation>Неможливо конвертувати &apos;%1&apos; в тип властивості &apos;%2&apos;</translation>
    </message>
    <message>
        <source>Types matched, but setting property failed.</source>
        <translation>Типи співпадають, але установка властивості неможлива.</translation>
    </message>
    <message>
        <source>Unable to save pixmap</source>
        <comment>scripter error</comment>
        <translation>Неможливо записати зображення</translation>
    </message>
    <message>
        <source>An object with the requested name already exists.</source>
        <comment>python error</comment>
        <translation>Об&apos;єкт з таким іменем вже існує.</translation>
    </message>
    <message>
        <source>Point list must contain at least two points (four values).</source>
        <comment>python error</comment>
        <translation>Список точок повинен містити хоча б дві точки (чотири значення).</translation>
    </message>
    <message>
        <source>Point list must contain an even number of values.</source>
        <comment>python error</comment>
        <translation>Список точок повинен містити парну кількість значень.</translation>
    </message>
    <message>
        <source>Point list must contain at least three points (six values).</source>
        <comment>python error</comment>
        <translation>Список точок повинен містити хоча б три точки (шість значень).</translation>
    </message>
    <message>
        <source>Point list must contain at least four points (eight values).</source>
        <comment>python error</comment>
        <translation>Список точок повинен містити хоча б чотири точки (вісім значень).</translation>
    </message>
    <message>
        <source>Point list must have a multiple of six values.</source>
        <comment>python error</comment>
        <translation>Список точок повинен містити кількість значень, яка ділиться на шість.</translation>
    </message>
    <message>
        <source>Object not found.</source>
        <comment>python error</comment>
        <translation>Об&apos;єкт не знайдено.</translation>
    </message>
    <message>
        <source>Style not found.</source>
        <comment>python error</comment>
        <translation>Стиль не знайдено.</translation>
    </message>
    <message>
        <source>Cannot set style on a non-text frame.</source>
        <comment>python error</comment>
        <translation>Неможливо установити стиль в нетекстовій рамці.</translation>
    </message>
    <message>
        <source>Failed to save EPS.</source>
        <comment>python error</comment>
        <translation>Неможливо записати EPS.</translation>
    </message>
    <message>
        <source>Page number out of range.</source>
        <comment>python error</comment>
        <translation>Число сторінок виходить за допустимий діапазон.</translation>
    </message>
    <message>
        <source>argument is not list: must be list of float values.</source>
        <comment>python error</comment>
        <translation>аргумент не являється списком - повинен бути списком чисел з плаваючою комою.</translation>
    </message>
    <message>
        <source>argument contains non-numeric values: must be list of float values.</source>
        <comment>python error</comment>
        <translation>аргумент містить нечислові значення - повинен бути списком чисел з плаваючою комою.</translation>
    </message>
    <message>
        <source>argument contains no-numeric values: must be list of float values.</source>
        <comment>python error</comment>
        <translation>аргумент не містить числових значень - повинен бути списком чисел з плаваючою комою.</translation>
    </message>
    <message>
        <source>Line width out of bounds, must be 0 &lt;= line_width &lt;= 12.</source>
        <comment>python error</comment>
        <translation>Товщина лінії виходить за межі - повинна бути між 0 та 12.</translation>
    </message>
    <message>
        <source>Line shade out of bounds, must be 0 &lt;= shade &lt;= 100.</source>
        <comment>python error</comment>
        <translation>Тінь лінії виходить за межі - повинна бути від 0 до 100.</translation>
    </message>
    <message>
        <source>Fill shade out of bounds, must be 0 &lt;= shade &lt;= 100.</source>
        <comment>python error</comment>
        <translation>Заповнення тіні виходить за межі - повинне бути від 0 до 100.</translation>
    </message>
    <message>
        <source>Line style not found.</source>
        <comment>python error</comment>
        <translation>стиль лінії не знайдено.</translation>
    </message>
    <message>
        <source>Only text frames can be checked for overflowing</source>
        <comment>python error</comment>
        <translation>Лише текстові рамки можуть бути перевірені на переповнення</translation>
    </message>
    <message>
        <source>&amp;Script</source>
        <translation>С&amp;ценарій</translation>
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
raise a NoValidObjectError if it can&apos;t find anything to operate
on.
- Many functions will raise WrongFrameTypeError if you try to use them
on a frame type that they do not make sense with. For example, setting
the text color on a graphics frame doesn&apos;t make sense, and will result
in this exception being raised.
- Errors resulting from calls to the underlying Python API will be
passed through unaltered. As such, the list of exceptions thrown by
any function as provided here and in its docstring is incomplete.

Details of what exceptions each function may throw are provided on the
function&apos;s documentation, though as with most Python code this list
is not exhaustive due to exceptions from called functions.
</source>
        <translation>Модуль інтерфейса Пітона

Цей модуль являється інтерфейсом Пітона та Scribus. Він містить функції для керування scribus і для маніпуляції об&apos;єктами на канві. Кожна функція індивідуально описана внизу. 

Деякі загальні поняття для всього інтерфейсу.

Більшість функцій оперує на рамками. Рамки визначаються іменем, 
яке являється строковою величиною Пітона. Багато функцій приймають
необов&apos;язковий параметр (не ключове слово) імені рамки. Багато виключень
такоє є спільними для більшості функцій. Ці виключення не описуються окремо.
Багато функцій активують виключення NoDocOpenError, якщо їх застосувати
при відсутності активного документу.
- Якщо функції, яка вимагає ім&apos;я рамки, не задати цей параметр, то вона спробує
використати активну рамку, якщо така існує, або активує виключення 
NoValidObjectError, якщо вона не знайде об&apos;єкта над яким можна провести дії.
- Багато функцій активують виключення WrongFrameTypeError, якщо їх застосувати
на типові рамки для якого вони не підходять. Наприклад, установка кольору
тексту на рамці для зображень не має смислу і призведе до активації цього виключення.
- Помилки, які є результатом викликів стандартного програмного інтерфейсу Пітону
повертаються без змін. Тому список можливих виключень, який міститься в 
документації функції не може бути повним принципово.

Деталі виключень для кожної функції можна знайти в документації функції, хоча
цей список і не являється повним із-за особливостей виключень Пітона.</translation>
    </message>
    <message>
        <source> c</source>
        <translation>с</translation>
    </message>
    <message>
        <source>c</source>
        <translation>с</translation>
    </message>
    <message>
        <source>Cicero (c)</source>
        <translation>Сісеро (с)</translation>
    </message>
    <message>
        <source>Cannot group less than two items</source>
        <comment>python error</comment>
        <translation>Неможливо згрупувати менш ніж два об&apos;єкти</translation>
    </message>
    <message>
        <source>Can&apos;t group less than two items</source>
        <comment>python error</comment>
        <translation>Неможливо згрупувати менш ніж два об&apos;єкти</translation>
    </message>
    <message>
        <source>Need selection or argument list of items to group</source>
        <comment>python error</comment>
        <translation>Потрібний список аргументів чи об&apos;єктів для згрупування</translation>
    </message>
    <message>
        <source>The filename should not be empty string.</source>
        <comment>python error</comment>
        <translation>Ім&apos;я файла не повинне бути пустою строковою величиною.</translation>
    </message>
    <message>
        <source>Copy #%1 of </source>
        <translation>Копія №%1 з</translation>
    </message>
    <message>
        <source>Black</source>
        <translation>Чорний</translation>
    </message>
    <message>
        <source>Cyan</source>
        <translation>Салатовий</translation>
    </message>
    <message>
        <source>Magenta</source>
        <translation>Малиновий</translation>
    </message>
    <message>
        <source>Yellow</source>
        <translation>Жовтий</translation>
    </message>
    <message>
        <source>page</source>
        <comment>page export</comment>
        <translation>сторінка</translation>
    </message>
    <message>
        <source>Color Wheel</source>
        <translation>Колесо кольорів</translation>
    </message>
    <message>
        <source>Font Preview</source>
        <translation>Попередній перегляд шрифтів</translation>
    </message>
    <message>
        <source>My Plugin</source>
        <translation>Мій модуль</translation>
    </message>
    <message>
        <source>New From Template</source>
        <translation>Новий з шаблона</translation>
    </message>
    <message>
        <source>Export As Image</source>
        <translation type="obsolete">Експортувати, як зображення</translation>
    </message>
    <message>
        <source>PS/EPS Importer</source>
        <translation>ЕPS/PS імпортер</translation>
    </message>
    <message>
        <source>Save As Template</source>
        <translation>Записати як шаблон</translation>
    </message>
    <message>
        <source>Scripter</source>
        <translation>Сценарист</translation>
    </message>
    <message>
        <source>Short Words</source>
        <translation>Короткі слова</translation>
    </message>
    <message>
        <source>SVG Export</source>
        <translation>Експорт SVG</translation>
    </message>
    <message>
        <source>SVG Import</source>
        <translation>Імпорт SVG</translation>
    </message>
    <message>
        <source>OpenOffice.org Draw Importer</source>
        <translation>Імпортер OpenOffice.org Draw</translation>
    </message>
    <message>
        <source>Scribus crashes due to the following exception : %1</source>
        <translation>Scribus буде зачинено із-за помилки: %1</translation>
    </message>
    <message>
        <source>Creating Font Cache</source>
        <translation>Створення проміжного набору шрифтів</translation>
    </message>
    <message>
        <source>New Font found, checking...</source>
        <translation>Знайдено новий шрифт, перевірка...</translation>
    </message>
    <message>
        <source>Modified Font found, checking...</source>
        <translation>Знайдено змінений шрифт, перевірка...</translation>
    </message>
    <message>
        <source>Reading Font Cache</source>
        <translation>Зчитування проміжного набору шрифтів</translation>
    </message>
    <message>
        <source>Writing updated Font Cache</source>
        <translation>Запис поновленого проміжного набору шрифтів</translation>
    </message>
    <message>
        <source>Searching for Fonts</source>
        <translation>Пошук шрифтів</translation>
    </message>
    <message>
        <source>You are running a development version of Scribus 1.3.x. The document you are working with was created in Scribus 1.2.3 or lower. The process of saving will make this file unusable again in Scribus 1.2.3 unless you use File-&gt;Save As. Are you sure you wish to proceed with this operation?</source>
        <translation type="obsolete">Ви запустили версію Scribus 1.3.x, які знаходиться в стадії розробки. Документ з яким Ви працюєте було створено версією
Scribus 1.2.3 чи нижче. Процес запису зробить цей файл несумісним з версією 1.2.3. Ви справді бажаєте виконати цю операцію
чи може відміните її і запишете цей файл під іншим іменем?</translation>
    </message>
    <message>
        <source>The changes to your document have not been saved and you have requested to revert them. Do you wish to continue?</source>
        <translation>Зміни внесені в документ не були записані і Ви бажаєте їх відмінити. Ви хочете продовжити виконання цієї операції?</translation>
    </message>
    <message>
        <source>A file named &apos;%1&apos; already exists.&lt;br/&gt;Do you want to replace it with the file you are saving?</source>
        <translation>Файл з назвою &apos;%1&apos; вже існує.&lt;br/&gt;Ви бажаєте замінити його файлом, який Ви записуєте?</translation>
    </message>
    <message>
        <source>firstPageOrder is bigger than allowed.</source>
        <comment>python error</comment>
        <translation>firstPageOrder більше ніж дозволено.</translation>
    </message>
    <message>
        <source>Old .sla format support</source>
        <translation>Підтримка старого .sla формату</translation>
    </message>
    <message>
        <source>German (Trad.)</source>
        <translation>Німецька (Традиц.)</translation>
    </message>
    <message>
        <source>Exporting PostScript File</source>
        <translation>Експортування постскрипт файла</translation>
    </message>
    <message>
        <source>Printing File</source>
        <translation>Друк файла</translation>
    </message>
    <message>
        <source>&lt;p&gt;You are trying to import more pages than there are available in the current document counting from the active page.&lt;/p&gt;Choose one of the following:&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;b&gt;Create&lt;/b&gt; missing pages&lt;/li&gt;&lt;li&gt;&lt;b&gt;Import&lt;/b&gt; pages until the last page&lt;/li&gt;&lt;li&gt;&lt;b&gt;Cancel&lt;/b&gt;&lt;/li&gt;&lt;/ul&gt;</source>
        <translation>&lt;p&gt;Ви намагаєтеся імпортувати більше число сторінок ніж є доступним в активному документі рахуючи з активної сторінки.&lt;/p&gt;Виберіть варіант дії:&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;b&gt;Створити&lt;/b&gt; недостаючі сторінки&lt;/li&gt;&lt;li&gt;&lt;b&gt;Імпортувати&lt;/b&gt; сторінки до останньої існуючої сторінки&lt;/li&gt;&lt;li&gt;&lt;b&gt;Вихід&lt;/b&gt;&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
    <message>
        <source>C&amp;reate</source>
        <translation>С&amp;творити</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
    <message>
        <source>Thai</source>
        <translation>Таіландська</translation>
    </message>
    <message>
        <source>Barcode Generator</source>
        <translation>Генератор штрих-коду</translation>
    </message>
    <message>
        <source>OpenOffice.org Draw (*.sxd *.odg);;All Files (*)</source>
        <translation>OpenOffice.org Draw (*.sxd *.odg);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Word Documents</source>
        <translation>Документи MSWord</translation>
    </message>
    <message>
        <source>Palm PDB Documents</source>
        <comment>PDB Importer</comment>
        <translation>Документи Palm PDB</translation>
    </message>
    <message>
        <source>PDB_data</source>
        <comment>PDB Importer</comment>
        <translation>PDB_дані</translation>
    </message>
    <message>
        <source>PDB Import</source>
        <comment>PDB Importer</comment>
        <translation>Імпорт PDB</translation>
    </message>
    <message>
        <source>Could not open file %1</source>
        <comment>PDB Importer</comment>
        <translation>Неможливо відчинити файл %1</translation>
    </message>
    <message>
        <source>This file is not recognized as a PDB document propably. Please, report this as a bug if you are sure it is one.</source>
        <comment>PDB Importer</comment>
        <translation type="obsolete">Цей файл можливо не було розпізнано, як PDB документ. Будь-ласка повідомте розробників про помилку, якщо Ви впевнені у наявності проблеми.</translation>
    </message>
    <message>
        <source>Luxembourgish</source>
        <translation>Люксембурзька</translation>
    </message>
    <message>
        <source>Japanese</source>
        <translation>Японська</translation>
    </message>
    <message>
        <source>Font %1(%2) is broken</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Given master page name does not match any existing.</source>
        <comment>python error</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Arabic</source>
        <translation type="unfinished">Арабська</translation>
    </message>
    <message>
        <source>Dzongkha</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Estonian</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>font %1 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>size %1 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+style </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+color </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+underline </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>-underline </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+strikeout </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>-strikeout </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+shadow </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>-shadow </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+outline </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>-outline </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>-tracking </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+stretch </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>parent= %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Latin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Icelandic</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Norwegian (Bokm&#xc3;&#xa5;l)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Romanian</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Quarto</source>
        <translation type="unfinished">Кварто</translation>
    </message>
    <message>
        <source>Foolscap</source>
        <translation type="unfinished">Фулскап</translation>
    </message>
    <message>
        <source>Letter</source>
        <translation type="unfinished">Лист</translation>
    </message>
    <message>
        <source>Govt. Letter</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Legal</source>
        <translation type="unfinished">Юридичний</translation>
    </message>
    <message>
        <source>Ledger</source>
        <translation type="unfinished">Бухгалтерський</translation>
    </message>
    <message>
        <source>Executive</source>
        <translation type="unfinished">Виконавчий</translation>
    </message>
    <message>
        <source>Post</source>
        <translation type="unfinished">Поштовий</translation>
    </message>
    <message>
        <source>Crown</source>
        <translation type="unfinished">Королівський</translation>
    </message>
    <message>
        <source>Large Post</source>
        <translation type="unfinished">Великий поштовий</translation>
    </message>
    <message>
        <source>Demy</source>
        <translation type="unfinished">Демі</translation>
    </message>
    <message>
        <source>Medium</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Royal</source>
        <translation type="unfinished">Вінценосний</translation>
    </message>
    <message>
        <source>Elephant</source>
        <translation type="unfinished">Слоновий</translation>
    </message>
    <message>
        <source>Double Demy</source>
        <translation type="unfinished">Подвійний демі</translation>
    </message>
    <message>
        <source>Quad Demy</source>
        <translation type="unfinished">Четверний демі</translation>
    </message>
    <message>
        <source>STMT</source>
        <translation type="unfinished">STMT</translation>
    </message>
    <message>
        <source>A</source>
        <translation type="unfinished">A</translation>
    </message>
    <message>
        <source>B</source>
        <translation type="unfinished">B</translation>
    </message>
    <message>
        <source>C</source>
        <translation type="unfinished">С</translation>
    </message>
    <message>
        <source>D</source>
        <translation type="unfinished">D</translation>
    </message>
    <message>
        <source>E</source>
        <translation type="unfinished">E</translation>
    </message>
    <message>
        <source>%1 may be corrupted : missing resolution tags</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Font %1 has broken glyph %2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Transparency out of bounds, must be 0 &lt;= transparency &lt;= 1.</source>
        <comment>python error</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Blendmode out of bounds, must be 0 &lt;= blendmode &lt;= 15.</source>
        <comment>python error</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Scribus 1.2.x Support</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Scribus 1.3.4 Support</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This file is not recognized as a PDB document. Please, report this as a bug if you are sure it is one.</source>
        <comment>PDB Importer</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Cannot get number of lines of non-text frame.</source>
        <comment>python error</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>You are running a development version of Scribus 1.3.x. The document you are working with was created in Scribus 1.2.x.  Saving the current file under 1.3.x renders it unable to be edited in Scribus 1.2.x versions. To preserve the ability to edit in 1.2.x, save this file under a different name and further edit the newly named file and the original will be untouched. Are you sure you wish to proceed with this operation?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+tracking %1 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>+baseline %1 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Breton</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>English (American)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>%1 may be corrupted : missing or wrong resolution tags</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The Font(s):
%1 are not available.
They have been replaced by &quot;Courier&quot;
Therefore the image may be not correct</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>English (Australian)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Supported Formats (*.eps *.EPS *.epsi *.EPSI *.ps *.PS);;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>German (Swiss)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hebrew</source>
        <translation type="unfinished">Іврит</translation>
    </message>
    <message>
        <source>Scribus 1.3.0-&gt;1.3.3.7 Support</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>QTextEdit</name>
    <message>
        <source>Clear</source>
        <translation>Очистити</translation>
    </message>
    <message>
        <source>Select All</source>
        <translation>Вибрати все</translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation>&amp;Відмінити</translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation>&amp;Повторити</translation>
    </message>
    <message>
        <source>Cu&amp;t</source>
        <translation>&amp;Вирізати</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
</context>
<context>
    <name>QTitleBar</name>
    <message>
        <source>System Menu</source>
        <translation>Системне меню</translation>
    </message>
    <message>
        <source>Shade</source>
        <translation>Затінити</translation>
    </message>
    <message>
        <source>Unshade</source>
        <translation>Відтінити</translation>
    </message>
    <message>
        <source>Normalize</source>
        <translation>Нормальний розмір</translation>
    </message>
    <message>
        <source>Minimize</source>
        <translation>Згорнути до мінімуму</translation>
    </message>
    <message>
        <source>Maximize</source>
        <translation>Розгорнути до максимуму</translation>
    </message>
    <message>
        <source>Close</source>
        <translation>Зачинити</translation>
    </message>
</context>
<context>
    <name>QWorkspace</name>
    <message>
        <source>&amp;Restore</source>
        <translation>&amp;Відновити</translation>
    </message>
    <message>
        <source>&amp;Move</source>
        <translation>&amp;Перемістити</translation>
    </message>
    <message>
        <source>&amp;Size</source>
        <translation>&amp;Розмір</translation>
    </message>
    <message>
        <source>Mi&amp;nimize</source>
        <translation>Зверну&amp;ти</translation>
    </message>
    <message>
        <source>Ma&amp;ximize</source>
        <translation>Ма&amp;ксимальний розмір</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>Stay on &amp;Top</source>
        <translation>&amp;Залишатися поверх</translation>
    </message>
    <message>
        <source>Minimize</source>
        <translation>Звернути</translation>
    </message>
    <message>
        <source>Restore Down</source>
        <translation>Відновити вниз</translation>
    </message>
    <message>
        <source>Close</source>
        <translation>Зачинити</translation>
    </message>
    <message>
        <source>Sh&amp;ade</source>
        <translation>За&amp;тінити</translation>
    </message>
    <message>
        <source>%1 - [%2]</source>
        <translation>%1 - [%2]</translation>
    </message>
    <message>
        <source>&amp;Unshade</source>
        <translation>Відті&amp;нити</translation>
    </message>
</context>
<context>
    <name>ReformDoc</name>
    <message>
        <source>Document Setup</source>
        <translation>Установка опцій документа</translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation type="obsolete">Розмітка полів</translation>
    </message>
    <message>
        <source>&amp;Top:</source>
        <translation type="obsolete">&amp;Верх:</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation type="obsolete">&amp;Лівий край:</translation>
    </message>
    <message>
        <source>&amp;Bottom:</source>
        <translation type="obsolete">&amp;Низ:</translation>
    </message>
    <message>
        <source>&amp;Right:</source>
        <translation type="obsolete">&amp;Правий край:</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation type="obsolete">Розмір сторінки</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation type="obsolete">Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation type="obsolete">Горизонтальна</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation type="obsolete">&amp;Розмір:</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation type="obsolete">&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation type="obsolete">&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation type="obsolete">&amp;Висота:</translation>
    </message>
    <message>
        <source>&amp;Unit:</source>
        <translation type="obsolete">&amp;Одиниця виміру:</translation>
    </message>
    <message>
        <source>Autosave</source>
        <translation type="obsolete">Автоматичний запис</translation>
    </message>
    <message>
        <source>min</source>
        <translation type="obsolete">хв</translation>
    </message>
    <message>
        <source>&amp;Interval:</source>
        <translation type="obsolete">&amp;Інтервал:</translation>
    </message>
    <message>
        <source>Document</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>Document Information</source>
        <translation>Інформація про документ</translation>
    </message>
    <message>
        <source>Guides</source>
        <translation>Розмітка</translation>
    </message>
    <message>
        <source>Page Display</source>
        <translation type="obsolete">Показ сторінки</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation type="obsolete">Колір:</translation>
    </message>
    <message>
        <source>Display &amp;Unprintable Area in Margin Color</source>
        <translation type="obsolete">Виділити &amp;недрукуєму область кольором поля</translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation type="obsolete">Alt+U</translation>
    </message>
    <message>
        <source>Show Pictures</source>
        <translation type="obsolete">Показати зображення</translation>
    </message>
    <message>
        <source>Show Text Chains</source>
        <translation type="obsolete">Показати текстові ланцюги</translation>
    </message>
    <message>
        <source>Show Text Control Characters</source>
        <translation type="obsolete">Показати контрольні знаки тексту</translation>
    </message>
    <message>
        <source>Show Frames</source>
        <translation type="obsolete">Показати рамки</translation>
    </message>
    <message>
        <source>Display</source>
        <translation>Відображення</translation>
    </message>
    <message>
        <source>Typography</source>
        <translation>Типографія</translation>
    </message>
    <message>
        <source>Tools</source>
        <translation>Інструменти</translation>
    </message>
    <message>
        <source>Hyphenator</source>
        <translation>Переносник</translation>
    </message>
    <message>
        <source>Fonts</source>
        <translation>Шрифти</translation>
    </message>
    <message>
        <source>PDF Export</source>
        <translation>Експорт PDF</translation>
    </message>
    <message>
        <source>Document Item Attributes</source>
        <translation>Атрибути об&apos;єкта документа</translation>
    </message>
    <message>
        <source>Table of Contents and Indexes</source>
        <translation>Зміст та індекси</translation>
    </message>
    <message>
        <source>Color Management</source>
        <translation>Керування кольорами</translation>
    </message>
    <message>
        <source>Turns the display of frames on or off</source>
        <translation type="obsolete">Переключає показ рамок</translation>
    </message>
    <message>
        <source>Turns the display of pictures on or off</source>
        <translation type="obsolete">Переключає показ зображень</translation>
    </message>
    <message>
        <source>Color for paper</source>
        <translation type="obsolete">Колір паперу</translation>
    </message>
    <message>
        <source>Mask the area outside the margins in the margin color</source>
        <translation type="obsolete">Замаскувати область за полями кольором полів</translation>
    </message>
    <message>
        <source>Rulers relative to Page</source>
        <translation type="obsolete">Лінійки відносні до сторінки</translation>
    </message>
    <message>
        <source>Minimum Scratch Space</source>
        <translation type="obsolete">Мінімальний чорновик</translation>
    </message>
    <message>
        <source>Gaps between Pages</source>
        <translation type="obsolete">Проміжки між сторінками</translation>
    </message>
    <message>
        <source>Horizontal:</source>
        <translation type="obsolete">Горизонтальна:</translation>
    </message>
    <message>
        <source>Vertical:</source>
        <translation type="obsolete">Вертикальна:</translation>
    </message>
    <message>
        <source>Preflight Verifier</source>
        <translation>Передекспортна перевірка</translation>
    </message>
    <message>
        <source>Display non-printing characters such as paragraph markers in text frames</source>
        <translation type="obsolete">Показувати недруковані знаки, такі як маркери абзаців, в текстових рамках</translation>
    </message>
    <message>
        <source>Enable or disable the display of linked text frames.</source>
        <translation type="obsolete">Ввімкнути або вимкнути показ поєднаних текстових рамок.</translation>
    </message>
    <message>
        <source>Adjusting Colors</source>
        <translation>Налаштування кольорів</translation>
    </message>
    <message>
        <source>Apply size settings to all pages</source>
        <translation type="obsolete">Застосувати установки розміру до всіх сторінок</translation>
    </message>
    <message>
        <source>Sections</source>
        <translation>Розділи</translation>
    </message>
    <message>
        <source>Apply the page size changes to all existing pages in the document</source>
        <translation type="obsolete">Застосувати зміни розмірів сторінки до всіх існуючих сторінок документа</translation>
    </message>
</context>
<context>
    <name>RunScriptDialog</name>
    <message>
        <source>Python Scripts (*.py);; All Files (*)</source>
        <translation type="obsolete">Сценарії на Пітоні (*.py);; Всі файли (*)</translation>
    </message>
    <message>
        <source>Run as Extension Script</source>
        <comment>run script dialog</comment>
        <translation>Запустити, як зовнішній сценарій</translation>
    </message>
    <message>
        <source>Python Scripts (*.py *.PY);; All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMAlignSelect</name>
    <message>
        <source>P</source>
        <comment>P as in Parent</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Use parent style&apos;s alignment instead of overriding it</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMBase</name>
    <message>
        <source>Style Manager</source>
        <translation>Менеджер стилів</translation>
    </message>
    <message>
        <source>Column 1</source>
        <translation type="obsolete">Стовпець 1</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation type="obsolete">&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+А</translation>
    </message>
    <message>
        <source>C&amp;lone</source>
        <translation type="obsolete">К&amp;лонувати</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation type="obsolete">Alt+Л</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+В</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>Назва:</translation>
    </message>
    <message>
        <source>O&amp;K</source>
        <translation type="obsolete">Га&amp;разд</translation>
    </message>
    <message>
        <source>Alt+K</source>
        <translation type="obsolete">Alt+Г</translation>
    </message>
    <message>
        <source>A&amp;pply</source>
        <translation type="obsolete">&amp;Застосувати</translation>
    </message>
    <message>
        <source>Alt+P</source>
        <translation type="obsolete">Alt+З</translation>
    </message>
    <message>
        <source>Ca&amp;ncel</source>
        <translation type="obsolete">В&amp;ихід</translation>
    </message>
    <message>
        <source>Alt+N</source>
        <translation>Alt+И</translation>
    </message>
    <message>
        <source>&amp;Apply</source>
        <translation type="unfinished">&amp;Застосувати</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation type="unfinished">&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Clone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation type="unfinished">І&amp;мпортувати</translation>
    </message>
    <message>
        <source>Alt+I</source>
        <translation type="unfinished">Alt+I</translation>
    </message>
    <message>
        <source>Please select a unique name for the style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;&lt; &amp;Done</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Reset</source>
        <translation type="unfinished">&amp;Перезавантажити</translation>
    </message>
    <message>
        <source>Alt+R</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMCStylePage</name>
    <message>
        <source> pt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source> %</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Parent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Parent style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Font face</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Font size</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Tracking</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Baseline offset</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Horizontal scaling</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Vertical scaling</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Language</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fill color</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fill shade</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Stroke color</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Stroke shade</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shade</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMCharacterStyle</name>
    <message>
        <source>Properties</source>
        <translation type="unfinished">Властивості</translation>
    </message>
    <message>
        <source>Character Styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Character Style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>New Style</source>
        <translation type="unfinished">Новий стиль</translation>
    </message>
    <message>
        <source>Clone of %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>%1 (%2)</source>
        <comment>This for unique name when creating a new character style. %1 will be the name of the style and %2 will be a number forming a style name like: New Style (2)</comment>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMColorCombo</name>
    <message>
        <source>Use Parent Value</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMFontComboH</name>
    <message>
        <source>Use Parent Font</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMLineStyle</name>
    <message>
        <source>Properties</source>
        <translation>Властивості</translation>
    </message>
    <message>
        <source>Lines</source>
        <translation type="obsolete">Лінії</translation>
    </message>
    <message>
        <source>Line Styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line Style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>New Style</source>
        <translation type="unfinished">Новий стиль</translation>
    </message>
    <message>
        <source>Clone of %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>%1 (%2)</source>
        <comment>This for unique name when creating a new character style. %1 will be the name of the style and %2 will be a number forming a style name like: New Style (2)</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source> pt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Solid Line</source>
        <translation type="unfinished">Суцільна лінія</translation>
    </message>
    <message>
        <source>Dashed Line</source>
        <translation type="unfinished">Переривчаста лінія</translation>
    </message>
    <message>
        <source>Dotted Line</source>
        <translation type="unfinished">Лінія з точок</translation>
    </message>
    <message>
        <source>Dash Dot Line</source>
        <translation type="unfinished">Переривчасто точкова лінія</translation>
    </message>
    <message>
        <source>Dash Dot Dot Line</source>
        <translation type="unfinished">Риска-точка-точка лінія</translation>
    </message>
    <message>
        <source> pt </source>
        <translation type="unfinished"> тчк </translation>
    </message>
</context>
<context>
    <name>SMPStyleWidget</name>
    <message>
        <source>Fixed Linespacing</source>
        <translation type="unfinished">Фіксований міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Automatic Linespacing</source>
        <translation type="unfinished">Автоматичний міжрядковий проміжок</translation>
    </message>
    <message>
        <source>Align to Baseline Grid</source>
        <translation type="unfinished">Вирівняти по базовій сітці</translation>
    </message>
    <message>
        <source> pt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Parent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Distances and Alignment</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Drop Caps</source>
        <translation type="unfinished">Буквиця</translation>
    </message>
    <message>
        <source>Tabulators and Indentation</source>
        <translation type="unfinished">Табулятори та відступи</translation>
    </message>
    <message>
        <source>Properties</source>
        <translation type="unfinished">Властивості</translation>
    </message>
    <message>
        <source>Character Style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Lines:</source>
        <translation type="unfinished">&amp;Лінії:</translation>
    </message>
    <message>
        <source>Distance from Text:</source>
        <translation type="unfinished">Відстань від тексту:</translation>
    </message>
    <message>
        <source>Based on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Parent style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line spacing mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Line spacing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Space above</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Space below</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enable or disable drop cap</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Drop cap lines</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Drop cap offset</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alignment</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>First line indent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Left indent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Right indent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Tabulators</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMParagraphStyle</name>
    <message>
        <source>Paragraph Styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Paragraph Style</source>
        <translation type="unfinished">Стиль абзацу</translation>
    </message>
    <message>
        <source>New Style</source>
        <translation type="unfinished">Новий стиль</translation>
    </message>
    <message>
        <source>Clone of %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>%1 (%2)</source>
        <comment>This for unique name when creating a new character style. %1 will be the name of the style and %2 will be a number forming a style name like: New Style (2)</comment>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMReplaceDia</name>
    <message>
        <source>Remove</source>
        <translation type="unfinished">Видалити</translation>
    </message>
    <message>
        <source>Replace with</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMReplaceDiaBase</name>
    <message>
        <source>Delete Styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished">&amp;Гаразд</translation>
    </message>
    <message>
        <source>Ca&amp;ncel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
    <message>
        <source>Alt+N</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMRowWidget</name>
    <message>
        <source>No Style</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMScComboBox</name>
    <message>
        <source>Use Parent Value</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMShadeButton</name>
    <message>
        <source>Use Parent Value</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMStyleSelect</name>
    <message>
        <source>P</source>
        <comment>P as in Parent</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Use parent style&apos;s effects instead of overriding them</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SMTabruler</name>
    <message>
        <source> Parent Tabs </source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SToolBAlign</name>
    <message>
        <source>Style of current paragraph</source>
        <translation>Стиль активного абзацу</translation>
    </message>
    <message>
        <source>Style Settings</source>
        <translation>Установки стилю</translation>
    </message>
</context>
<context>
    <name>SToolBColorF</name>
    <message>
        <source>Color of text fill</source>
        <translation>Колір заповнення тексту</translation>
    </message>
    <message>
        <source>Saturation of color of text fill</source>
        <translation>Насиченість кольору заповнення тексту</translation>
    </message>
    <message>
        <source>Fill Color Settings</source>
        <translation>Установки кольору заповнення</translation>
    </message>
</context>
<context>
    <name>SToolBColorS</name>
    <message>
        <source>Color of text stroke</source>
        <translation>Колір силуетів тексту</translation>
    </message>
    <message>
        <source>Saturation of color of text stroke</source>
        <translation>Насиченість кольору силуетів тексту</translation>
    </message>
    <message>
        <source>Stroke Color Settings</source>
        <translation>Установки кольору контурів</translation>
    </message>
</context>
<context>
    <name>SToolBFont</name>
    <message>
        <source> pt</source>
        <translation>тчк</translation>
    </message>
    <message>
        <source> %</source>
        <translation>%</translation>
    </message>
    <message>
        <source>Font of selected text</source>
        <translation>Шрифт вибраного тексту</translation>
    </message>
    <message>
        <source>Font Size</source>
        <translation>Розмір шрифта</translation>
    </message>
    <message>
        <source>Scaling width of characters</source>
        <translation>Масштабування ширини знаків</translation>
    </message>
    <message>
        <source>Font Settings</source>
        <translation>Установки шрифтів</translation>
    </message>
    <message>
        <source>Scaling height of characters</source>
        <translation>Масштабування висоти знаків</translation>
    </message>
</context>
<context>
    <name>SToolBStyle</name>
    <message>
        <source>Character Settings</source>
        <translation>Установки текстових символів</translation>
    </message>
    <message>
        <source>Manual Tracking</source>
        <translation>Слідкування вручну</translation>
    </message>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
</context>
<context>
    <name>SVGExportPlugin</name>
    <message>
        <source>Save Page as &amp;SVG...</source>
        <translation type="obsolete">Записати сторінку, як SVG з&amp;ображення...</translation>
    </message>
    <message>
        <source>Exports SVG Files</source>
        <translation>Експорт SVG файлів</translation>
    </message>
    <message>
        <source>Exports the current page into an SVG file.</source>
        <translation>Експортувати активну сторінку в SVG файл.</translation>
    </message>
    <message>
        <source>Save as &amp;SVG...</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SVGImportPlugin</name>
    <message>
        <source>Import &amp;SVG...</source>
        <translation>Імпортувати  SVG зображ&amp;ення...</translation>
    </message>
    <message>
        <source>Imports SVG Files</source>
        <translation>Імпорт SVG файлів</translation>
    </message>
    <message>
        <source>Imports most SVG files into the current document,
converting their vector data into Scribus objects.</source>
        <translation>Імпортує більшість SVG файлів в активний документ,
конвертуючи їхні векторні дані в об&apos;єкти Scribus.</translation>
    </message>
    <message>
        <source>Scalable Vector Graphics</source>
        <translation>Масштабована векторна графіка</translation>
    </message>
    <message>
        <source>SVG file contains some unsupported features</source>
        <translation>SVG файл містить деякі несумісні дані</translation>
    </message>
</context>
<context>
    <name>SVGPlug</name>
    <message>
        <source>Group%1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SWDialog</name>
    <message>
        <source>Short Words</source>
        <comment>short words plugin</comment>
        <translation>Модуль &quot;короткі слова&quot;</translation>
    </message>
    <message>
        <source>Apply unbreakable space on:</source>
        <comment>short words plugin</comment>
        <translation>Вставити нерозбиваємий інтервал в:</translation>
    </message>
    <message>
        <source>&amp;Selected frames</source>
        <comment>short words plugin</comment>
        <translation>&amp;Вибрані рамки</translation>
    </message>
    <message>
        <source>Active &amp;page</source>
        <comment>short words plugin</comment>
        <translation>Активна &amp;сторінка</translation>
    </message>
    <message>
        <source>&amp;All items</source>
        <comment>short words plugin</comment>
        <translation>Всі &amp;Об&apos;єкти</translation>
    </message>
    <message>
        <source>Only selected frames processed.</source>
        <comment>short words plugin</comment>
        <translation>Обробляються лише вибрані рамки.</translation>
    </message>
    <message>
        <source>Only actual page processed.</source>
        <comment>short words plugin</comment>
        <translation>Обробляється лише активна сторінка.</translation>
    </message>
    <message>
        <source>All items in document processed.</source>
        <comment>short words plugin</comment>
        <translation>Обробляються всі об&apos;єкти в документі.</translation>
    </message>
</context>
<context>
    <name>SWPrefsGui</name>
    <message>
        <source>User settings</source>
        <translation>Установки користувача</translation>
    </message>
    <message>
        <source>System wide configuration</source>
        <translation>Системна конфігурація</translation>
    </message>
    <message>
        <source>&amp;Save</source>
        <translation>&amp;Записати</translation>
    </message>
    <message>
        <source>&amp;Reset</source>
        <translation>&amp;Перезавантажити</translation>
    </message>
    <message>
        <source>Save user configuration</source>
        <translation>Записати конфігурацію користувача</translation>
    </message>
    <message>
        <source>Reload system wide configuration and remove user defined one</source>
        <translation>Перезавантажити системну конфігурацію та видалити конфігурацію користувача</translation>
    </message>
    <message>
        <source>Edit custom configuration. If you save it, it will be used over system wide configuration</source>
        <translation>Редагувати нетипову конфігурацію. Якщо Ви її запишете, то вона буде використовуватися
замість системної конфігурації</translation>
    </message>
    <message>
        <source>Short Words</source>
        <translation>Короткі слова</translation>
    </message>
    <message>
        <source>User configuration exists elready. Do you really want to overwrite it?</source>
        <translation>Конфігурація користувача вже існує. Ви справді бажаєте її перезаписати?</translation>
    </message>
    <message>
        <source>Cannot write file %1.</source>
        <translation>Неможливо записати файл %1.</translation>
    </message>
    <message>
        <source>User settings saved</source>
        <translation>Установки користувача записано</translation>
    </message>
    <message>
        <source>System wide configuration reloaded</source>
        <translation>Системна конфігурація перезавантажена</translation>
    </message>
    <message>
        <source>Cannot open file %1</source>
        <translation>Неможливо відчинити файл %1</translation>
    </message>
</context>
<context>
    <name>SaveAsTemplatePlugin</name>
    <message>
        <source>Save as &amp;Template...</source>
        <translation>Записати як ша&amp;блон...</translation>
    </message>
    <message>
        <source>Save a document as a template</source>
        <translation>Записати документ як шаблон</translation>
    </message>
    <message>
        <source>Save a document as a template. Good way to ease the initial work for documents with a constant look</source>
        <translation>Записати документ, як шаблон. Гарний метод для полегшення роботи по наданню документам однакового вигляду</translation>
    </message>
</context>
<context>
    <name>ScGTFileDialog</name>
    <message>
        <source>Select a file to import</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Append</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show options</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ScInputDialog</name>
    <message>
        <source>Input Dialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>InputDialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished">&amp;Гаразд</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished">В&amp;ихід</translation>
    </message>
</context>
<context>
    <name>ScPlugin</name>
    <message>
        <source>Persistent</source>
        <comment>plugin manager plugin type</comment>
        <translation>Постійний</translation>
    </message>
    <message>
        <source>Action</source>
        <comment>plugin manager plugin type</comment>
        <translation>Дія</translation>
    </message>
    <message>
        <source>Load/Save/Import/Export</source>
        <translation>Завантажити/Записати/Імпортувати/Експортувати</translation>
    </message>
    <message>
        <source>Unknown</source>
        <translation>Невідомий</translation>
    </message>
</context>
<context>
    <name>ScProgressBar</name>
    <message>
        <source>%1 of %2</source>
        <translation type="unfinished">%1 з %2</translation>
    </message>
</context>
<context>
    <name>ScToolBar</name>
    <message>
        <source>Top</source>
        <translation></translation>
    </message>
    <message>
        <source>Right</source>
        <translation>Правий край</translation>
    </message>
    <message>
        <source>Bottom</source>
        <translation></translation>
    </message>
    <message>
        <source>Left</source>
        <translation>Лівий край</translation>
    </message>
    <message>
        <source>Allow Docking To...</source>
        <translation>Дозволити приєднання до...</translation>
    </message>
    <message>
        <source>Horizontal</source>
        <translation>Горизонтально</translation>
    </message>
    <message>
        <source>Vertical</source>
        <translation>Вертикально</translation>
    </message>
    <message>
        <source>Floating Orientation...</source>
        <translation>Плаваюче розміщення...</translation>
    </message>
</context>
<context>
    <name>ScWinPrint</name>
    <message>
        <source>Printing...</source>
        <translation>Друкування...</translation>
    </message>
</context>
<context>
    <name>ScriXmlDoc</name>
    <message>
        <source>Copy #%1 of </source>
        <translation type="obsolete">Копія №%1 з </translation>
    </message>
    <message>
        <source>Background</source>
        <translation type="obsolete">Фон</translation>
    </message>
</context>
<context>
    <name>Scribus12Format</name>
    <message>
        <source>Scribus 1.2.x Document</source>
        <translation type="unfinished">Документ Scribus версій 1.2.x</translation>
    </message>
    <message>
        <source>Background</source>
        <translation type="unfinished">Фон</translation>
    </message>
    <message>
        <source>Copy #%1 of </source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Scribus134Format</name>
    <message>
        <source>Scribus 1.3.4 Document</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Copy #%1 of </source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Scribus13Format</name>
    <message>
        <source>Copy #%1 of </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Scribus 1.3.0-&gt;1.3.3.7 Document</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ScribusColorList</name>
    <message>
        <source>Document Colors</source>
        <translation type="obsolete">Кольори документу</translation>
    </message>
</context>
<context>
    <name>ScribusCore</name>
    <message>
        <source>Initializing Plugins</source>
        <translation type="unfinished">Ініціалізація модулів</translation>
    </message>
    <message>
        <source>Initializing Keyboard Shortcuts</source>
        <translation type="unfinished">Ініціалізація гарячих клавіш</translation>
    </message>
    <message>
        <source>Reading Preferences</source>
        <translation type="unfinished">Зчитування установок</translation>
    </message>
    <message>
        <source>Reading ICC Profiles</source>
        <translation type="unfinished">Зчитування ICC профілів</translation>
    </message>
    <message>
        <source>Searching for Fonts</source>
        <translation type="unfinished">Пошук шрифтів</translation>
    </message>
    <message>
        <source>There are no fonts found on your system.</source>
        <translation type="unfinished">На вашій системі не знайдено жодного шрифта.</translation>
    </message>
    <message>
        <source>Exiting now.</source>
        <translation type="unfinished">Терміновий вихід.</translation>
    </message>
    <message>
        <source>Fatal Error</source>
        <translation type="unfinished">Фатальна помилка</translation>
    </message>
    <message>
        <source>Font System Initialized</source>
        <translation type="unfinished">Шрифтова система ініціалізована</translation>
    </message>
</context>
<context>
    <name>ScribusDoc</name>
    <message>
        <source>Document</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>Background</source>
        <translation>Фон</translation>
    </message>
    <message>
        <source>New Layer</source>
        <translation>Новий план</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайний</translation>
    </message>
    <message>
        <source>Do you really want to clear all your text?</source>
        <translation>Ви справді бажаєте очистити весь Ваш текст?</translation>
    </message>
    <message>
        <source>Cannot Delete In-Use Item</source>
        <translation>Неможливо видалити об&apos;єкт під час його використання</translation>
    </message>
    <message>
        <source>The item %1 is currently being edited by Story Editor. The delete operation will be cancelled</source>
        <translation>Об&apos;єкт %1 в даний час редагується в редакторі тексту. Операція видалення буде відмінена</translation>
    </message>
    <message>
        <source>Some objects are locked.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Unlock All</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Skip locked objects</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>An error occurred while opening ICC profiles, color management is not enabled.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Number of copies: %1
Horizontal shift: %2
Vertical shift: %3</source>
        <translation type="unfinished">Число копій: %1(new line)
Горизонтальний зсув: %2(new line)
Вертикальний зсув: %3</translation>
    </message>
    <message>
        <source>Number of copies: %1
Horizontal gap: %2
Vertical gap: %3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Adjusting Colors</source>
        <translation type="unfinished">Налаштування кольорів</translation>
    </message>
    <message>
        <source>Default Paragraph Style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Default Character Style</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ScribusMainWindow</name>
    <message>
        <source>Initializing Plugins</source>
        <translation type="obsolete">Ініціалізація модулів</translation>
    </message>
    <message>
        <source>Initializing Keyboard Shortcuts</source>
        <translation type="obsolete">Ініціалізація гарячих клавіш</translation>
    </message>
    <message>
        <source>Reading Preferences</source>
        <translation type="obsolete">Зчитування установок</translation>
    </message>
    <message>
        <source>Initializing Story Editor</source>
        <translation>Ініціалізація текстового редактора</translation>
    </message>
    <message>
        <source>Reading ICC Profiles</source>
        <translation type="obsolete">Зчитування ICC профілів</translation>
    </message>
    <message>
        <source>Initializing Hyphenator</source>
        <translation>Ініціалізація системи переносів</translation>
    </message>
    <message>
        <source>Reading Scrapbook</source>
        <translation>Зчитування чорновика</translation>
    </message>
    <message>
        <source>Setting up Shortcuts</source>
        <translation>Установка гарячих клавіш</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Edit</source>
        <translation>Редагувати</translation>
    </message>
    <message>
        <source>Searching for Fonts</source>
        <translation type="obsolete">Пошук шрифтів</translation>
    </message>
    <message>
        <source>There are no fonts found on your system.</source>
        <translation type="obsolete">На вашій системі не знайдено жодного шрифта.</translation>
    </message>
    <message>
        <source>Exiting now.</source>
        <translation type="obsolete">Терміновий вихід.</translation>
    </message>
    <message>
        <source>Fatal Error</source>
        <translation>Фатальна помилка</translation>
    </message>
    <message>
        <source>Font System Initialized</source>
        <translation type="obsolete">Шрифтова система ініціалізована</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <source>Open &amp;Recent</source>
        <translation>Відчинити &amp;недавно редагований документ</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
    <message>
        <source>&amp;Export</source>
        <translation>&amp;Експортувати</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>St&amp;yle</source>
        <translation>&amp;Стиль</translation>
    </message>
    <message>
        <source>&amp;Color</source>
        <translation>&amp;Колір</translation>
    </message>
    <message>
        <source>&amp;Size</source>
        <translation>&amp;Розмір</translation>
    </message>
    <message>
        <source>&amp;Shade</source>
        <translation>&amp;Тінь</translation>
    </message>
    <message>
        <source>&amp;Font</source>
        <translation>&amp;Шрифт</translation>
    </message>
    <message>
        <source>&amp;Effects</source>
        <translation>&amp;Ефекти</translation>
    </message>
    <message>
        <source>&amp;Item</source>
        <translation>&amp;Об&apos;єкт</translation>
    </message>
    <message>
        <source>Preview Settings</source>
        <translation>Установки попереднього перегляду перед друком</translation>
    </message>
    <message>
        <source>Level</source>
        <translation>План</translation>
    </message>
    <message>
        <source>Send to La&amp;yer</source>
        <translation>Перемістити на &amp;план</translation>
    </message>
    <message>
        <source>&amp;PDF Options</source>
        <translation>&amp;Установки PDF</translation>
    </message>
    <message>
        <source>&amp;Shape</source>
        <translation>Геометрична &amp;Фігура</translation>
    </message>
    <message>
        <source>C&amp;onvert To</source>
        <translation>К&amp;онвертувати в</translation>
    </message>
    <message>
        <source>I&amp;nsert</source>
        <translation>&amp;Вставити</translation>
    </message>
    <message>
        <source>Character</source>
        <translation>Символ</translation>
    </message>
    <message>
        <source>Quote</source>
        <translation>Цитата</translation>
    </message>
    <message>
        <source>Space</source>
        <translation>Проміжок</translation>
    </message>
    <message>
        <source>&amp;Page</source>
        <translation>С&amp;торінка</translation>
    </message>
    <message>
        <source>&amp;View</source>
        <translation>&amp;Вид</translation>
    </message>
    <message>
        <source>E&amp;xtras</source>
        <translation>&amp;Додатки</translation>
    </message>
    <message>
        <source>&amp;Windows</source>
        <translation>Ві&amp;кна</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>До&amp;помога</translation>
    </message>
    <message>
        <source>&amp;Alignment</source>
        <translation>Ви&amp;рівнювання</translation>
    </message>
    <message>
        <source>Ready</source>
        <translation>Готовий</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Importing Pages...</source>
        <translation>Імпортування Сторінок...</translation>
    </message>
    <message>
        <source>Import Page(s)</source>
        <translation>Імпортувати сторінку(и)</translation>
    </message>
    <message>
        <source>Import done</source>
        <translation>Імпортування закінчено</translation>
    </message>
    <message>
        <source>Found nothing to import</source>
        <translation>Не знаходжу, що імпортувати</translation>
    </message>
    <message>
        <source>File %1 is not in an acceptable format</source>
        <translation>Файл %1 - в форматі, що не підтримується</translation>
    </message>
    <message>
        <source>Loading...</source>
        <translation>Завантаження...</translation>
    </message>
    <message>
        <source>PostScript</source>
        <translation>Постскрипт</translation>
    </message>
    <message>
        <source>Some ICC profiles used by this document are not installed:</source>
        <translation>Деякі кольорові профілі, використані в цьому документі, не інстальовано:</translation>
    </message>
    <message>
        <source> was replaced by: </source>
        <translation>був замінений на:</translation>
    </message>
    <message>
        <source>(converted)</source>
        <translation>(конвертовано)</translation>
    </message>
    <message>
        <source>All Supported Formats</source>
        <translation type="obsolete">Всі формати, що підтримуються</translation>
    </message>
    <message>
        <source>All Files (*)</source>
        <translation type="obsolete">Всі файли (*)</translation>
    </message>
    <message>
        <source>Cannot write the file: 
%1</source>
        <translation>Неможливо записати файл: 
%1</translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *scd.gz);;All Files (*)</source>
        <translation type="obsolete">Документи (*.sla *.sla.gz *.scd *scd.gz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;All Files (*)</source>
        <translation type="obsolete">Документи (*.sla *.scd);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Save As</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>Saving...</source>
        <translation>Запис...</translation>
    </message>
    <message>
        <source>Scribus has detected some errors. Consider using the Preflight Verifier to correct them</source>
        <translation>Scribus знайшов помилки. Спробуйте використати передекспортну перевірку для їх виправлення</translation>
    </message>
    <message>
        <source>&amp;Ignore</source>
        <translation>&amp;Ігнорувати</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Аварійний вихід</translation>
    </message>
    <message>
        <source>Printing...</source>
        <translation>Друк...</translation>
    </message>
    <message>
        <source>Document</source>
        <translation>Документ</translation>
    </message>
    <message>
        <source>Printing failed!</source>
        <translation>Друк не вдався!</translation>
    </message>
    <message>
        <source>Cannot Cut In-Use Item</source>
        <translation>Неможливо вирізати об&apos;єкт під час його використання</translation>
    </message>
    <message>
        <source>The item %1 is currently being edited by Story Editor. The cut operation will be cancelled</source>
        <translation>Об&apos;єкт %1 в даний час редагується в редакторі тексту. Операція вирізання буде відмінена</translation>
    </message>
    <message>
        <source>About Qt</source>
        <translation>Про Qt</translation>
    </message>
    <message>
        <source>Scribus Manual</source>
        <translation>Довідка Scribus</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>Text Files (*.txt);;All Files(*)</source>
        <translation>Текстові файли (*.txt);;Всі файли(*)</translation>
    </message>
    <message>
        <source>Normal</source>
        <translation type="obsolete">Звичайна</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>Назва:</translation>
    </message>
    <message>
        <source>Convert Page to Master Page</source>
        <translation>Конвертувати сторінку в майстер сторінку</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation>&amp;Розмір:</translation>
    </message>
    <message>
        <source>Size</source>
        <translation>Розмір</translation>
    </message>
    <message>
        <source>&amp;Shade:</source>
        <translation>&amp;Тінь:</translation>
    </message>
    <message>
        <source>Shade</source>
        <translation>Тінь</translation>
    </message>
    <message>
        <source>No Style</source>
        <translation>Стиль відсутній</translation>
    </message>
    <message>
        <source>The following programs are missing:</source>
        <translation>Відсутні такі програми:</translation>
    </message>
    <message>
        <source>Ghostscript : You cannot use EPS images or Print Preview</source>
        <translation>Ghostscript : Ви не можете використовувати EPS зображення або попередній перегляд перед друком</translation>
    </message>
    <message>
        <source>All</source>
        <translation>Все</translation>
    </message>
    <message>
        <source>Scribus detected some errors.
Consider using the Preflight Verifier  to correct them.</source>
        <translation>Scribus знайшов деякі помилки. Спробуйте використати
передекспортну перевірку для їх виправлення.</translation>
    </message>
    <message>
        <source>EPS Files (*.eps);;All Files (*)</source>
        <translation>Файли EPS (*.eps);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Detected some errors.
Consider using the Preflight Verifier to correct them</source>
        <translation>Знайдено деякі помилки. Спробуйте використати
передекспортну перевірку для їх виправлення</translation>
    </message>
    <message>
        <source>-Page%1</source>
        <translation>-Сторінка%1</translation>
    </message>
    <message>
        <source>Some objects are locked.</source>
        <translation>Деякі об&apos;єкти замкнені.</translation>
    </message>
    <message>
        <source>&amp;Lock All</source>
        <translation>&amp;Замкнути все</translation>
    </message>
    <message>
        <source>&amp;Unlock All</source>
        <translation>&amp;Розімкнути все</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Інформація</translation>
    </message>
    <message>
        <source>The program %1 is already running!</source>
        <translation>Програма %1 вже запущена!</translation>
    </message>
    <message>
        <source>The program %1 is missing!</source>
        <translation>Програма %1 відсутня!</translation>
    </message>
    <message>
        <source>The selected color does not exist in the document&apos;s color set. Please enter a name for this new color.</source>
        <translation>Вибраний колір відсутній в наборі кольорів документу. Будь ласка введіть назву цього нового кольору.</translation>
    </message>
    <message>
        <source>Color Not Found</source>
        <translation>Колір не знайдено</translation>
    </message>
    <message>
        <source>The name you have selected already exists. Please enter a different name for this new color.</source>
        <translation>Вибране ім&apos;я вже існує. Будь-ласка введіть інше ім&apos;я для цього нового кольору.</translation>
    </message>
    <message>
        <source>&amp;Level</source>
        <translation>&amp;План</translation>
    </message>
    <message>
        <source>Send to Layer</source>
        <translation>Перемістити на план</translation>
    </message>
    <message>
        <source>Previe&amp;w Settings</source>
        <translation>Установки попереднього перегляду перед д&amp;руком</translation>
    </message>
    <message>
        <source>&amp;Tools</source>
        <translation>&amp;Інструменти</translation>
    </message>
    <message>
        <source>X-Pos:</source>
        <translation>Поз. Х:</translation>
    </message>
    <message>
        <source>Y-Pos:</source>
        <translation>Поз. У:</translation>
    </message>
    <message>
        <source>Ghostscript : You cannot use EPS images or PostScript Print Preview</source>
        <translation>Ghostscript : Ви не можете використовувати EPS зображення або попередній перегляд постскрипту перед друком</translation>
    </message>
    <message>
        <source>Ghostscript is missing : Postscript Print Preview is not available</source>
        <translation>Ghostscript  відсутній: попередній перегляд постскрипту перед друком недоступний</translation>
    </message>
    <message>
        <source>Spaces &amp;&amp; Breaks</source>
        <translation type="obsolete">Проміжки та переноси</translation>
    </message>
    <message>
        <source>Ligature</source>
        <translation type="obsolete">Лігатура</translation>
    </message>
    <message>
        <source>New Master Page %1</source>
        <translation>Нова майстер сторінка %1</translation>
    </message>
    <message>
        <source>Number of copies: %1
Horizontal shift: %2
Vertical shift: %3</source>
        <translation type="obsolete">Число копій: %1(new line)
Горизонтальний зсув: %2(new line)
Вертикальний зсув: %3</translation>
    </message>
    <message>
        <source>Do you really want to replace your existing image?</source>
        <translation>Ви справді бажаєте замінити існуюче зображення?</translation>
    </message>
    <message>
        <source>Contents</source>
        <translation>Зміст</translation>
    </message>
    <message>
        <source>&amp;Character</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Quote</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>S&amp;paces &amp;&amp; Breaks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Liga&amp;ture</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Paste Recent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Updating Pictures</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Documents (*.sla);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Group%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Do you really want to clear all your text?</source>
        <translation type="unfinished">Ви справді бажаєте очистити весь Ваш текст?</translation>
    </message>
</context>
<context>
    <name>ScribusQApp</name>
    <message>
        <source>Invalid argument: </source>
        <translation>Невірний аргумент:</translation>
    </message>
    <message>
        <source>File %1 does not exist, aborting.</source>
        <translation>Файл %1 не існує, аварійний вихід.</translation>
    </message>
    <message>
        <source>Usage: scribus [option ... ] [file]</source>
        <translation>Використання: scribus [ключ ... ] [файл]</translation>
    </message>
    <message>
        <source>Options:</source>
        <translation>Установки:</translation>
    </message>
    <message>
        <source>Print help (this message) and exit</source>
        <translation>Надрукувати підказку (це повідомлення) та вийти</translation>
    </message>
    <message>
        <source>Uses xx as shortcut for a language, eg `en&apos; or `de&apos;</source>
        <translation>Використовує хх, як кодову назву мови, наприклад &apos;en&apos; або &apos;de&apos;</translation>
    </message>
    <message>
        <source>List the currently installed interface languages</source>
        <translation>Показати список доступних мов інтерфейса</translation>
    </message>
    <message>
        <source>Show information on the console when fonts are being loaded</source>
        <translation>Показати в терміналі інформацію про завантаження шрифтів</translation>
    </message>
    <message>
        <source>Do not show the splashscreen on startup</source>
        <translation>Не показувати стартову заставку під час запуску програми</translation>
    </message>
    <message>
        <source>Output version information and exit</source>
        <translation>Показати інформацію про версію та вийти</translation>
    </message>
    <message>
        <source>Use right to left dialog button ordering (eg. Cancel/No/Yes instead of Yes/No/Cancel)</source>
        <translation>Використовувати порядок кнопок в діалогових вікнах справа наліво (наприклад Вихід/Ні/Так замість Так/Ні/Вихід</translation>
    </message>
    <message>
        <source>filename</source>
        <translation>назва файла</translation>
    </message>
    <message>
        <source>Use filename as path for user given preferences</source>
        <translation>Використовувати назву файла, як шлях для установок користувача</translation>
    </message>
    <message>
        <source>Installed interface languages for Scribus are as follows:</source>
        <translation>Інстальовані мови інтерфейсу Scribus включають:</translation>
    </message>
    <message>
        <source>To override the default language choice:</source>
        <translation>Вибрати нестандартну мову:</translation>
    </message>
    <message>
        <source>scribus -l xx or scribus --lang xx, where xx is the language of choice.</source>
        <translation>scribus -l xx або scribus --lang xx, де xx - це код вибраної мови.</translation>
    </message>
    <message>
        <source>Scribus Version</source>
        <translation>Версія Scribus</translation>
    </message>
    <message>
        <source>Scribus, Open Source Desktop Publishing</source>
        <translation>Scribus, поліграфічне програмне забезпечення з відкритим кодом</translation>
    </message>
    <message>
        <source>Homepage</source>
        <translation>Домашня сторінка</translation>
    </message>
    <message>
        <source>Documentation</source>
        <translation>Документація</translation>
    </message>
    <message>
        <source>Wiki</source>
        <translation>Вікі</translation>
    </message>
    <message>
        <source>Issues</source>
        <translation>Проблеми</translation>
    </message>
    <message>
        <source>Stop the showing of the splashscreen on startup. Writes an empty file called .neversplash in ~/.scribus.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Download a file from the Scribus website and show the latest available version.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Display a console window</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show location ICC profile information on console while starting</source>
        <translation type="unfinished"></translation>
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
        <translation type="obsolete">План</translation>
    </message>
    <message>
        <source>Copy Here</source>
        <translation>Копіювати сюди</translation>
    </message>
    <message>
        <source>Move Here</source>
        <translation>Перемістити сюди</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
    <message>
        <source>Picture</source>
        <translation>Зображення</translation>
    </message>
    <message>
        <source>File: </source>
        <translation>Файл: </translation>
    </message>
    <message>
        <source>Original PPI: </source>
        <translation>Початкові ТНД: </translation>
    </message>
    <message>
        <source>Actual PPI: </source>
        <translation>Фактичні ТНД: </translation>
    </message>
    <message>
        <source>Linked Text</source>
        <translation>Зв&apos;язаний текст</translation>
    </message>
    <message>
        <source>Text Frame</source>
        <translation>Текстова рамка</translation>
    </message>
    <message>
        <source>Text on a Path</source>
        <translation>Текст на шляху</translation>
    </message>
    <message>
        <source>Paragraphs: </source>
        <translation>Абзаци: </translation>
    </message>
    <message>
        <source>Words: </source>
        <translation>Слова: </translation>
    </message>
    <message>
        <source>Chars: </source>
        <translation>Символи: </translation>
    </message>
    <message>
        <source>Print: </source>
        <translation>Друкувати: </translation>
    </message>
    <message>
        <source>Enabled</source>
        <translation>Ввімкнено</translation>
    </message>
    <message>
        <source>Disabled</source>
        <translation>Вимкнено</translation>
    </message>
    <message>
        <source>In&amp;fo</source>
        <translation>&amp;Інформація</translation>
    </message>
    <message>
        <source>Preview Settings</source>
        <translation>Установки попереднього перегляду перед друком</translation>
    </message>
    <message>
        <source>&amp;PDF Options</source>
        <translation>&amp;Установки PDF</translation>
    </message>
    <message>
        <source>Send to La&amp;yer</source>
        <translation>Перемістити на &amp;план</translation>
    </message>
    <message>
        <source>Le&amp;vel</source>
        <translation>Пла&amp;н</translation>
    </message>
    <message>
        <source>Conve&amp;rt to</source>
        <translation>&amp;Конвертувати в</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Linking Text Frames</source>
        <translation>Установка зв&apos;язку між текстовими рамками</translation>
    </message>
    <message>
        <source>You are trying to link to a filled frame, or a frame to itself.</source>
        <translation>Ви намагаєтеся установити зв&apos;язок до заповненої рамки або до цієї ж рамки.</translation>
    </message>
    <message>
        <source>Page %1 to %2</source>
        <translation>Від сторінки %1 до %2</translation>
    </message>
    <message>
        <source>Cannot Convert In-Use Item</source>
        <translation>Неможливо конвертувати об&apos;єкт під час його використання</translation>
    </message>
    <message>
        <source>The item %1 is currently being edited by Story Editor. The convert to outlines operation for this item will be skipped</source>
        <translation>Об&apos;єкт %1 в даний час редагується в редакторі тексту. Операція конвертування в контурні лінії буде пропущена</translation>
    </message>
    <message>
        <source>Colorspace: </source>
        <translation>Кольоровий простір: </translation>
    </message>
    <message>
        <source>Unknown</source>
        <translation>Невідомий</translation>
    </message>
    <message>
        <source>RGB</source>
        <translation>RGB</translation>
    </message>
    <message>
        <source>CMYK</source>
        <translation>CMYK</translation>
    </message>
    <message>
        <source>Grayscale</source>
        <translation>Відтінки сірого</translation>
    </message>
    <message>
        <source>Contents</source>
        <translation>Зміст</translation>
    </message>
    <message>
        <source>Paste Recent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Duotone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Lines: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Group%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enables the Preview Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Here you can select the visual appearance of the display
You can choose between normal and several color blindness forms</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal Vision</source>
        <translation type="obsolete">Нормальний зір</translation>
    </message>
    <message>
        <source>Protanopia (Red)</source>
        <translation type="obsolete">Протанопія (Червоний)</translation>
    </message>
    <message>
        <source>Deuteranopia (Green)</source>
        <translation type="obsolete">Дейтеранопія (Зелений)</translation>
    </message>
    <message>
        <source>Tritanopia (Blue)</source>
        <translation type="obsolete">Тританопія (Синій)</translation>
    </message>
    <message>
        <source>Full Color Blindness</source>
        <translation type="obsolete">Повний дальтонізм</translation>
    </message>
    <message>
        <source>Switches Color Management on or off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Preview Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CMS is active. Therefore the color display may not match the perception by visually impaired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enter Object Size</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ScribusWin</name>
    <message>
        <source>Document:</source>
        <translation>Документ:</translation>
    </message>
    <message>
        <source>has been changed since the last save.</source>
        <translation>був змінений з часу останнього запису.</translation>
    </message>
    <message>
        <source>&amp;Discard</source>
        <translation>За&amp;бути</translation>
    </message>
</context>
<context>
    <name>ScriptPlugin</name>
    <message>
        <source>Embedded Python scripting support.</source>
        <translation>Вбудована підтримка сценаріїв пітону.</translation>
    </message>
    <message>
        <source>Scripter</source>
        <translation>Сценарист</translation>
    </message>
</context>
<context>
    <name>ScripterCore</name>
    <message>
        <source>Script error</source>
        <translation>Помилка сценарія</translation>
    </message>
    <message>
        <source>If you are running an official script report it at &lt;a href=&quot;http://bugs.scribus.net&quot;&gt;bugs.scribus.net&lt;/a&gt; please.</source>
        <translation>Якщо ви використовуєте офіційний сценарій то, будь-ласка, повідомляйте про помилки на &lt;a href=&quot;http://bugs.scribus.net&quot;&gt;bugs.scribus.net&lt;/a&gt;.</translation>
    </message>
    <message>
        <source>This message is in your clipboard too. Use Ctrl+V to paste it into bug tracker.</source>
        <translation>Це повідомлення також розміщене в блоці копіювання. Використайте 
Ctrl-V для вставки його в систему обробітку програмних помилок.</translation>
    </message>
    <message>
        <source>Examine Script</source>
        <translation>Розглянути сценарій</translation>
    </message>
    <message>
        <source>There was an internal error while trying the command you entered. Details were printed to stderr. </source>
        <translation>Під час виконання введеної Вами команди була знайдена внутрішня помилка. Деталі будуть надруковані в стандартний вивід помилок. </translation>
    </message>
    <message>
        <source>Setting up the Python plugin failed. Error details were printed to stderr. </source>
        <translation>Активація модуля пітона не вдалася. Деталі помилки будуть надруковані в стандартний вивід помилок. </translation>
    </message>
    <message>
        <source>Python Scripts (*.py);;All Files (*)</source>
        <translation type="obsolete">Сценарії на Пітоні (*.py);; Всі файли (*)</translation>
    </message>
    <message>
        <source>Documentation for:</source>
        <translation>Документація для:</translation>
    </message>
    <message>
        <source>Script</source>
        <translation>Сценарій</translation>
    </message>
    <message>
        <source> doesn&apos;t contain any docstring!</source>
        <translation> не містить ніякого опису!</translation>
    </message>
    <message>
        <source>Python Scripts (*.py *.PY);;All Files (*)</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ScripterPrefsGui</name>
    <message>
        <source>Scripter Preferences</source>
        <translation>Установки сценариста</translation>
    </message>
    <message>
        <source>Enable Extension Scripts</source>
        <translation>Ввімкнути зовнішні сценарії</translation>
    </message>
    <message>
        <source>Extensions</source>
        <translation>Розширення</translation>
    </message>
    <message>
        <source>Console</source>
        <translation>Термінал</translation>
    </message>
    <message>
        <source>Startup Script:</source>
        <translation>Початковий сценарій:</translation>
    </message>
    <message>
        <source>Errors:</source>
        <comment>syntax highlighting</comment>
        <translation>Помилки:</translation>
    </message>
    <message>
        <source>Comments:</source>
        <comment>syntax highlighting</comment>
        <translation>Коментарії:</translation>
    </message>
    <message>
        <source>Keywords:</source>
        <comment>syntax highlighting</comment>
        <translation>Ключові слова:</translation>
    </message>
    <message>
        <source>Signs:</source>
        <comment>syntax highlighting</comment>
        <translation>Знаки:</translation>
    </message>
    <message>
        <source>Numbers:</source>
        <comment>syntax highlighting</comment>
        <translation>Числа:</translation>
    </message>
    <message>
        <source>Strings:</source>
        <comment>syntax highlighting</comment>
        <translation>Строкові величини:</translation>
    </message>
    <message>
        <source>Base Texts:</source>
        <comment>syntax highlighting</comment>
        <translation>Базові тексти:</translation>
    </message>
    <message>
        <source>Select Color</source>
        <translation>Вибрати колір</translation>
    </message>
    <message>
        <source>Change...</source>
        <translation>Змінити...</translation>
    </message>
    <message>
        <source>Locate Startup Script</source>
        <translation>Знайти початковий сценарій</translation>
    </message>
</context>
<context>
    <name>SeList</name>
    <message>
        <source>Show Page Previews</source>
        <translation>Попередній перегляд сторінок</translation>
    </message>
</context>
<context>
    <name>SearchReplace</name>
    <message>
        <source>Search/Replace</source>
        <translation>Пошук/Заміна</translation>
    </message>
    <message>
        <source>Search for:</source>
        <translation>Шукати:</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Текст</translation>
    </message>
    <message>
        <source>Paragraph Style</source>
        <translation>Стиль абзацу</translation>
    </message>
    <message>
        <source>Font</source>
        <translation>Шрифт</translation>
    </message>
    <message>
        <source>Font Size</source>
        <translation>Розмір шрифта</translation>
    </message>
    <message>
        <source>Font Effects</source>
        <translation>Ефекти шрифта</translation>
    </message>
    <message>
        <source>Fill Color</source>
        <translation>Колір заповнення</translation>
    </message>
    <message>
        <source>Fill Shade</source>
        <translation>Тінь заповнення</translation>
    </message>
    <message>
        <source>Stroke Color</source>
        <translation>Колір контура</translation>
    </message>
    <message>
        <source>Stroke Shade</source>
        <translation>Тінь контура</translation>
    </message>
    <message>
        <source> pt</source>
        <translation>тчк</translation>
    </message>
    <message>
        <source>Replace with:</source>
        <translation>Замінити на:</translation>
    </message>
    <message>
        <source>Search finished</source>
        <translation>Пошук закінчено</translation>
    </message>
    <message>
        <source>Left</source>
        <translation>Лівий край</translation>
    </message>
    <message>
        <source>Center</source>
        <translation>Центр</translation>
    </message>
    <message>
        <source>Right</source>
        <translation>Правий край</translation>
    </message>
    <message>
        <source>Block</source>
        <translation>Блок</translation>
    </message>
    <message>
        <source>Forced</source>
        <translation>Вимушене</translation>
    </message>
    <message>
        <source>&amp;Whole Word</source>
        <translation>&amp;Повне слово</translation>
    </message>
    <message>
        <source>&amp;Ignore Case</source>
        <translation>&amp;Ігнорувати регістр</translation>
    </message>
    <message>
        <source>&amp;Search</source>
        <translation>&amp;Пошук</translation>
    </message>
    <message>
        <source>&amp;Replace</source>
        <translation>&amp;Заміна</translation>
    </message>
    <message>
        <source>Replace &amp;All</source>
        <translation>Замінити &amp;всі</translation>
    </message>
    <message>
        <source>&amp;Close</source>
        <translation>&amp;Зачинити</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>Search finished, found %1 matches</source>
        <translation>Пошук завершено, знайдено %1 співпадіння</translation>
    </message>
</context>
<context>
    <name>SelectFields</name>
    <message>
        <source>Select Fields</source>
        <translation>Вибрати поля</translation>
    </message>
    <message>
        <source>Available Fields</source>
        <translation>Доступні поля</translation>
    </message>
    <message>
        <source>Selected Fields</source>
        <translation>Вибрані поля</translation>
    </message>
    <message>
        <source>&amp;&gt;&gt;</source>
        <translation>&amp;&gt;&gt;</translation>
    </message>
    <message>
        <source>&amp;&lt;&lt;</source>
        <translation>&amp;&lt;&lt;</translation>
    </message>
</context>
<context>
    <name>ShadeButton</name>
    <message>
        <source>Other...</source>
        <translation>Інші...</translation>
    </message>
    <message>
        <source>Shade</source>
        <translation>Тінь</translation>
    </message>
    <message>
        <source>&amp;Shade:</source>
        <translation>&amp;Тінь:</translation>
    </message>
</context>
<context>
    <name>ShadowValues</name>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
    <message>
        <source>X-Offset</source>
        <translation>Зміщення по осі Х</translation>
    </message>
    <message>
        <source>Y-Offset</source>
        <translation>Зміщення по осі У</translation>
    </message>
</context>
<context>
    <name>ShortWordsPlugin</name>
    <message>
        <source>Short &amp;Words...</source>
        <comment>short words plugin</comment>
        <translation>Короткі &amp;Слова...</translation>
    </message>
    <message>
        <source>Short Words</source>
        <translation>Короткі слова</translation>
    </message>
    <message>
        <source>Special plug-in for adding non-breaking spaces before or after so called short words. Available in the following languages: </source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ShortcutWidget</name>
    <message>
        <source>&amp;No Key</source>
        <translation type="unfinished">&amp;Без ключа</translation>
    </message>
    <message>
        <source>&amp;User Defined Key</source>
        <translation type="unfinished">Ключ визначений &amp;користувачем</translation>
    </message>
    <message>
        <source>ALT+SHIFT+T</source>
        <translation type="unfinished">ALT+SHIFT+T</translation>
    </message>
    <message>
        <source>Set &amp;Key</source>
        <translation type="unfinished">&amp;Установити ключ</translation>
    </message>
    <message>
        <source>Alt</source>
        <translation type="unfinished">Alt</translation>
    </message>
    <message>
        <source>Ctrl</source>
        <translation type="unfinished">Ctrl</translation>
    </message>
    <message>
        <source>Shift</source>
        <translation type="unfinished">Shift</translation>
    </message>
    <message>
        <source>Meta</source>
        <translation type="unfinished">Мета</translation>
    </message>
    <message>
        <source>Meta+</source>
        <translation type="unfinished">Мета+</translation>
    </message>
    <message>
        <source>Shift+</source>
        <translation type="unfinished">Shift+</translation>
    </message>
    <message>
        <source>Alt+</source>
        <translation type="unfinished">Alt+</translation>
    </message>
    <message>
        <source>Ctrl+</source>
        <translation type="unfinished">Ctrl+</translation>
    </message>
    <message>
        <source>No shortcut for the style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Style has user defined shortcut</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Assign a shortcut for the style</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SideBar</name>
    <message>
        <source>No Style</source>
        <translation>Стиль відсутній</translation>
    </message>
    <message>
        <source>Edit Styles...</source>
        <translation>Редагувати стилі...</translation>
    </message>
</context>
<context>
    <name>Spalette</name>
    <message>
        <source>No Style</source>
        <translation>Немає стилю</translation>
    </message>
</context>
<context>
    <name>StilFormate</name>
    <message>
        <source>Edit Styles</source>
        <translation>Редагування стилю</translation>
    </message>
    <message>
        <source>Copy of %1</source>
        <translation>Копія %1</translation>
    </message>
    <message>
        <source>New Style</source>
        <translation>Новий стиль</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)</source>
        <translation>Документи (*.sla *.sla.gz *.scd *.scd.gz);;Всі файли (*)</translation>
    </message>
    <message>
        <source>Documents (*.sla *.scd);;All Files (*)</source>
        <translation>Документи (*.sla *.scd);;Всі файли (*)</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>D&amp;uplicate</source>
        <translation>&amp;Дублювати</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation>І&amp;мпортувати</translation>
    </message>
</context>
<context>
    <name>StoryEditor</name>
    <message>
        <source>Story Editor</source>
        <translation>Редактор тексту</translation>
    </message>
    <message>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <source>Current Paragraph:</source>
        <translation>Активний абзац:</translation>
    </message>
    <message>
        <source>Words: </source>
        <translation>Слова:</translation>
    </message>
    <message>
        <source>Chars: </source>
        <translation>Символи:</translation>
    </message>
    <message>
        <source>Totals:</source>
        <translation>Сумми:</translation>
    </message>
    <message>
        <source>Paragraphs: </source>
        <translation>Абзаци:</translation>
    </message>
    <message>
        <source>Open</source>
        <translation>Відчинити</translation>
    </message>
    <message>
        <source>Text Files (*.txt);;All Files(*)</source>
        <translation>Текстові файли (*.txt);;Всі файли(*)</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation>Записати як</translation>
    </message>
    <message>
        <source>Do you want to save your changes?</source>
        <translation>Записати зміни?</translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation>&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Reload Text from Frame</source>
        <translation>&amp;Поновити текст з рамки</translation>
    </message>
    <message>
        <source>&amp;Save to File...</source>
        <translation>За&amp;писати в файл...</translation>
    </message>
    <message>
        <source>&amp;Load from File...</source>
        <translation>&amp;Завантажити з файла...</translation>
    </message>
    <message>
        <source>Save &amp;Document</source>
        <translation>Записати &amp;документ</translation>
    </message>
    <message>
        <source>&amp;Update Text Frame and Exit</source>
        <translation>Поно&amp;вити текстову рамку та вийти</translation>
    </message>
    <message>
        <source>&amp;Exit Without Updating Text Frame</source>
        <translation>Вийти &amp;без поновлення текстової рамки</translation>
    </message>
    <message>
        <source>Cu&amp;t</source>
        <translation>Ви&amp;різати</translation>
    </message>
    <message>
        <source>&amp;Copy</source>
        <translation>&amp;Скопіювати</translation>
    </message>
    <message>
        <source>&amp;Paste</source>
        <translation>&amp;Вклеїти</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>&amp;Update Text Frame</source>
        <translation>&amp;Поновити вміст текстової рамки</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation>&amp;Редагувати</translation>
    </message>
    <message>
        <source>Select &amp;All</source>
        <translation>Виді&amp;лити все</translation>
    </message>
    <message>
        <source>&amp;Edit Styles...</source>
        <translation>&amp;Редагувати стилі...</translation>
    </message>
    <message>
        <source>&amp;Search/Replace...</source>
        <translation>&amp;Пошук/Заміна...</translation>
    </message>
    <message>
        <source>&amp;Fonts Preview...</source>
        <translation>&amp;Попередній перегляд шрифтів...</translation>
    </message>
    <message>
        <source>&amp;Background...</source>
        <translation>&amp;Фон...</translation>
    </message>
    <message>
        <source>&amp;Display Font...</source>
        <translation>&amp;Екранний шрифт...</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>&amp;Установки</translation>
    </message>
    <message>
        <source>&amp;Smart text selection</source>
        <translation>&amp;Розумне виділення тексту</translation>
    </message>
    <message>
        <source>&amp;Insert Glyph...</source>
        <translation>Вставити &amp;Символ...</translation>
    </message>
    <message>
        <source>Clear All Text</source>
        <translation>Очистити весь текст</translation>
    </message>
    <message>
        <source>Story Editor - %1</source>
        <translation>Редактор тексту - %1</translation>
    </message>
    <message>
        <source>Do you really want to lose all your changes?</source>
        <translation>Ви справді бажаєте відмінити всі Ваші зміни?</translation>
    </message>
    <message>
        <source>Do you really want to clear all your text?</source>
        <translation>Ви справді бажаєте очистити весь Ваш текст?</translation>
    </message>
    <message>
        <source>&amp;Insert</source>
        <translation>&amp;Вставити</translation>
    </message>
    <message>
        <source>Character</source>
        <translation>Символ</translation>
    </message>
    <message>
        <source>Quote</source>
        <translation>Цитата</translation>
    </message>
    <message>
        <source>Spaces &amp;&amp; Breaks</source>
        <translation>Проміжки та переноси</translation>
    </message>
    <message>
        <source>Ligature</source>
        <translation>Лігатура</translation>
    </message>
    <message>
        <source>Space</source>
        <translation>Проміжок</translation>
    </message>
</context>
<context>
    <name>StrikeValues</name>
    <message>
        <source>Auto</source>
        <translation>Автоматична</translation>
    </message>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
    <message>
        <source>Displacement</source>
        <translation>Зміщення</translation>
    </message>
    <message>
        <source>Linewidth</source>
        <translation>Товщина лінії</translation>
    </message>
</context>
<context>
    <name>StyleManager</name>
    <message>
        <source>More than one item selected</source>
        <translation type="obsolete">Вибрано більш ніж один об&apos;єкт</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Reset</source>
        <translation type="unfinished">&amp;Перезавантажити</translation>
    </message>
    <message>
        <source>&amp;Apply</source>
        <translation type="unfinished">&amp;Застосувати</translation>
    </message>
    <message>
        <source>&lt;&lt; &amp;Done</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Edit &gt;&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;New</source>
        <translation type="unfinished">&amp;Новий</translation>
    </message>
    <message>
        <source>&amp;Import</source>
        <translation type="unfinished">І&amp;мпортувати</translation>
    </message>
    <message>
        <source>&amp;Clone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation type="unfinished">&amp;Видалити</translation>
    </message>
    <message>
        <source>Reset all changes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply all changes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply all changes and exit edit mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Create a new style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Import styles from another document</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Clone selected style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete selected styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>New</source>
        <translation type="unfinished">Новий</translation>
    </message>
    <message>
        <source>Import</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Clone</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Send to Scrapbook</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Delete</source>
        <translation type="unfinished">Видалити</translation>
    </message>
    <message>
        <source>&amp;Edit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Done</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shortcut</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Edit styles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name of the selected style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Edit</source>
        <translation type="unfinished">Редагувати</translation>
    </message>
    <message>
        <source>New %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This key sequence is already in use</source>
        <translation type="unfinished">Ця ключова послідовність вже використовується</translation>
    </message>
    <message>
        <source>More than one style selected</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>StyleSelect</name>
    <message>
        <source>Underline</source>
        <translation type="obsolete">Підкреслення</translation>
    </message>
    <message>
        <source>Small Caps</source>
        <translation>Капітель</translation>
    </message>
    <message>
        <source>Subscript</source>
        <translation>Нижній індекс</translation>
    </message>
    <message>
        <source>Superscript</source>
        <translation>Верхній індекс</translation>
    </message>
    <message>
        <source>Strike Out</source>
        <translation type="obsolete">Перекреслений текст</translation>
    </message>
    <message>
        <source>Underline Words Only</source>
        <translation type="obsolete">Підкреслити лише слова</translation>
    </message>
    <message>
        <source>All Caps</source>
        <translation>Всі великі літери</translation>
    </message>
    <message>
        <source>Shadow</source>
        <translation type="obsolete">Тінь</translation>
    </message>
    <message>
        <source>Outline</source>
        <comment>Text Style Selector</comment>
        <translation type="obsolete">Схема</translation>
    </message>
    <message>
        <source>Underline Text. Hold down the button momentarily to set line width and displacement options.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Underline Words Only. Hold down the button momentarily to set line width and displacement options.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Strike Out. Hold down the button momentarily to set line width and displacement options.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Outline. Hold down the button momentarily to change the outline stroke width.</source>
        <comment>Text Style Selector</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shadowed Text. Hold down the button momentarily to enable the offset spacing.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SxwDialog</name>
    <message>
        <source>Use document name as a prefix for paragraph styles</source>
        <translation>Використовувати ім&quot;я документа, як префікс для стилів абзаців</translation>
    </message>
    <message>
        <source>Do not ask again</source>
        <translation>Більше на запитувати</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>OpenOffice.org Writer Importer Options</source>
        <translation>Установки імпортера документів OpenOffice.org Writer</translation>
    </message>
    <message>
        <source>Enabling this will overwrite existing styles in the current Scribus document</source>
        <translation>Активація цією установки приведе до перезапису існуючих стилів
в активному документі Scribus</translation>
    </message>
    <message>
        <source>Merge Paragraph Styles</source>
        <translation>Об&apos;єднати стилі абзаців</translation>
    </message>
    <message>
        <source>Merge paragraph styles by attributes. This will result in fewer similar paragraph styles, will retain style attributes, even if the original document&apos;s styles are named differently.</source>
        <translation>Об&apos;єднати стилі абзаців по атрибутах. Це приведе до зменшення числа схожих
стилів абзаців і збереже атрибути стилів навіть якщо стилі вихідного документу
мали інші імена.</translation>
    </message>
    <message>
        <source>Prepend the document name to the paragraph style name in Scribus.</source>
        <translation>Приєднати назву документа як префікс до імені стилю абзацу в
Scribus.</translation>
    </message>
    <message>
        <source>Make these settings the default and do not prompt again when importing an OpenOffice.org 1.x document.</source>
        <translation>Зробити ці установки установками по умовчанню і не запитувати знову під
час імпорту документу OASIS OpenDocument версій 1.х.</translation>
    </message>
    <message>
        <source>Overwrite Paragraph Styles</source>
        <translation>Переписати стилі абзаців</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
</context>
<context>
    <name>TOCIndexPrefs</name>
    <message>
        <source>None</source>
        <translation>Ніякого</translation>
    </message>
    <message>
        <source>At the beginning</source>
        <translation>На початку</translation>
    </message>
    <message>
        <source>At the end</source>
        <translation>В кінці</translation>
    </message>
    <message>
        <source>Not Shown</source>
        <translation>Не показано</translation>
    </message>
    <message>
        <source>Table of Contents and Indexes</source>
        <translation>Зміст та індекси</translation>
    </message>
    <message>
        <source>Table Of Contents</source>
        <translation>Зміст</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation>&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>The frame the table of contents will be placed into</source>
        <translation>Рамка в якій буде розміщено зміст</translation>
    </message>
    <message>
        <source>Page Numbers Placed:</source>
        <translation>Розміщені номери сторінок:</translation>
    </message>
    <message>
        <source>Item Attribute Name:</source>
        <translation>Назва атрибута об&apos;єкта:</translation>
    </message>
    <message>
        <source>The Item Attribute that will be set on frames used as a basis for creation of the entries</source>
        <translation>Атрибут об&apos;єкта, який буде встановлено для рамок, які будуть використані для створення нових пунктів</translation>
    </message>
    <message>
        <source>Place page numbers of the entries at the beginning or the end of the line, or not at all</source>
        <translation>Розмістити номери сторінок пунктів на початку або в кінці рядка, або ніде</translation>
    </message>
    <message>
        <source>List Non-Printing Entries</source>
        <translation>Представити список недрукуємих пунктів</translation>
    </message>
    <message>
        <source>Include frames that are set to not print as well</source>
        <translation>Також включити рамки, які не будуть надруковані</translation>
    </message>
    <message>
        <source>The paragraph style used for the entry lines</source>
        <translation>Стиль абзацу використовуваний для рядків</translation>
    </message>
    <message>
        <source>Paragraph Style:</source>
        <translation>Стиль абзацу:</translation>
    </message>
    <message>
        <source>Destination Frame:</source>
        <translation>Цільова рамка:</translation>
    </message>
    <message>
        <source>Inde&amp;x</source>
        <translation type="obsolete">Інде&amp;кс</translation>
    </message>
</context>
<context>
    <name>TOCIndexPrefsBase</name>
    <message>
        <source>Table of Contents and Indexes</source>
        <translation>Зміст та індекси</translation>
    </message>
    <message>
        <source>Table Of Contents</source>
        <translation>Зміст</translation>
    </message>
    <message>
        <source>&amp;Add</source>
        <translation>&amp;Додати</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation>Alt+A</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Alt+D</source>
        <translation>Alt+D</translation>
    </message>
    <message>
        <source>The frame the table of contents will be placed into</source>
        <translation>Рамка в якій буде розміщено зміст</translation>
    </message>
    <message>
        <source>Page Numbers Placed:</source>
        <translation>Розміщені номери сторінок:</translation>
    </message>
    <message>
        <source>Item Attribute Name:</source>
        <translation>Назва атрибута об&apos;єкта:</translation>
    </message>
    <message>
        <source>The Item Attribute that will be set on frames used as a basis for creation of the entries</source>
        <translation>Атрибут об&apos;єкта, який буде встановлено для рамок, які будуть використані для створення нових пунктів</translation>
    </message>
    <message>
        <source>Place page numbers of the entries at the beginning or the end of the line, or not at all</source>
        <translation>Розмістити номери сторінок пунктів на початку або в кінці рядка, або не розміщувати зовсім</translation>
    </message>
    <message>
        <source>List Non-Printing Entries</source>
        <translation>Представити список недрукованих пунктів</translation>
    </message>
    <message>
        <source>Include frames that are set to not print as well</source>
        <translation>Також включити рамки, які не будуть надруковані</translation>
    </message>
    <message>
        <source>The paragraph style used for the entry lines</source>
        <translation>Стиль абзаца для рядків</translation>
    </message>
    <message>
        <source>Paragraph Style:</source>
        <translation>Стиль абзаца:</translation>
    </message>
    <message>
        <source>Destination Frame:</source>
        <translation>Цільова рамка:</translation>
    </message>
    <message>
        <source>Inde&amp;x</source>
        <translation type="obsolete">Інде&amp;кс</translation>
    </message>
</context>
<context>
    <name>TabCheckDoc</name>
    <message>
        <source>Ignore all errors</source>
        <translation>Ігнорувати всі помилки</translation>
    </message>
    <message>
        <source>Automatic check before printing or exporting</source>
        <translation>Автоматична перевірка перед друком чи експортом</translation>
    </message>
    <message>
        <source>Check for missing glyphs</source>
        <translation>Перевірка відсутності символів</translation>
    </message>
    <message>
        <source>Check for objects not on a page</source>
        <translation type="obsolete">Перевірка відсутності об&apos;єктів на сторінці</translation>
    </message>
    <message>
        <source>Check for overflow in text frames</source>
        <translation>Перевірка переповнення текстових рамок</translation>
    </message>
    <message>
        <source>Check for transparencies used</source>
        <translation type="obsolete">Перевірка використання прозорості</translation>
    </message>
    <message>
        <source>Check for missing images</source>
        <translation>Перевірка відсутності зображень</translation>
    </message>
    <message>
        <source>Check image resolution</source>
        <translation>Перевірка розрішення зображень</translation>
    </message>
    <message>
        <source>Lowest allowed resolution</source>
        <translation>Найнижче дозволене розрішення</translation>
    </message>
    <message>
        <source> dpi</source>
        <translation> тнд</translation>
    </message>
    <message>
        <source>Check for placed PDF Files</source>
        <translation>Перевірка розміщених PDF файлів</translation>
    </message>
    <message>
        <source>Check for PDF Annotations and Fields</source>
        <translation>Перевірка PDF аннотацій та полів</translation>
    </message>
    <message>
        <source>Add Profile</source>
        <translation>Додати профіль</translation>
    </message>
    <message>
        <source>Remove Profile</source>
        <translation>Видалити профіль</translation>
    </message>
    <message>
        <source>Highest allowed resolution</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Check for GIF images</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Ignore non-printable Layers</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Check for items not on a page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Check for used transparencies</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabDisplay</name>
    <message>
        <source>Color for paper</source>
        <translation type="unfinished">Колір паперу</translation>
    </message>
    <message>
        <source>Mask the area outside the margins in the margin color</source>
        <translation type="unfinished">Замаскувати область за полями кольором полів</translation>
    </message>
    <message>
        <source>Enable or disable  the display of linked frames.</source>
        <translation type="unfinished">Ввімкнути або вимкнути показ поєднаних рамок.</translation>
    </message>
    <message>
        <source>Display non-printing characters such as paragraph markers in text frames</source>
        <translation type="unfinished">Показувати недруковані знаки, такі як маркери абзаців, в текстових рамках</translation>
    </message>
    <message>
        <source>Turns the display of frames on or off</source>
        <translation type="unfinished">Переключає показ рамок</translation>
    </message>
    <message>
        <source>Turns the display of layer indicators on or off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Turns the display of pictures on or off</source>
        <translation type="unfinished">Переключає показ зображень</translation>
    </message>
    <message>
        <source>Defines amount of space left of the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="unfinished">Визначає розмір простіру на канві зліва від документа доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space right of the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="unfinished">Визначає розмір простіру на канві справа від документа доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space above the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="unfinished">Визначає розмір простіру на канві над документом доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Defines amount of space below the document canvas available as a pasteboard for creating and modifying elements and dragging them onto the active page</source>
        <translation type="unfinished">Визначає розмір простіру на канві під документом доступного як чорновик для створення та редагування елементів перед перетягуванням їх на активну сторінку</translation>
    </message>
    <message>
        <source>Set the default zoom level</source>
        <translation type="unfinished">Установити стандартний масштаб зображення</translation>
    </message>
    <message>
        <source>Place a ruler against your screen and drag the slider to set the zoom level so Scribus will display your pages and objects on them at the correct size</source>
        <translation type="unfinished">Притуліть лінійку до екрану та зсуньте повзунок масштаба зображення поки Scribus не почне показувати справжній розмір сторінок та об&apos;єктів на них</translation>
    </message>
</context>
<context>
    <name>TabDisplayBase</name>
    <message>
        <source>Page Display</source>
        <translation type="unfinished">Показ сторінки</translation>
    </message>
    <message>
        <source>Show Layer Indicators</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Frames</source>
        <translation type="unfinished">Показати рамки</translation>
    </message>
    <message>
        <source>Show Text Chains</source>
        <translation type="unfinished">Показати текстові ланцюги</translation>
    </message>
    <message>
        <source>Display &amp;Unprintable Area in Margin Color</source>
        <translation type="unfinished">Виділити &amp;недрукуєму область кольором поля</translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation type="unfinished">Alt+U</translation>
    </message>
    <message>
        <source>Rulers Relative to Page</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Text Control Characters</source>
        <translation type="unfinished">Показати контрольні знаки тексту</translation>
    </message>
    <message>
        <source>Show Pictures</source>
        <translation type="unfinished">Показати зображення</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation type="obsolete">Колір:</translation>
    </message>
    <message>
        <source>Scratch Space</source>
        <translation type="unfinished">Чорновик</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Right:</source>
        <translation type="unfinished">&amp;Правий край:</translation>
    </message>
    <message>
        <source>&amp;Bottom:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Top:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Gaps Between Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Horizontal:</source>
        <translation type="unfinished">Горизонтальна:</translation>
    </message>
    <message>
        <source>Vertical:</source>
        <translation type="unfinished">Вертикальна:</translation>
    </message>
    <message>
        <source>Adjust Display Size</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>To adjust the display drag the ruler below with the slider.</source>
        <translation type="unfinished">Для зміни видимого перетягніть лінійку внизу повзунком.</translation>
    </message>
    <message>
        <source>General</source>
        <translation type="unfinished">Загальні</translation>
    </message>
    <message>
        <source>Colors</source>
        <translation type="unfinished">Кольори</translation>
    </message>
    <message>
        <source>Pages:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fill Color:</source>
        <translation type="unfinished">Колір заповнення:</translation>
    </message>
    <message>
        <source>Selected Page Border:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Frames</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Locked:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Normal:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Selected:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Linked:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Grouped:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Annotation:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Text:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Control Characters:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Bleed Area</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>TabDisplayBase</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Scale%</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabDocument</name>
    <message>
        <source>Custom</source>
        <translation type="obsolete">Нестандартний</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation type="unfinished">Розмір сторінки</translation>
    </message>
    <message>
        <source>&amp;Size:</source>
        <translation type="unfinished">&amp;Розмір:</translation>
    </message>
    <message>
        <source>Portrait</source>
        <translation type="unfinished">Вертикальна</translation>
    </message>
    <message>
        <source>Landscape</source>
        <translation type="unfinished">Горизонтальна</translation>
    </message>
    <message>
        <source>Orie&amp;ntation:</source>
        <translation type="unfinished">&amp;Орієнтація:</translation>
    </message>
    <message>
        <source>Units:</source>
        <translation type="unfinished">Одиниці виміру:</translation>
    </message>
    <message>
        <source>&amp;Width:</source>
        <translation type="unfinished">&amp;Ширина:</translation>
    </message>
    <message>
        <source>&amp;Height:</source>
        <translation type="unfinished">&amp;Висота:</translation>
    </message>
    <message>
        <source>Margin Guides</source>
        <translation type="unfinished">Розмітка полів</translation>
    </message>
    <message>
        <source>Autosave</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>min</source>
        <translation type="unfinished">хв</translation>
    </message>
    <message>
        <source>&amp;Interval:</source>
        <translation type="unfinished">&amp;Інтервал:</translation>
    </message>
    <message>
        <source>Undo/Redo</source>
        <translation type="unfinished">Відмінити/повторити</translation>
    </message>
    <message>
        <source>Action history length</source>
        <translation type="unfinished">Розмір історії подій</translation>
    </message>
    <message>
        <source>Width of document pages, editable if you have chosen a custom page size</source>
        <translation type="unfinished">Ширина сторінок документа. Її можна змінити, якщо Ви вибрали нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Height of document pages, editable if you have chosen a custom page size</source>
        <translation type="unfinished">Висота сторінок документа. Її можна змінити, якщо Ви вибрали нестандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Default page size, either a standard size or a custom size</source>
        <translation type="unfinished">Стандартний розмір сторінки</translation>
    </message>
    <message>
        <source>Default orientation of document pages</source>
        <translation type="unfinished">Стандартна орієнтація сторінок документа</translation>
    </message>
    <message>
        <source>Default unit of measurement for document editing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>When enabled, Scribus saves a backup copy of your file with the .bak extension each time the time period elapses</source>
        <translation type="unfinished">Якщо ввімкнено, Scribus зберігатиме резервну копію файла з розширенням .bak в кінці кожног заданого періода</translation>
    </message>
    <message>
        <source>Time period between saving automatically</source>
        <translation type="unfinished">Період часу між двома автоматичними записами файла</translation>
    </message>
    <message>
        <source>Set the length of the action history in steps. If set to 0 infinite amount of actions will be stored.</source>
        <translation type="unfinished">Установити протяжність історії дій в кроках. Якщо установлено 0 (нуль) то зберігатиметься необмежена кількість кроків.</translation>
    </message>
    <message>
        <source>Apply the page size changes to all existing pages in the document</source>
        <translation type="unfinished">Застосувати зміни розмірів сторінки до всіх існуючих сторінок документа</translation>
    </message>
    <message>
        <source>Apply settings to:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Document Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>All Master Pages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply the page size changes to all existing master pages in the document</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabExternalToolsWidget</name>
    <message>
        <source>Locate Ghostscript</source>
        <translation type="unfinished">Знайти Ghostscript </translation>
    </message>
    <message>
        <source>Locate your image editor</source>
        <translation type="unfinished">Знайти редактор зображень</translation>
    </message>
    <message>
        <source>Locate your web browser</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabExternalToolsWidgetBase</name>
    <message>
        <source>External Tools</source>
        <translation type="unfinished">Зовнішні інструменти</translation>
    </message>
    <message>
        <source>PostScript Interpreter</source>
        <translation type="unfinished">Інтерпретатор постскрипт</translation>
    </message>
    <message>
        <source>&amp;Name of Executable:</source>
        <translation type="unfinished">Назва файла про&amp;грами:</translation>
    </message>
    <message>
        <source>&amp;Change..</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Antialias &amp;Text</source>
        <translation type="unfinished">Антиаліасинг &amp;тексту</translation>
    </message>
    <message>
        <source>Alt+T</source>
        <translation type="unfinished">Alt+T</translation>
    </message>
    <message>
        <source>Antialias text for EPS and PDF onscreen rendering</source>
        <translation type="unfinished">Антиаліасинг тексту для рендерингу EPS та PDF на екрані</translation>
    </message>
    <message>
        <source>Antialias &amp;Graphics</source>
        <translation type="unfinished">Антиаліасинг &amp;графіки</translation>
    </message>
    <message>
        <source>Alt+G</source>
        <translation type="unfinished">Alt+G</translation>
    </message>
    <message>
        <source>Antialias graphics for EPS and PDF onscreen rendering</source>
        <translation type="unfinished">Антиаліасинг графіки для рендерингу EPS та PDF на екрані</translation>
    </message>
    <message>
        <source>Resolution:</source>
        <translation type="unfinished">Розрішення:</translation>
    </message>
    <message>
        <source> dpi</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Image Processing Tool</source>
        <translation type="unfinished">Інструмент для обробки зображень</translation>
    </message>
    <message>
        <source>Name of &amp;Executable:</source>
        <translation type="unfinished">Назва файла про&amp;грами:</translation>
    </message>
    <message>
        <source>&amp;Change...</source>
        <translation type="unfinished">&amp;Замінити...</translation>
    </message>
    <message>
        <source>&amp;Rescan</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+R</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;qt&gt;Add the path for the Ghostscript interpreter. On Windows, please note it is important to note you need to use the program named gswin32c.exe - NOT gswin32.exe. Otherwise, this maybe cause a hang when starting Scribus.&lt;/qt&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;qt&gt;File system location for graphics editor. If you use gimp and your distribution includes it, we recommend &apos;gimp-remote&apos;, as it allows you to edit the image in an already running instance of gimp.&lt;/qt&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Web Browser</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Web Browser to launch with links from the Help system</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;qt&gt;File system location for your web browser. This is used for external links from the Help system.&lt;/qt&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Rescan for the external tools if they do not exist in the already specified location</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabGeneral</name>
    <message>
        <source>Select your default language for Scribus to run with. Leave this blank to choose based on environment variables. You can still override this by passing a command line option when starting Scribus</source>
        <translation type="unfinished">Виберіть основну мову для використання в Scribus. Залиште пустим для використання перемінних робочого середовища. Ви зможете змінити цю установку за допомогою використання перемикачів командної строки при запуску Scribus</translation>
    </message>
    <message>
        <source>Number of recently edited documents to show in the File menu</source>
        <translation type="unfinished">Скільки недавно редагованих документів показувати в меню Файл</translation>
    </message>
    <message>
        <source>Number of lines Scribus will scroll for each move of the mouse wheel</source>
        <translation type="unfinished">Число рядків для прокручування на кожний рух колеса мишки</translation>
    </message>
    <message>
        <source>Choose the default window decoration and looks. Scribus inherits any available KDE or Qt themes, if Qt is configured to search KDE plugins.</source>
        <translation type="unfinished">Виберіть стандартні декорацію вікон та вигляд програми. Scribus має доступ до всіх наявних тем KDE та Qt, якщо Qt
сконфігурований для пошуку KDE модулів.</translation>
    </message>
    <message>
        <source>Default font size for the menus and windows</source>
        <translation type="unfinished">Стандартний розмір шрифта для меню та вікон</translation>
    </message>
    <message>
        <source>Default font size for the tool windows</source>
        <translation type="unfinished">Стандартний розмір шрифта для вікон інструментарію</translation>
    </message>
    <message>
        <source>Default documents directory</source>
        <translation type="unfinished">Стандартна директорія для документів</translation>
    </message>
    <message>
        <source>Default ICC profiles directory. This cannot be changed with a document open. By default, Scribus will look in the System Directories under Mac OSX and Windows. On Linux and Unix, Scribus will search $home/.color/icc,/usr/share/color/icc and /usr/local/share/color/icc </source>
        <translation type="unfinished">Стандартна директорія для кольорових профілів. Ця установка не може бути змінена при відчиненому документі. По умовчанню
Scribus виконає пошук в системних директоріях під системами MacOSX та Windows. Під Linux та Unix Scribus шукатиме в
директоріях $home/.color/icc,/usr/share/color/icc та /usr/local/share/color/icc(sp)</translation>
    </message>
    <message>
        <source>Default Scripter scripts directory</source>
        <translation type="unfinished">Стандартна директорія для сценаріїв Сценариста</translation>
    </message>
    <message>
        <source>Additional directory for document templates</source>
        <translation type="unfinished">Додаткова директорія для шаблонів</translation>
    </message>
    <message>
        <source>Choose a Directory</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabGeneralBase</name>
    <message>
        <source>GUI</source>
        <translation type="obsolete">Графічна оболонка</translation>
    </message>
    <message>
        <source>&amp;Language:</source>
        <translation type="unfinished">&amp;Мова:</translation>
    </message>
    <message>
        <source>&amp;Theme:</source>
        <translation type="unfinished">&amp;Тема:</translation>
    </message>
    <message>
        <source>Time before a Move or Resize starts:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source> ms</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Font Size (Menus):</source>
        <translation type="unfinished">&amp;Розмір шрифта (Меню):</translation>
    </message>
    <message>
        <source> pt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Font Size (&amp;Palettes):</source>
        <translation type="unfinished">Розмір шрифта (&amp;Палітри):</translation>
    </message>
    <message>
        <source>&amp;Wheel Jump:</source>
        <translation type="unfinished">&amp;Крок колесика миші:</translation>
    </message>
    <message>
        <source>&amp;Recent Documents:</source>
        <translation type="unfinished">&amp;Недавно редаговані документи:</translation>
    </message>
    <message>
        <source>Paths</source>
        <translation type="unfinished">Шляхи</translation>
    </message>
    <message>
        <source>&amp;Documents:</source>
        <translation type="unfinished">Док&amp;ументи:</translation>
    </message>
    <message>
        <source>&amp;Change...</source>
        <translation type="unfinished">&amp;Замінити...</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;ICC Profiles:</source>
        <translation type="unfinished">&amp;ICC профілі:</translation>
    </message>
    <message>
        <source>C&amp;hange...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Alt+H</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Scripts:</source>
        <translation type="unfinished">&amp;Сценарії:</translation>
    </message>
    <message>
        <source>Ch&amp;ange...</source>
        <translation type="unfinished">&amp;Змінити...</translation>
    </message>
    <message>
        <source>Alt+A</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Document &amp;Templates:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Cha&amp;nge...</source>
        <translation type="unfinished">З&amp;мінити...</translation>
    </message>
    <message>
        <source>Alt+N</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>User Interface</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Show Startup Dialog</source>
        <translation type="unfinished">Показувати стартовий діалог</translation>
    </message>
    <message>
        <source>Show Splashscreen on Startup</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>TabGeneralBase</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabGuides</name>
    <message>
        <source>Common Settings</source>
        <translation>Загальні установки</translation>
    </message>
    <message>
        <source>Placing in Documents</source>
        <translation>Розміщення в документах</translation>
    </message>
    <message>
        <source>In the Background</source>
        <translation>На фоні</translation>
    </message>
    <message>
        <source>In the Foreground</source>
        <translation>На передньому плані</translation>
    </message>
    <message>
        <source>Snapping</source>
        <translation>Притягування</translation>
    </message>
    <message>
        <source>Snap Distance:</source>
        <translation>Відстань притягування:</translation>
    </message>
    <message>
        <source>Grab Radius:</source>
        <translation>Радіус захвату:</translation>
    </message>
    <message>
        <source> px</source>
        <translation> пікс</translation>
    </message>
    <message>
        <source>Show Guides</source>
        <translation>Показати розмітку</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation>Колір:</translation>
    </message>
    <message>
        <source>Show Margins</source>
        <translation>Показати поля</translation>
    </message>
    <message>
        <source>Show Page Grid</source>
        <translation>Показати сітку сторінки</translation>
    </message>
    <message>
        <source>Major Grid</source>
        <translation>Основна сітка</translation>
    </message>
    <message>
        <source>Spacing:</source>
        <translation>Проміжок:</translation>
    </message>
    <message>
        <source>Minor Grid</source>
        <translation>Допоміжна сітка</translation>
    </message>
    <message>
        <source>Show Baseline Grid</source>
        <translation>Показати базову сітку</translation>
    </message>
    <message>
        <source>Baseline Settings</source>
        <translation>Установки базової сітки</translation>
    </message>
    <message>
        <source>Baseline &amp;Grid:</source>
        <translation>&amp;Базова сітка:</translation>
    </message>
    <message>
        <source>Baseline &amp;Offset:</source>
        <translation>Зс&amp;ув базової сітки:</translation>
    </message>
    <message>
        <source>Distance between the minor grid lines</source>
        <translation>Відстань між лініями допоміжної сітки</translation>
    </message>
    <message>
        <source>Distance between the major grid lines</source>
        <translation>Відстань між лініями головної сітки</translation>
    </message>
    <message>
        <source>Distance within which an object will snap to your placed guides</source>
        <translation>Зона притягування об&apos;єкта до розмітки</translation>
    </message>
    <message>
        <source>Radius of the area where Scribus will allow you to grab an objects handles</source>
        <translation>Радіус захвату вузлів об&apos;єктів</translation>
    </message>
    <message>
        <source>Color of the minor grid lines</source>
        <translation>Колір ліній допоміжної сітки</translation>
    </message>
    <message>
        <source>Color of the major grid lines</source>
        <translation>Колір ліній головної сітки</translation>
    </message>
    <message>
        <source>Color of the guide lines you insert</source>
        <translation>Колір вставлених ліній розмітки</translation>
    </message>
    <message>
        <source>Color for the margin lines</source>
        <translation>Колір ліній полів сторінки</translation>
    </message>
    <message>
        <source>Color for the baseline grid</source>
        <translation>Колір базової сітки</translation>
    </message>
    <message>
        <source>Turns the basegrid on or off</source>
        <translation>Вмикає та вимикає базову сітку</translation>
    </message>
    <message>
        <source>Turns the gridlines on or off</source>
        <translation>Вмикає та вимикає сітку</translation>
    </message>
    <message>
        <source>Turns the guides on or off</source>
        <translation>Вмикає та вимикає розмітку</translation>
    </message>
    <message>
        <source>Turns the margins on or off</source>
        <translation>Вмикає та вимикає поля</translation>
    </message>
    <message>
        <source>Guides are not visible through objects on the page</source>
        <translation>Розмітка не видима через об&apos;єкти розміщені на сторінці</translation>
    </message>
    <message>
        <source>Guides are visible above all objects on the page</source>
        <translation>Розмітка видима через об&apos;єкти розміщені на сторінці</translation>
    </message>
    <message>
        <source>Distance between the lines of the baseline grid</source>
        <translation>Відстань між лініями базової сітки</translation>
    </message>
    <message>
        <source>Distance from the top of the page for the first baseline</source>
        <translation>Відстань від верхнього краю сторінки до першої базової лінії</translation>
    </message>
</context>
<context>
    <name>TabKeyboardShortcutsWidget</name>
    <message>
        <source>Key Set XML Files (*.ksxml)</source>
        <translation type="unfinished">Файли ключового набору XML (*.ksxml)</translation>
    </message>
    <message>
        <source>Alt</source>
        <translation type="unfinished">Alt</translation>
    </message>
    <message>
        <source>Ctrl</source>
        <translation type="unfinished">Ctrl</translation>
    </message>
    <message>
        <source>Shift</source>
        <translation type="unfinished">Shift</translation>
    </message>
    <message>
        <source>Meta</source>
        <translation type="unfinished">Мета</translation>
    </message>
    <message>
        <source>Meta+</source>
        <translation type="unfinished">Мета+</translation>
    </message>
    <message>
        <source>Shift+</source>
        <translation type="unfinished">Shift+</translation>
    </message>
    <message>
        <source>Alt+</source>
        <translation type="unfinished">Alt+</translation>
    </message>
    <message>
        <source>Ctrl+</source>
        <translation type="unfinished">Ctrl+</translation>
    </message>
    <message>
        <source>This key sequence is already in use</source>
        <translation type="unfinished">Ця ключова послідовність вже використовується</translation>
    </message>
</context>
<context>
    <name>TabKeyboardShortcutsWidgetBase</name>
    <message>
        <source>Keyboard Shortcuts</source>
        <translation type="unfinished">Набори гарячих клавіш</translation>
    </message>
    <message>
        <source>Search:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Action</source>
        <translation type="unfinished">Дія</translation>
    </message>
    <message>
        <source>Shortcut</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shortcut for Selected Action</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;No Key</source>
        <translation type="unfinished">&amp;Без ключа</translation>
    </message>
    <message>
        <source>Alt+N</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;User Defined Key</source>
        <translation type="unfinished">Ключ визначений &amp;користувачем</translation>
    </message>
    <message>
        <source>Alt+U</source>
        <translation type="unfinished">Alt+U</translation>
    </message>
    <message>
        <source>Set &amp;Key</source>
        <translation type="unfinished">&amp;Установити ключ</translation>
    </message>
    <message>
        <source>Alt+K</source>
        <translation type="unfinished">Alt+Г</translation>
    </message>
    <message>
        <source>CTRL+ALT+SHIFT+W</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Loadable Shortcut Sets</source>
        <translation type="unfinished">Набори гарячих клавіш</translation>
    </message>
    <message>
        <source>Keyboard shortcut sets available to load</source>
        <translation type="unfinished">Набори гарячих клавіш доступні для завантаження</translation>
    </message>
    <message>
        <source>&amp;Load</source>
        <translation type="unfinished">За&amp;вантажити</translation>
    </message>
    <message>
        <source>Alt+L</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Load the selected shortcut set</source>
        <translation type="unfinished">Завантажити вибраний набір гарячих клавіш</translation>
    </message>
    <message>
        <source>&amp;Import...</source>
        <translation type="unfinished">&amp;Імпортувати...</translation>
    </message>
    <message>
        <source>Alt+I</source>
        <translation type="unfinished">Alt+I</translation>
    </message>
    <message>
        <source>Import a shortcut set into the current configuration</source>
        <translation type="unfinished">Імпортувати набір гарячих клавіш в активну конфігурацію</translation>
    </message>
    <message>
        <source>&amp;Export...</source>
        <translation type="unfinished">&amp;Експортувати...</translation>
    </message>
    <message>
        <source>Alt+E</source>
        <translation type="unfinished">Alt+E</translation>
    </message>
    <message>
        <source>Export the current shortcuts into an importable file</source>
        <translation type="unfinished">Експортувати активні гарячі клавіші в зовнішій файл</translation>
    </message>
    <message>
        <source>&amp;Reset</source>
        <translation type="unfinished">&amp;Перезавантажити</translation>
    </message>
    <message>
        <source>Alt+R</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Reload the default Scribus shortcuts</source>
        <translation type="unfinished">Перезавантажити набір гарячих клавіш по умовчанню</translation>
    </message>
</context>
<context>
    <name>TabManager</name>
    <message>
        <source>Manage Tabulators</source>
        <translation>Налаштування табуляторів</translation>
    </message>
</context>
<context>
    <name>TabMiscellaneousBase</name>
    <message>
        <source>Form1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Always ask before fonts are replaced when loading a document</source>
        <translation type="unfinished">Завжди запитувати перед заміною шрифтів при завантаженні документа</translation>
    </message>
    <message>
        <source>Preview of current Paragraph Style visible when editing Styles</source>
        <translation type="unfinished">Попередній перегляд активних стилів абзаців видимий при редагуванні стилів</translation>
    </message>
    <message>
        <source>Show Startup Dialog</source>
        <translation type="obsolete">Показувати стартовий діалог</translation>
    </message>
    <message>
        <source>Lorem Ipsum</source>
        <translation type="unfinished">Lorem Ipsum</translation>
    </message>
    <message>
        <source>Always use standard Lorem Ipsum</source>
        <translation type="unfinished">Завжди використовувати стандартний текст Lorem Ipsum</translation>
    </message>
    <message>
        <source>Count of the Paragraphs:</source>
        <translation type="unfinished">Число абзаців:</translation>
    </message>
</context>
<context>
    <name>TabPDFOptions</name>
    <message>
        <source>Export Range</source>
        <translation>Діапазон експортування</translation>
    </message>
    <message>
        <source>&amp;All Pages</source>
        <translation>&amp;Всі сторінки</translation>
    </message>
    <message>
        <source>C&amp;hoose Pages</source>
        <translation>&amp;Виберіть сторінки</translation>
    </message>
    <message>
        <source>&amp;Rotation:</source>
        <translation>&amp;Кут повороту:</translation>
    </message>
    <message>
        <source>File Options</source>
        <translation>Установки файла</translation>
    </message>
    <message>
        <source>Compatibilit&amp;y:</source>
        <translation>&amp;Сумісність:</translation>
    </message>
    <message>
        <source>&amp;Binding:</source>
        <translation>&amp;Перепліт:</translation>
    </message>
    <message>
        <source>Left Margin</source>
        <translation>Ліва сторона</translation>
    </message>
    <message>
        <source>Right Margin</source>
        <translation>Права сторона</translation>
    </message>
    <message>
        <source>Generate &amp;Thumbnails</source>
        <translation>Створити &amp;Мініатюрні зображення</translation>
    </message>
    <message>
        <source>Save &amp;Linked Text Frames as PDF Articles</source>
        <translation>Зберегти &amp;зв&apos;язані текстові рамки, як статті PDF</translation>
    </message>
    <message>
        <source>&amp;Include Bookmarks</source>
        <translation>Включити &amp;закладки</translation>
    </message>
    <message>
        <source> dpi</source>
        <translation> тнд</translation>
    </message>
    <message>
        <source>&amp;Resolution for EPS Graphics:</source>
        <translation>Роз&amp;рішення для EPS графіки:</translation>
    </message>
    <message>
        <source>Com&amp;press Text and Vector Graphics</source>
        <translation>Стис&amp;нути текст та векторну графіку</translation>
    </message>
    <message>
        <source>Automatic</source>
        <translation>Автоматичний</translation>
    </message>
    <message>
        <source>None</source>
        <translation>Ніякого</translation>
    </message>
    <message>
        <source>Maximum</source>
        <translation>Максимальна</translation>
    </message>
    <message>
        <source>High</source>
        <translation>Висока</translation>
    </message>
    <message>
        <source>Medium</source>
        <translation>Середня</translation>
    </message>
    <message>
        <source>Low</source>
        <translation>Низька</translation>
    </message>
    <message>
        <source>Minimum</source>
        <translation>Мінімальна</translation>
    </message>
    <message>
        <source>&amp;General</source>
        <translation>&amp;Загальні</translation>
    </message>
    <message>
        <source>&amp;Embed all Fonts</source>
        <translation type="obsolete">&amp;Вбудувати всі шрифти</translation>
    </message>
    <message>
        <source>&amp;Subset all Fonts</source>
        <translation type="obsolete">Провести вибірку всіх &amp;шрифтів</translation>
    </message>
    <message>
        <source>Embedding</source>
        <translation>Вбудовування шрифтів</translation>
    </message>
    <message>
        <source>Available Fonts:</source>
        <translation>Доступні шрифти:</translation>
    </message>
    <message>
        <source>&amp;&gt;&gt;</source>
        <translation>&amp;&gt;&gt;</translation>
    </message>
    <message>
        <source>&amp;&lt;&lt;</source>
        <translation>&amp;&lt;&lt;</translation>
    </message>
    <message>
        <source>Fonts to embed:</source>
        <translation>Шрифти для вбудовування:</translation>
    </message>
    <message>
        <source>Fonts to subset:</source>
        <translation type="obsolete">Шрифти для вибірки:</translation>
    </message>
    <message>
        <source>&amp;Fonts</source>
        <translation>&amp;Шрифти</translation>
    </message>
    <message>
        <source>Enable &amp;Presentation Effects</source>
        <translation>Ввімкнути презентаційні &amp;ефекти</translation>
    </message>
    <message>
        <source>Page</source>
        <translation>Сторінка</translation>
    </message>
    <message>
        <source>Show Page Pre&amp;views</source>
        <translation>&amp;Попередній перегляд сторінок</translation>
    </message>
    <message>
        <source>Effects</source>
        <translation>Ефекти</translation>
    </message>
    <message>
        <source>&amp;Display Duration:</source>
        <translation>&amp;Тривалість показу:</translation>
    </message>
    <message>
        <source>Effec&amp;t Duration:</source>
        <translation>Тривалість &amp;ефекту:</translation>
    </message>
    <message>
        <source>Effect T&amp;ype:</source>
        <translation>Т&amp;ип ефекту:</translation>
    </message>
    <message>
        <source>&amp;Moving Lines:</source>
        <translation>&amp;Рухливі лінії:</translation>
    </message>
    <message>
        <source>F&amp;rom the:</source>
        <translation>&amp;Від:</translation>
    </message>
    <message>
        <source>D&amp;irection:</source>
        <translation>&amp;Напрямок:</translation>
    </message>
    <message>
        <source> sec</source>
        <translation> сек</translation>
    </message>
    <message>
        <source>No Effect</source>
        <translation>Ніякого ефекту</translation>
    </message>
    <message>
        <source>Blinds</source>
        <translation>Венська фіранка</translation>
    </message>
    <message>
        <source>Box</source>
        <translation>Коробка</translation>
    </message>
    <message>
        <source>Dissolve</source>
        <translation>Розтавання</translation>
    </message>
    <message>
        <source>Glitter</source>
        <translation>Сяйво</translation>
    </message>
    <message>
        <source>Split</source>
        <translation>Розділення</translation>
    </message>
    <message>
        <source>Wipe</source>
        <translation>Витирання</translation>
    </message>
    <message>
        <source>Horizontal</source>
        <translation>Горизонтально</translation>
    </message>
    <message>
        <source>Vertical</source>
        <translation>Вертикально</translation>
    </message>
    <message>
        <source>Inside</source>
        <translation>Зсередини</translation>
    </message>
    <message>
        <source>Outside</source>
        <translation>Ззовні</translation>
    </message>
    <message>
        <source>Left to Right</source>
        <translation>Зліва направо</translation>
    </message>
    <message>
        <source>Top to Bottom</source>
        <translation>Зверху донизу</translation>
    </message>
    <message>
        <source>Bottom to Top</source>
        <translation>Знизу вверх</translation>
    </message>
    <message>
        <source>Right to Left</source>
        <translation>Зправа наліво</translation>
    </message>
    <message>
        <source>Top-left to Bottom-Right</source>
        <translation>Зліва зверху вправо вниз</translation>
    </message>
    <message>
        <source>&amp;Apply Effect on all Pages</source>
        <translation>Застосувати ефект на в&amp;сіх сторінках</translation>
    </message>
    <message>
        <source>E&amp;xtras</source>
        <translation>&amp;Додатки</translation>
    </message>
    <message>
        <source>&amp;Use Encryption</source>
        <translation>Використовувати &amp;шифрування</translation>
    </message>
    <message>
        <source>Passwords</source>
        <translation>Паролі</translation>
    </message>
    <message>
        <source>&amp;User:</source>
        <translation>&amp;Користувач:</translation>
    </message>
    <message>
        <source>&amp;Owner:</source>
        <translation>В&amp;ласник:</translation>
    </message>
    <message>
        <source>Settings</source>
        <translation>Установки</translation>
    </message>
    <message>
        <source>Allow &amp;Printing the Document</source>
        <translation>Дозволити &amp;друк документа</translation>
    </message>
    <message>
        <source>Allow &amp;Changing the Document</source>
        <translation>Дозволити внесення &amp;змін в документ</translation>
    </message>
    <message>
        <source>Allow Cop&amp;ying Text and Graphics</source>
        <translation>Дозволити &amp;копіювання тексту і зображень</translation>
    </message>
    <message>
        <source>Allow Adding &amp;Annotations and Fields</source>
        <translation>Дозволити додавання &amp;аннотацій та полів</translation>
    </message>
    <message>
        <source>S&amp;ecurity</source>
        <translation>&amp;Захист</translation>
    </message>
    <message>
        <source>General</source>
        <translation>Загальні</translation>
    </message>
    <message>
        <source>Output &amp;Intended For:</source>
        <translation>Вихідний документ &amp;призначений для:</translation>
    </message>
    <message>
        <source>Screen / Web</source>
        <translation>Екран комп&apos;ютера/Веб сторінка</translation>
    </message>
    <message>
        <source>Printer</source>
        <translation>Прінтер</translation>
    </message>
    <message>
        <source>Grayscale</source>
        <translation>Відтінки сірого</translation>
    </message>
    <message>
        <source>&amp;Use Custom Rendering Settings</source>
        <translation>Використовувати нестандартні &amp;установки рендерингу</translation>
    </message>
    <message>
        <source>Rendering Settings</source>
        <translation>Установки рендерингу</translation>
    </message>
    <message>
        <source>Fre&amp;quency:</source>
        <translation>&amp;Частота:</translation>
    </message>
    <message>
        <source>&amp;Angle:</source>
        <translation>&amp;Кут:</translation>
    </message>
    <message>
        <source>S&amp;pot Function:</source>
        <translation>&amp;Локальна функція:</translation>
    </message>
    <message>
        <source>Simple Dot</source>
        <translation>Проста точка</translation>
    </message>
    <message>
        <source>Line</source>
        <translation>Лінія</translation>
    </message>
    <message>
        <source>Round</source>
        <translation>Круг</translation>
    </message>
    <message>
        <source>Ellipse</source>
        <translation>Елліпс</translation>
    </message>
    <message>
        <source>Solid Colors:</source>
        <translation>Однотонні кольори:</translation>
    </message>
    <message>
        <source>Use ICC Profile</source>
        <translation>Використовувати ICC профіль</translation>
    </message>
    <message>
        <source>Profile:</source>
        <translation>Профіль:</translation>
    </message>
    <message>
        <source>Rendering-Intent:</source>
        <translation>Призначення вихідного зображення:</translation>
    </message>
    <message>
        <source>Perceptual</source>
        <translation>Уявний</translation>
    </message>
    <message>
        <source>Relative Colorimetric</source>
        <translation>Відносно кольорометричний</translation>
    </message>
    <message>
        <source>Saturation</source>
        <translation>Насичення</translation>
    </message>
    <message>
        <source>Absolute Colorimetric</source>
        <translation>Абсолютна кольорометрія</translation>
    </message>
    <message>
        <source>Images:</source>
        <translation>Зображення:</translation>
    </message>
    <message>
        <source>Don&apos;t use embedded ICC profiles</source>
        <translation>Не використовувати внутрішні ICC профілі</translation>
    </message>
    <message>
        <source>C&amp;olor</source>
        <translation>&amp;Колір</translation>
    </message>
    <message>
        <source>PDF/X-3 Output Intent</source>
        <translation>Призначення вихідного документу PDF/X-3</translation>
    </message>
    <message>
        <source>&amp;Info String:</source>
        <translation>&amp;Інформація:</translation>
    </message>
    <message>
        <source>Output &amp;Profile:</source>
        <translation>Профіль &amp;виводу:</translation>
    </message>
    <message>
        <source>Trim Box</source>
        <translation type="obsolete">Обрізати рамку</translation>
    </message>
    <message>
        <source>PDF/X-&amp;3</source>
        <translation type="obsolete">PDF/X-&amp;3</translation>
    </message>
    <message>
        <source>Show page previews of each page listed above.</source>
        <translation>Показувати попередній перегляд кожної сторінки вказаної вверху.</translation>
    </message>
    <message>
        <source>Type of the display effect.</source>
        <translation>Тип ефекту.</translation>
    </message>
    <message>
        <source>Direction of the effect of moving lines for the split and blind effects.</source>
        <translation>Напрямок руху ліній для ефектів &quot;розділений&quot; і &quot;венеціанська штора&quot;.</translation>
    </message>
    <message>
        <source>Starting position for the box and split effects.</source>
        <translation>Початкова позиція для ефектів &quot;коробка&quot; і &quot;розділений&quot;.</translation>
    </message>
    <message>
        <source>Direction of the glitter or wipe effects.</source>
        <translation>Напрямок руху ефектів &quot;блиск&quot; і &quot;витирання&quot;.</translation>
    </message>
    <message>
        <source>Apply the selected effect to all pages.</source>
        <translation>Застосувати вибраний ефект на всіх сторінках.</translation>
    </message>
    <message>
        <source>Export all pages to PDF</source>
        <translation>Експортувати всі сторінки в PDF</translation>
    </message>
    <message>
        <source>Export a range of pages to PDF</source>
        <translation>Експортувати діапазон сторінок в PDF</translation>
    </message>
    <message>
        <source>Generate PDF Articles, which is useful for navigating linked articles in a PDF.</source>
        <translation>Генерувати PDF Статті. Вони корисні для навігації ссилок на статті в PDF.</translation>
    </message>
    <message>
        <source>DPI (Dots Per Inch) for image export.</source>
        <translation>DPI (Точок на квадратний дюйм) для експорту зображень.</translation>
    </message>
    <message>
        <source>Choose a password for users to be able to read your PDF.</source>
        <translation>Виберіть пароль для захисту PDF документа від перегляду.</translation>
    </message>
    <message>
        <source>Allow printing of the PDF. If un-checked, printing is prevented. </source>
        <translation>Дозволити друк PDF. Якщо не вибрати цей параметр, то друк буде заборонено.</translation>
    </message>
    <message>
        <source>Allow modifying of the PDF. If un-checked, modifying the PDF is prevented.</source>
        <translation>Дозволити редагування PDF. Якщо цей параметр не вибрати, то редагування PDF буде заборонено.</translation>
    </message>
    <message>
        <source>Embed a color profile for solid colors</source>
        <translation>Вбудувати кольоровий профіль для однотонних кольорів</translation>
    </message>
    <message>
        <source>Color profile for solid colors</source>
        <translation>Кольоровий профіль для однотонних кольорів</translation>
    </message>
    <message>
        <source>Rendering intent for solid colors</source>
        <translation>Схема перерахунку кольорів для однотонних кольорів</translation>
    </message>
    <message>
        <source>Embed a color profile for images</source>
        <translation>Вбудований кольоровий профіль для зображень</translation>
    </message>
    <message>
        <source>Do not use color profiles that are embedded in source images</source>
        <translation>Не використовувати кольорові профілі вбудовані в оригінальні зображення</translation>
    </message>
    <message>
        <source>Color profile for images</source>
        <translation>Кольоровий профіль для зображень</translation>
    </message>
    <message>
        <source>Rendering intent for images</source>
        <translation>Схема перерахунку кольорів для зображень</translation>
    </message>
    <message>
        <source>Output profile for printing. If possible, get some guidance from your printer on profile selection.</source>
        <translation>Профіль для друку. При можливості скористайтеся порадами 
технолога типографії для правильного вибору цього профіля.</translation>
    </message>
    <message>
        <source>Distance for bleed from the top of the physical page</source>
        <translation>Розмір поля для перекриття з верхньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the bottom of the physical page</source>
        <translation>Розмір поля для перекриття з нижньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the left of the physical page</source>
        <translation>Розмір поля для перекриття з лівої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the right of the physical page</source>
        <translation>Розмір поля для перекриття з правої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Mirror Page(s) horizontally</source>
        <translation>Віддзеркалити сторінку(и) горизонтально</translation>
    </message>
    <message>
        <source>Mirror Page(s) vertically</source>
        <translation>Віддзеркалити сторінку(и) вертикально</translation>
    </message>
    <message>
        <source>Convert Spot Colors to Process Colors</source>
        <translation>Конвертувати точкові кольори в процесні кольори</translation>
    </message>
    <message>
        <source>Compression &amp;Quality:</source>
        <translation>Стиснення та &amp;Якість:</translation>
    </message>
    <message>
        <source>Compression quality levels for lossy compression methods: Minimum (25%), Low (50%), Medium (75%), High (85%), Maximum (95%). Note that a quality level does not directly determine the size of the resulting image - both size and quality loss vary from image to image at any given quality level.</source>
        <translation type="obsolete">Рівні якості стиснення для методів, які допускають втрату якості: Мінімальна (25%), Низька (50%), Середня (75%), Висока (85%), Максимальна (95%). Майте на увазі, що рівень якості прямо не визначає розмір кінцевого зображення - і розмір і втрата якості будуть різними для різних зображень на любому рівні якості.</translation>
    </message>
    <message>
        <source>Allow copying of text or graphics from the PDF. If unchecked, text and graphics cannot be copied.</source>
        <translation>Дозволити копіювання тексту чи графіки з PDF. Якщо не вибрано, текст та графіка не можуть бути скопійовані.</translation>
    </message>
    <message>
        <source>Allow adding annotations and fields to the PDF. If unchecked, editing annotations and fields is prevented.</source>
        <translation>Дозволити додавання аннотацій та полів до PDF. Якщо не вибрано, редагування аннотацій та полів не дозволяється.</translation>
    </message>
    <message>
        <source>Enables Spot Colors to be converted to composite colors. Unless you are planning to print spot colors at a commercial printer, this is probably best left enabled.</source>
        <translation>Дозволяє конвертування реєстрових кольорів в композитні. Якщо Ви не збираєтеся друкувати Ваш документ в
комерційній друкарні реєстровими кольорами то краще залиште цю установку ввімкненою.</translation>
    </message>
    <message>
        <source>Include La&amp;yers</source>
        <translation>Включити &amp;плани</translation>
    </message>
    <message>
        <source>Compression Metho&amp;d:</source>
        <translation>&amp;Метод стиснення:</translation>
    </message>
    <message>
        <source>Resa&amp;mple Images to:</source>
        <translation>Пере&amp;рахувати зображення до:</translation>
    </message>
    <message>
        <source>Embed fonts into the PDF. Embedding the fonts will preserve the layout and appearance of your document.</source>
        <translation>Вбудувати шрифти в PDF. Вбудовування шрифтів забезпечить точне збереження формату та вигляду документа.</translation>
    </message>
    <message>
        <source>Length of time the effect runs. A shorter time will speed up the effect, a longer one will slow it down.</source>
        <translation>Час дії ефекту. Коротший час пришвидшить ефект, а довший час його сповільнить.</translation>
    </message>
    <message>
        <source>Insert a comma separated list of tokens where a token can be * for all the pages, 1-5 for a range of pages or a single page number.</source>
        <translation>Вмістити список елементів, розділений комами де елемент
може бути * для всіх сторінок, 1-5 для діапазона сторінок, або
номер окремої сторінки.</translation>
    </message>
    <message>
        <source>Determines the binding of pages in the PDF. Unless you know you need to change it leave the default choice - Left.</source>
        <translation>Визначає переплітання сторінок в PDF. Якщо Ви не впевнені в необхідності зміни цієї установки то краще залиште стандартний метод - Ліве.</translation>
    </message>
    <message>
        <source>Generates thumbnails of each page in the PDF. Some viewers can use the thumbnails for navigation.</source>
        <translation>Створює зменшені зображення кожної сторінки в PDF.  Деякі програми для перегляду PDF можуть використовувати ці зменшені зображення для навігації.</translation>
    </message>
    <message>
        <source>Embed the bookmarks you created in your document. These are useful for navigating long PDF documents.</source>
        <translation>Вбудувати закладки в документ. Вони можуть бути корисними для навігації в довгих PDF документах.</translation>
    </message>
    <message>
        <source>Export resolution of text and vector graphics. This does not affect the resolution of bitmap images like photos.</source>
        <translation>Розрішення експортування тексту та векторної графіки. Не має ніякого впливу на розрішення експортування растрових зображень, таких як фотографії.</translation>
    </message>
    <message>
        <source>Enables lossless compression of text and graphics. Unless you have a reason, leave this checked. This reduces PDF file size.</source>
        <translation>Ввімкнути стиснення тексту та графіки без втрат якості. Залиште ввімкненим, якщо Ви не впевнені в необхідності зміни цієї установки. Приводить до зменшення розміру PDF файла.</translation>
    </message>
    <message>
        <source>Enable the security features in your exported PDF. If you selected PDF 1.3, the PDF will be protected by 40 bit encryption. If you selected PDF 1.4, the PDF will be protected by 128 bit encryption. Disclaimer: PDF encryption is not as reliable as GPG or PGP encryption and does have some limitations.</source>
        <translation>Ввімкнути систему захисту в експортованому PDF. Якщо вибрано PDF 1.3, файл буде захищено 40-бітним шифруванням. PDF 1.4 дозволяє 128-бітне шифрування. Попередження: шифрування PDF не є таким надійним, як GPG чи PGP шифрування і має певні додаткові обмеження.</translation>
    </message>
    <message>
        <source>Choose a master password which enables or disables all the security features in your exported PDF</source>
        <translation>Виберіть головний пароль, який керує всіма засобами захисту в експортованому PDF</translation>
    </message>
    <message>
        <source>This is an advanced setting which is not enabled by default. This should only be enabled when specifically requested by your printer and they have given you the exact details needed. Otherwise, your exported PDF may not print properly and is truly not portable across systems.</source>
        <translation>Це продвинута установка не ввімкнена по умовчанню. Її варто вмикати лише по проханню друкаря, використовуючи надані ним параметри. В іншому випадку Ви ризикуєте тим, що експортований PDF не буде правильно друкуватися і не буде еквівалентно показаним на різних системах.</translation>
    </message>
    <message>
        <source>Mandatory string for PDF/X-3 or the PDF will fail PDF/X-3 conformance. We recommend you use the title of the document.</source>
        <translation>Обов&apos;язкова установка для PDF/X-3. В іншому випадку PDF не відповідатиме вимогам PDF/X-3. Ми рекомендуємо використання заголовку документа.</translation>
    </message>
    <message>
        <source>Display Settings</source>
        <translation>Установки показу</translation>
    </message>
    <message>
        <source>Page Layout</source>
        <translation type="obsolete">Макет сторінки</translation>
    </message>
    <message>
        <source>Single Page</source>
        <translation>Одна сторінка</translation>
    </message>
    <message>
        <source>Continuous</source>
        <translation>Суцільна сторінка</translation>
    </message>
    <message>
        <source>Double Page Left</source>
        <translation>Подвійна сторінка зліва</translation>
    </message>
    <message>
        <source>Double Page Right</source>
        <translation>Подвійна сторінка справа</translation>
    </message>
    <message>
        <source>Visual Appearance</source>
        <translation>Візуальне враження</translation>
    </message>
    <message>
        <source>Use Viewers Defaults</source>
        <translation>Використовувати стандартні установки програм показу</translation>
    </message>
    <message>
        <source>Use Full Screen Mode</source>
        <translation>Використовувати повноекранний режим</translation>
    </message>
    <message>
        <source>Display Bookmarks Tab</source>
        <translation>Показувати панель закладок</translation>
    </message>
    <message>
        <source>Display Thumbnails</source>
        <translation>Показувати зменшені зображення</translation>
    </message>
    <message>
        <source>Display Layers Tab</source>
        <translation>Показувати панель планів</translation>
    </message>
    <message>
        <source>Hide Viewers Toolbar</source>
        <translation>Сховати панель інструментів програм показу</translation>
    </message>
    <message>
        <source>Hide Viewers Menubar</source>
        <translation>Сховати панель меню програм показу</translation>
    </message>
    <message>
        <source>Zoom Pages to fit Viewer Window</source>
        <translation>Установити масштаб сторінок для заповнення вікна програми показу</translation>
    </message>
    <message>
        <source>Special Actions</source>
        <translation>Особливі дії</translation>
    </message>
    <message>
        <source>No Script</source>
        <translation>Ніякого сценарію</translation>
    </message>
    <message>
        <source>Viewer</source>
        <translation>Програма показу</translation>
    </message>
    <message>
        <source>Clip to Page Margins</source>
        <translation>Обрізати по полях сторінки</translation>
    </message>
    <message>
        <source>Lossy - JPEG</source>
        <translation>З втратами - JPEG</translation>
    </message>
    <message>
        <source>Lossless - Zip</source>
        <translation>Без втрат - Zip</translation>
    </message>
    <message>
        <source>Image Compression Method</source>
        <translation>Метод стиснення зображень</translation>
    </message>
    <message>
        <source>Javascript to be executed
when PDF document is opened:</source>
        <translation>Javascript сценарій, який буде виконано
при відчиненні PDF документа:</translation>
    </message>
    <message>
        <source>Enables presentation effects when using Adobe&amp;#174; Reader&amp;#174; and other PDF viewers which support this in full screen mode.</source>
        <translation>Дозволяє використання презентаційних ефектів при застосуванні Adobe&amp;#174; Reader&amp;#174; та інших програм для перегляду PDF, які дозволяють це в повноекранному режимі.</translation>
    </message>
    <message>
        <source>Determines the PDF compatibility. The default is PDF 1.3 which gives the widest compatibility. Choose PDF 1.4 if your file uses features such as transparency or you require 128 bit encryption. PDF 1.5 is necessary when you wish to preserve objects in separate layers within the PDF.  PDF/X-3 is for exporting the PDF when you want color managed RGB for commercial printing and is selectable when you have activated color management. Use only when advised by your printer or in some cases printing to a 4 color digital color laser printer.</source>
        <translation type="obsolete">Визначає рівень сумісності PDF. По умовчанню використовується PDF 1.3, який має найбільшу сумісність. Виберіть PDF 1.4, якщо Ваш файл використовує такі можливості, як прозорість або Ви потребуєте використання 128-бітного шифрування. Використовуйте PDF 1.5, якщо Ви бажаєте зберегти об&apos;єкти на різних планах всередині PDF документа. PDF/X-3 використовується для експортування PDF при застосуванні керування RGB кольорами для комерційного друку і може бути вибраний лише при ввімкненому керуванні кольорами. Використовуйте лише з поради Вашого друкаря або, в деяких випадках, при друці на 4-х колірному лазерному принтері.</translation>
    </message>
    <message>
        <source>Layers in your document are exported to the PDF Only available if PDF 1.5 is chosen.</source>
        <translation>Плани у Вашому документі будуть експортовані в PDF лише при виборі PDF 1.5.</translation>
    </message>
    <message>
        <source>Method of compression to use for images. Automatic allows Scribus to choose the best method. ZIP is lossless and good for images with solid colors. JPEG is better at creating smaller PDF files which have many photos (with slight image quality loss possible). Leave it set to Automatic unless you have a need for special compression options. This only affects JPEG images</source>
        <translation type="obsolete">Метод стиснення зображень. Автоматичний дозволяє Scribus вибрати найкращий метод. ZIP - метод без втрат і найкраще всього підходить для зображень з однотонними кольорами. JPEG краще використовувати для створення PDF файлів меншого розміру з багатьма фотографічними зображеннями (можлива деяка втрата якості). Залиште цю установку автоматичною, якщо у Вас немає потреби в особливих методах стиснення. Ця установка лише впливає на JPEG зображення</translation>
    </message>
    <message>
        <source>Re-sample your bitmap images to the selected DPI. Leaving this unchecked will render them at their native resolution. Enabling this will increase memory usage and slow down export.</source>
        <translation>Перерахувати растрові зображення до вибраних DPI. Вимкнення цієї установки приведе до того, що зображення будуть залишені з початковим розрішенням. Ввімкнення привете до підвищеного використання пам&apos;яті та сповільнення експортування.</translation>
    </message>
    <message>
        <source>Color model for the output of your PDF. Choose Screen/Web for PDFs which are used for screen display and for printing on typical inkjets. Choose Printer when printing to a true 4 color CMYK printer. Choose Grayscale when you want a grey scale PDF.</source>
        <translation>Кольорова модель PDF експорту. Виберіть Екран/Веб для PDF документів призначених для показу на екрані комп&apos;ютера чи для друку на типових струменевих принтерах. Виберіть Принтер для друку на справжньому 4-х колірному СМЖЧ принтері. Виберіть Відтінки сірого для експорту PDF у відтінках сірого кольору.</translation>
    </message>
    <message>
        <source>Do not show objects outside the margins in the exported file</source>
        <translation>Не показувати об&apos;єкти за полями в експортованому файлі</translation>
    </message>
    <message>
        <source>Length of time the page is shown before the presentation starts on the selected page. Setting 0 will disable automatic page transition.</source>
        <translation>Скільки часу буде показана сторінка до початку презентації. Вибір 0 приведе до вимкнення автоматичної зміни сторінок.</translation>
    </message>
    <message>
        <source>Force Overprint Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enables global Overprint Mode for this document, overrides object settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Determines the PDF compatibility.&lt;br/&gt;The default is &lt;b&gt;PDF 1.3&lt;/b&gt; which gives the widest compatibility.&lt;br/&gt;Choose &lt;b&gt;PDF 1.4&lt;/b&gt; if your file uses features such as transparency or you require 128 bit encryption.&lt;br/&gt;&lt;b&gt;PDF 1.5&lt;/b&gt; is necessary when you wish to preserve objects in separate layers within the PDF.&lt;br/&gt;&lt;b&gt;PDF/X-3&lt;/b&gt; is for exporting the PDF when you want color managed RGB for commercial printing and is selectable when you have activated color management. Use only when advised by your printer or in some cases printing to a 4 color digital color laser printer.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Embed all</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fonts to outline:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Outline all</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Printer Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Crop Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Registration Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color Bars</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Page Information</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Offset:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bottom:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Left:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Right:</source>
        <translation type="unfinished">Праве:</translation>
    </message>
    <message>
        <source>Use Document Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Pre-Press</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Convert all glyphs in the document to outlines.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Method of compression to use for images. Automatic allows Scribus to choose the best method. ZIP is lossless and good for images with solid colors. JPEG is better at creating smaller PDF files which have many photos (with slight image quality loss possible). Leave it set to Automatic unless you have a need for special compression options.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Compression quality levels for lossy compression methods: Minimum (25%), Low (50%), Medium (75%), High (85%), Maximum (95%). Note that a quality level does not directly determine the size of the resulting image - both size and quality loss vary from image to image at any given quality level. Even with Maximum selected, there is always some quality loss with jpeg.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Inside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Outside:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Document Layout</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabPrinter</name>
    <message>
        <source>Distance for bleed from the top of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з верхньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the bottom of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з нижньої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the left of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з лівої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Distance for bleed from the right of the physical page</source>
        <translation type="unfinished">Розмір поля для перекриття з правої сторони фізичної сторінки</translation>
    </message>
    <message>
        <source>Do not show objects outside the margins on the printed page</source>
        <translation type="unfinished">Не показувати об&apos;єкти за полями на друкованій сторінці</translation>
    </message>
    <message>
        <source>Use an alternative print manager, such as kprinter or gtklp, to utilize additional printing options</source>
        <translation type="unfinished">Використовуйте альтернативний менеджер друку, такий як kprinter чи gtklp, щоб мати 
доступ до додаткових установок друку</translation>
    </message>
    <message>
        <source>Sets the PostScript Level.
 Setting to Level 1 or 2 can create huge files</source>
        <translation type="unfinished">Установлює рівень Постскрипту.
 Вибір 1-го чи 2-го рівня може призвести
до створення дуже великих файлів</translation>
    </message>
    <message>
        <source>A way of switching off some of the gray shades which are composed of cyan, yellow and magenta and using black instead. UCR most affects parts of images which are neutral and/or dark tones which are close to the gray. Use of this may improve printing some images and some experimentation and testing is need on a case by case basis.UCR reduces the possibility of over saturation with CMY inks.</source>
        <translation type="unfinished">Метод заміни деяких відтінків сірого, які насправді складаються з салатового, жовтого та фуксинового кольорів, на 
чорний колір. UCR найбільше впливає на частини зображень з нейтральними та або темними відтінками близькими до
сірого. Використання цього методу може покращити якість друку деяких зображень. У певних випадках потребується
експериментальний підбір варіантів. UCR знижує ймовірність перенасичення паперу СЖФ чорнилами.</translation>
    </message>
    <message>
        <source>Enables Spot Colors to be converted to composite colors. Unless you are planning to print spot colors at a commercial printer, this is probably best left enabled.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enables global Overprint Mode for this document, overrides object settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Allows you to embed ICC profiles in the print stream when color management is enabled</source>
        <translation type="unfinished">Дозволяє вставку кольорових профілів в потік даних для друку при ввімкненому управлінні кольорами</translation>
    </message>
    <message>
        <source>This enables you to explicitely set the media size of the PostScript file. Not recommended unless requested by your printer.</source>
        <translation type="unfinished">Дозволяє явну установку розміру паперу для ПостСкрипт файла. Не рекомендується без запиту від професійного друкаря.</translation>
    </message>
    <message>
        <source>File</source>
        <translation type="unfinished">Файл</translation>
    </message>
    <message>
        <source>All</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabPrinterBase</name>
    <message>
        <source>Print Destination</source>
        <translation type="unfinished">Призначення для друку</translation>
    </message>
    <message>
        <source>Alternative Printer Command</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Command:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Options</source>
        <translation type="unfinished">Установки</translation>
    </message>
    <message>
        <source>Postscript Options</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Level 1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Level 2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Level 3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Print in Color if Available</source>
        <translation type="unfinished">Друкувати в кольорі, якщо можливо</translation>
    </message>
    <message>
        <source>Print in Grayscale</source>
        <translation type="unfinished">Друкувати у відтінках сірого кольору</translation>
    </message>
    <message>
        <source>Page</source>
        <translation type="unfinished">Сторінка</translation>
    </message>
    <message>
        <source>Mirror Page(s) Horizontal</source>
        <translation type="unfinished">Віддзеркалити сторінку(и) горизонтально</translation>
    </message>
    <message>
        <source>Mirror Page(s) Vertical</source>
        <translation type="unfinished">Віддзеркалити сторінку(и) вертикально</translation>
    </message>
    <message>
        <source>Set Media Size</source>
        <translation type="unfinished">Установити розмір паперу</translation>
    </message>
    <message>
        <source>Clip to Page Margins</source>
        <translation type="unfinished">Обрізати по полях сторінки</translation>
    </message>
    <message>
        <source>Color</source>
        <translation type="unfinished">Колір</translation>
    </message>
    <message>
        <source>Apply Under Color Removal</source>
        <translation type="unfinished">Виконати видалення кольорів</translation>
    </message>
    <message>
        <source>Convert Spot Colors to Process Colors</source>
        <translation type="unfinished">Конвертувати точкові кольори в процесні кольори</translation>
    </message>
    <message>
        <source>Force Overprint Mode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply ICC Profiles</source>
        <translation type="unfinished">Застосувати ICC профілі</translation>
    </message>
    <message>
        <source>General</source>
        <translation type="unfinished">Загальні</translation>
    </message>
    <message>
        <source>Print Normal</source>
        <translation type="unfinished">Звичайний друк</translation>
    </message>
    <message>
        <source>Print Separations</source>
        <translation type="unfinished">Друкувати окремі кольори</translation>
    </message>
    <message>
        <source>Marks &amp;&amp; Bleeds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Printer Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Crop Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Registration Marks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Offset:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Color Bars</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bleed Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Top:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bottom:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Left:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Right:</source>
        <translation type="unfinished">Праве:</translation>
    </message>
    <message>
        <source>TabPrinterBase</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabScrapbookBase</name>
    <message>
        <source>Send Copied Items Automatically to Scrapbook</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This enables the scrapbook to be used an extension to the copy/paste buffers. Simply copying an object or grouped object will send this to the Scrapbook automatically</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Keep Copied Items Permanently Across Sessions</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This enables copied items to be kept permanently in the scrapbook.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Number of Copied Items to Keep in Scrapbook:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The minimum number is 1; the maximum us 100.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>TabScrapbookBase</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabTools</name>
    <message>
        <source>Font:</source>
        <translation>Шрифт:</translation>
    </message>
    <message>
        <source> pt</source>
        <translation> тчк</translation>
    </message>
    <message>
        <source>Size:</source>
        <translation>Розмір:</translation>
    </message>
    <message>
        <source>None</source>
        <translation>Нічого</translation>
    </message>
    <message>
        <source>Fill Color:</source>
        <translation>Колір заповнення:</translation>
    </message>
    <message>
        <source>Stroke Color:</source>
        <translation>Колір контура:</translation>
    </message>
    <message>
        <source>Tab Fill Character:</source>
        <translation>Символ заповнення відступа:</translation>
    </message>
    <message>
        <source>Tab Width:</source>
        <translation>Ширина відступа:</translation>
    </message>
    <message>
        <source>Colu&amp;mns:</source>
        <translation>&amp;Стовпці:</translation>
    </message>
    <message>
        <source>&amp;Gap:</source>
        <translation>&amp;Проміжок:</translation>
    </message>
    <message>
        <source>Woven silk pyjamas exchanged for blue quartz</source>
        <translation>Реве та стогне Дніпр широкий, сердитий вітер завива</translation>
    </message>
    <message>
        <source>&amp;Line Color:</source>
        <translation>Колір &amp;лінії:</translation>
    </message>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
    <message>
        <source>&amp;Shading:</source>
        <translation>&amp;Затінення:</translation>
    </message>
    <message>
        <source>&amp;Fill Color:</source>
        <translation>Колір запо&amp;внення:</translation>
    </message>
    <message>
        <source>S&amp;hading:</source>
        <translation>&amp;Затінення:</translation>
    </message>
    <message>
        <source>Line Style:</source>
        <translation>Стиль лінії:</translation>
    </message>
    <message>
        <source>Line &amp;Width:</source>
        <translation>Тов&amp;щина лінії:</translation>
    </message>
    <message>
        <source>Line S&amp;tyle:</source>
        <translation>Стиль &amp;лінії:</translation>
    </message>
    <message>
        <source>Arrows:</source>
        <translation>Стрілки:</translation>
    </message>
    <message>
        <source>Start:</source>
        <translation>Початок:</translation>
    </message>
    <message>
        <source>End:</source>
        <translation>Кінець:</translation>
    </message>
    <message>
        <source>&amp;Free Scaling</source>
        <translation>&amp;Вільне масштабування</translation>
    </message>
    <message>
        <source>&amp;Horizontal Scaling:</source>
        <translation>&amp;Горизонтальне масштабування:</translation>
    </message>
    <message>
        <source>&amp;Vertical Scaling:</source>
        <translation>&amp;Вертикальне масштабування:</translation>
    </message>
    <message>
        <source>&amp;Scale Picture to Frame Size</source>
        <translation>Установити масштаб зображення по розміру &amp;рамки</translation>
    </message>
    <message>
        <source>Keep Aspect &amp;Ratio</source>
        <translation>Зберігати &amp;співвідношення сторін</translation>
    </message>
    <message>
        <source>F&amp;ill Color:</source>
        <translation>Колір запо&amp;внення:</translation>
    </message>
    <message>
        <source>Use embedded Clipping Path</source>
        <translation>Використовувати вбудований шлях обрізання</translation>
    </message>
    <message>
        <source>On Screen Preview</source>
        <translation>Попередній перегляд на екрані</translation>
    </message>
    <message>
        <source>Full Resolution Preview</source>
        <translation>Попередній перегляд з повним розрішенням</translation>
    </message>
    <message>
        <source>Normal Resolution Preview</source>
        <translation>Попередній перегляд зі звичайним розрішенням</translation>
    </message>
    <message>
        <source>Low Resolution Preview</source>
        <translation>Попередній перегляд з низьким розрішенням</translation>
    </message>
    <message>
        <source>Mi&amp;nimum:</source>
        <translation>&amp;Мінімум:</translation>
    </message>
    <message>
        <source>Ma&amp;ximum:</source>
        <translation>Ма&amp;ксимум:</translation>
    </message>
    <message>
        <source>&amp;Stepping:</source>
        <translation>&amp;Крок:</translation>
    </message>
    <message>
        <source>Text Frame Properties</source>
        <translation>Властивості текстової рамки</translation>
    </message>
    <message>
        <source>Picture Frame Properties</source>
        <translation>Властивості рамки для зображень</translation>
    </message>
    <message>
        <source>Shape Drawing Properties</source>
        <translation>Властивості рисування геометричних фігур</translation>
    </message>
    <message>
        <source>Magnification Level Defaults</source>
        <translation>Стандартні установки масштабу зображення</translation>
    </message>
    <message>
        <source>Line Drawing Properties</source>
        <translation>Властивості рисування лінії</translation>
    </message>
    <message>
        <source>Polygon Drawing Properties</source>
        <translation>Властивості рисування полігонів</translation>
    </message>
    <message>
        <source>Font for new text frames</source>
        <translation>Шрифт для нових текстових рамок</translation>
    </message>
    <message>
        <source>Size of font for new text frames</source>
        <translation>Розмір шрифта для нових текстових рамок</translation>
    </message>
    <message>
        <source>Color of font</source>
        <translation>Колір шрифта</translation>
    </message>
    <message>
        <source>Number of columns in a text frame</source>
        <translation>Число стовпців в текстовій рамці</translation>
    </message>
    <message>
        <source>Gap between text frame columns</source>
        <translation>Проміжок між стовпцями текстової рамки</translation>
    </message>
    <message>
        <source>Sample of your font</source>
        <translation>Зразок Вашого шрифта</translation>
    </message>
    <message>
        <source>Picture frames allow pictures to scale to any size</source>
        <translation>Рамки для зображень дозволяють масштабування зображень до любого розміру</translation>
    </message>
    <message>
        <source>Horizontal scaling of images</source>
        <translation>Горизонтальне масштабування зображень</translation>
    </message>
    <message>
        <source>Vertical scaling of images</source>
        <translation>Вертикальне масштабування зображень</translation>
    </message>
    <message>
        <source>Keep horizontal and vertical scaling the same</source>
        <translation>Утримувати горизонтальне масштабування рівним вертикальному</translation>
    </message>
    <message>
        <source>Pictures in picture frames are scaled to the size of the frame</source>
        <translation>Зображення у рамках для зображень масштабовані до розміру рамки</translation>
    </message>
    <message>
        <source>Automatically scaled pictures keep their original proportions</source>
        <translation>Автоматично масштабовані зображення зберігають відношення сторін</translation>
    </message>
    <message>
        <source>Fill color of picture frames</source>
        <translation>Колір заповнення рамок зображень</translation>
    </message>
    <message>
        <source>Saturation of color of fill</source>
        <translation>Насиченість кольору заповнення</translation>
    </message>
    <message>
        <source>Line color of shapes</source>
        <translation>Колір ліній геометричних фігур</translation>
    </message>
    <message>
        <source>Saturation of color of lines</source>
        <translation>Насиченість кольору ліній геометричних фігур</translation>
    </message>
    <message>
        <source>Fill color of shapes</source>
        <translation>Колір заповнення геометричних фігур</translation>
    </message>
    <message>
        <source>Line style of shapes</source>
        <translation>Стиль ліній геометричних фігур</translation>
    </message>
    <message>
        <source>Line width of shapes</source>
        <translation>Ширина ліній геометричних фігур</translation>
    </message>
    <message>
        <source>Minimum magnification allowed</source>
        <translation>Мінімально дозволений масштаб зображення</translation>
    </message>
    <message>
        <source>Maximum magnification allowed</source>
        <translation>Максимально дозволений масштаб зображення</translation>
    </message>
    <message>
        <source>Change in magnification for each zoom operation</source>
        <translation>Зміна масштабу зображення при кожному кроці масштабування</translation>
    </message>
    <message>
        <source>Color of lines</source>
        <translation>Колір ліній</translation>
    </message>
    <message>
        <source>Saturation of color</source>
        <translation>Насиченість кольору</translation>
    </message>
    <message>
        <source>Style of lines</source>
        <translation>Стиль ліній</translation>
    </message>
    <message>
        <source>Width of lines</source>
        <translation>Товщина ліній</translation>
    </message>
    <message>
        <source>Custom:</source>
        <translation type="obsolete">Нестандартний:</translation>
    </message>
    <message>
        <source>Custom: </source>
        <translation type="obsolete">Нестандартний: </translation>
    </message>
    <message>
        <source>Text Color:</source>
        <translation>Колір тексту:</translation>
    </message>
    <message>
        <source>Shading:</source>
        <translation>Затінення:</translation>
    </message>
    <message>
        <source>Text Stroke:</source>
        <translation>Контур тексту:</translation>
    </message>
    <message>
        <source>Dot</source>
        <translation>Точка</translation>
    </message>
    <message>
        <source>Hyphen</source>
        <translation>Тире</translation>
    </message>
    <message>
        <source>Underscore</source>
        <translation>Підкреслення</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation>Нестандартний</translation>
    </message>
    <message>
        <source>None</source>
        <comment>tab fill</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Text</source>
        <translation type="unfinished">Текст</translation>
    </message>
    <message>
        <source>Shapes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Lines</source>
        <translation type="unfinished">Лінії</translation>
    </message>
    <message>
        <source>Images</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Regular Polygons</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Zoom</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Rotation Tool</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Constrain to:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Other Properties</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Miscellaneous Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Item Duplicate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>X Displacement</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Y Displacement</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Horizontal displacement of page items</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Vertical displacement of page items</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Constrain value for the rotation tool when the Control key is pressed</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TabTypograpy</name>
    <message>
        <source>Subscript</source>
        <translation>Нижній індекс</translation>
    </message>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
    <message>
        <source>&amp;Displacement:</source>
        <translation>Змі&amp;щення:</translation>
    </message>
    <message>
        <source>&amp;Scaling:</source>
        <translation>&amp;Масштабування:</translation>
    </message>
    <message>
        <source>Superscript</source>
        <translation>Верхній індекс</translation>
    </message>
    <message>
        <source>D&amp;isplacement:</source>
        <translation>Змі&amp;щення:</translation>
    </message>
    <message>
        <source>S&amp;caling:</source>
        <translation>&amp;Масштабування:</translation>
    </message>
    <message>
        <source>Underline</source>
        <translation>Підкреслення</translation>
    </message>
    <message>
        <source>Displacement:</source>
        <translation>Зміщення:</translation>
    </message>
    <message>
        <source>Auto</source>
        <translation>Автоматична</translation>
    </message>
    <message>
        <source>Line Width:</source>
        <translation>Товщина лінії:</translation>
    </message>
    <message>
        <source>Strikethru</source>
        <translation>Перекреслення</translation>
    </message>
    <message>
        <source>Small Caps</source>
        <translation>Капітель</translation>
    </message>
    <message>
        <source>Sc&amp;aling:</source>
        <translation>&amp;Масштабування:</translation>
    </message>
    <message>
        <source>Automatic &amp;Line Spacing</source>
        <translation>Автоматичний мі&amp;жрядковий інтервал</translation>
    </message>
    <message>
        <source>Line Spacing:</source>
        <translation>Міжрядковий інтервал:</translation>
    </message>
    <message>
        <source>Displacement above the baseline of the font on a line</source>
        <translation>Зміщення над основою шрифта на лінії</translation>
    </message>
    <message>
        <source>Relative size of the superscript compared to the normal font</source>
        <translation>Відносний розмір верхнього індексу у порівнянні з звичайним шрифтом</translation>
    </message>
    <message>
        <source>Displacement below the baseline of the normal font on a line</source>
        <translation>Зміщення під основою шрифта на лінії</translation>
    </message>
    <message>
        <source>Relative size of the subscript compared to the normal font</source>
        <translation>Відносний розмір нижнього індексу у порівнянні з звичайним шрифтом</translation>
    </message>
    <message>
        <source>Relative size of the small caps font compared to the normal font</source>
        <translation>Відносний розмір капітелі у порівнянні з звичайним шрифтом</translation>
    </message>
    <message>
        <source>Percentage increase over the font size for the line spacing</source>
        <translation>Збільшення інтервалу між рядками у відсотках розміру шрифта</translation>
    </message>
    <message>
        <source>Displacement below the baseline of the normal font expressed as a percentage of the fonts descender</source>
        <translation>Зміщення під базовою лінією нормального шрифта, виражене у відсотках зменшення шрифтів</translation>
    </message>
    <message>
        <source>Line width expressed as a percentage of the font size</source>
        <translation>Товщина лінії вираженя у відсотках розміру шрифта</translation>
    </message>
    <message>
        <source>Displacement above the baseline of the normal font expressed as a percentage of the fonts ascender</source>
        <translation>Зміщення над базовою лінією нормального шрифта, виражене у відсотках збільшення шрифтів</translation>
    </message>
</context>
<context>
    <name>Tabruler</name>
    <message>
        <source>Left</source>
        <translation>Лівий край</translation>
    </message>
    <message>
        <source>Right</source>
        <translation>Правий край</translation>
    </message>
    <message>
        <source>Full Stop</source>
        <translation>Повна зупинка</translation>
    </message>
    <message>
        <source>Comma</source>
        <translation>Кома</translation>
    </message>
    <message>
        <source>Center</source>
        <translation>Центр</translation>
    </message>
    <message>
        <source>Delete All</source>
        <translation>Видалити всі</translation>
    </message>
    <message>
        <source>Indentation for first line of the paragraph</source>
        <translation>Відступ для першого рядка абзаца</translation>
    </message>
    <message>
        <source>Indentation from the left for the whole paragraph</source>
        <translation>Лівий відступ для всього абзаца</translation>
    </message>
    <message>
        <source>Delete all Tabulators</source>
        <translation>Видалити всі табулятори</translation>
    </message>
    <message>
        <source>&amp;Position:</source>
        <translation>По&amp;зиція:</translation>
    </message>
    <message>
        <source>None</source>
        <translation type="obsolete">Нічого</translation>
    </message>
    <message>
        <source>Fill Char:</source>
        <translation>Символ заповнення:</translation>
    </message>
    <message>
        <source>Custom:</source>
        <translation type="obsolete">Нестандартний:</translation>
    </message>
    <message>
        <source>Custom: </source>
        <translation type="obsolete">Нестандартний: </translation>
    </message>
    <message>
        <source>Dot</source>
        <translation>Точка</translation>
    </message>
    <message>
        <source>Hyphen</source>
        <translation>Тире</translation>
    </message>
    <message>
        <source>Underscore</source>
        <translation>Підкреслення</translation>
    </message>
    <message>
        <source>Custom</source>
        <translation>Нестандартний</translation>
    </message>
    <message>
        <source>None</source>
        <comment>tab fill</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Indentation from the right for the whole paragraph</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TextBrowser</name>
    <message>
        <source>Locate your web browser</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>External Web Browser Failed to Start</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Scribus was not able to start the external web browser application %1. Please check the setting in Preferences</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Tree</name>
    <message>
        <source>Outline</source>
        <translation>Об&apos;єкт</translation>
    </message>
    <message>
        <source>Element</source>
        <translation>Елемент</translation>
    </message>
    <message>
        <source>Group </source>
        <translation>Група</translation>
    </message>
    <message>
        <source>Free Objects</source>
        <translation>Вільні об&quot;єкти</translation>
    </message>
    <message>
        <source>Page </source>
        <translation>Сторінка </translation>
    </message>
    <message>
        <source>Free items</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>UnderlineValues</name>
    <message>
        <source>Auto</source>
        <translation>Автоматично</translation>
    </message>
    <message>
        <source> %</source>
        <translation> %</translation>
    </message>
    <message>
        <source>Displacement</source>
        <translation>Зміщення</translation>
    </message>
    <message>
        <source>Linewidth</source>
        <translation>Товщина лінії</translation>
    </message>
</context>
<context>
    <name>UndoManager</name>
    <message>
        <source>Add vertical guide</source>
        <translation>Додати вертикальну направляючу</translation>
    </message>
    <message>
        <source>Add horizontal guide</source>
        <translation>Додати горизонтальну направляючу</translation>
    </message>
    <message>
        <source>Remove vertical guide</source>
        <translation>Видалити вертикальну направляючу</translation>
    </message>
    <message>
        <source>Remove horizontal guide</source>
        <translation>Видалити горизонтальну направляючу</translation>
    </message>
    <message>
        <source>Move vertical guide</source>
        <translation>Перемістити вертикальну направляючу</translation>
    </message>
    <message>
        <source>Move horizontal guide</source>
        <translation>Перемістити горизонтальну направляючу</translation>
    </message>
    <message>
        <source>Lock guides</source>
        <translation>Замкнути направляючі</translation>
    </message>
    <message>
        <source>Unlock guides</source>
        <translation>Розімкнути направляючі</translation>
    </message>
    <message>
        <source>Move</source>
        <translation>Перемістити</translation>
    </message>
    <message>
        <source>Resize</source>
        <translation>Змінити розмір</translation>
    </message>
    <message>
        <source>Rotate</source>
        <translation>Повернути</translation>
    </message>
    <message>
        <source>X1: %1, Y1: %2, %3
X2: %4, Y2: %5, %6</source>
        <translation>X1: %1, Y1: %2, %3
X2: %4, Y2: %5, %6</translation>
    </message>
    <message>
        <source>W1: %1, H1: %2
W2: %3, H2: %4</source>
        <translation>W1: %1, H1: %2
W2: %3, H2: %4</translation>
    </message>
    <message>
        <source>Selection</source>
        <translation>Вибірка</translation>
    </message>
    <message>
        <source>Group</source>
        <translation>Згрупувати</translation>
    </message>
    <message>
        <source>Selection/Group</source>
        <translation>Вибірка/Група</translation>
    </message>
    <message>
        <source>Create</source>
        <translation>Створити</translation>
    </message>
    <message>
        <source>X: %1, Y: %2
W: %3, H: %4</source>
        <translation>X: %1, Y: %2
W: %3, H: %4</translation>
    </message>
    <message>
        <source>Align/Distribute</source>
        <translation>Розташувати/Вирівняти</translation>
    </message>
    <message>
        <source>Items involved</source>
        <translation>Затронуті об&apos;єкти</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <source>Set fill color</source>
        <translation>Установити колір заповнення</translation>
    </message>
    <message>
        <source>Color1: %1, Color2: %2</source>
        <translation>Колір1: %1, Колір2: %2</translation>
    </message>
    <message>
        <source>Set fill color shade</source>
        <translation>Установити колір заповнення тіні</translation>
    </message>
    <message>
        <source>Set line color</source>
        <translation>Установити колір лінії</translation>
    </message>
    <message>
        <source>Set line color shade</source>
        <translation>Установити колір тіні лінії</translation>
    </message>
    <message>
        <source>Flip horizontally</source>
        <translation>Перевернути по горизонталі</translation>
    </message>
    <message>
        <source>Flip vertically</source>
        <translation>Перевернути по вертикалі</translation>
    </message>
    <message>
        <source>Lock</source>
        <translation>Замкнути</translation>
    </message>
    <message>
        <source>Unlock</source>
        <translation>Розімкнути</translation>
    </message>
    <message>
        <source>Lock size</source>
        <translation>Замкнути розмір</translation>
    </message>
    <message>
        <source>Unlock size</source>
        <translation>Розімкнути розмір</translation>
    </message>
    <message>
        <source>Ungroup</source>
        <translation>Розгрупувати</translation>
    </message>
    <message>
        <source>Delete</source>
        <translation>Видалити</translation>
    </message>
    <message>
        <source>Rename</source>
        <translation>Перейменувати</translation>
    </message>
    <message>
        <source>From %1
to %2</source>
        <translation>Від %1
до %2</translation>
    </message>
    <message>
        <source>Apply Master Page</source>
        <translation>Застосувати головну сторінку</translation>
    </message>
    <message>
        <source>Paste</source>
        <translation>Вклеїти</translation>
    </message>
    <message>
        <source>Cut</source>
        <translation>Вирізати</translation>
    </message>
    <message>
        <source>Set fill color transparency</source>
        <translation>Установити прозорість кольору заповнення</translation>
    </message>
    <message>
        <source>Set line color transparency</source>
        <translation>Установити прозорість кольору лінії</translation>
    </message>
    <message>
        <source>Set line style</source>
        <translation>Установити стиль лінії</translation>
    </message>
    <message>
        <source>Set the style of line end</source>
        <translation>Установити стиль кінця лінії</translation>
    </message>
    <message>
        <source>Set the style of line join</source>
        <translation>Установити стиль з&apos;єднання лінії</translation>
    </message>
    <message>
        <source>Set line width</source>
        <translation>Установити товщину лінії</translation>
    </message>
    <message>
        <source>No style</source>
        <translation>Стиль не встановлено</translation>
    </message>
    <message>
        <source>Set custom line style</source>
        <translation>Установити нестандартний стиль лінії</translation>
    </message>
    <message>
        <source>Do not use custom line style</source>
        <translation>Не використовувати нестандартний стиль лінії</translation>
    </message>
    <message>
        <source>Set start arrow</source>
        <translation>Установити початкову стрілку</translation>
    </message>
    <message>
        <source>Set end arrow</source>
        <translation>Установити кінцеву стрілку</translation>
    </message>
    <message>
        <source>Create table</source>
        <translation>Створити таблицю</translation>
    </message>
    <message>
        <source>Rows: %1, Cols: %2</source>
        <translation>Рядків: %1, Стовпців: %2</translation>
    </message>
    <message>
        <source>Set font</source>
        <translation>Установити шрифт</translation>
    </message>
    <message>
        <source>Set font size</source>
        <translation>Установити розмір шрифта</translation>
    </message>
    <message>
        <source>Set font width</source>
        <translation>Установити ширину шрифта</translation>
    </message>
    <message>
        <source>Set font height</source>
        <translation>Установити висоту шрифта</translation>
    </message>
    <message>
        <source>Set font fill color</source>
        <translation>Установити колір заповнення шрифта</translation>
    </message>
    <message>
        <source>Set font stroke color</source>
        <translation>Колір силуетів шрифта</translation>
    </message>
    <message>
        <source>Set font fill color shade</source>
        <translation>Установити колір заповнення тіні шрифта</translation>
    </message>
    <message>
        <source>Set font stroke color shade</source>
        <translation>Колір тіні силуетів шрифта</translation>
    </message>
    <message>
        <source>Set kerning</source>
        <translation>Установити кернінг</translation>
    </message>
    <message>
        <source>Set line spacing</source>
        <translation>Установити міжрядковий інтервал</translation>
    </message>
    <message>
        <source>Set paragraph style</source>
        <translation>Установити стиль абзацу</translation>
    </message>
    <message>
        <source>Set language</source>
        <translation>Установити мову</translation>
    </message>
    <message>
        <source>Align text</source>
        <translation>Вирівняти текст</translation>
    </message>
    <message>
        <source>Set font effect</source>
        <translation>Установити ефект шрифта</translation>
    </message>
    <message>
        <source>Image frame</source>
        <translation>Рамка для зображень</translation>
    </message>
    <message>
        <source>Text frame</source>
        <translation>Текстова рамка</translation>
    </message>
    <message>
        <source>Polygon</source>
        <translation>Полігон</translation>
    </message>
    <message>
        <source>Bezier curve</source>
        <translation>Крива Безьє</translation>
    </message>
    <message>
        <source>Polyline</source>
        <translation>Багатосегментна лінія</translation>
    </message>
    <message>
        <source>Convert to</source>
        <translation>Конвертувати в</translation>
    </message>
    <message>
        <source>Import SVG image</source>
        <translation>Імпорт SVG зображення</translation>
    </message>
    <message>
        <source>Import EPS image</source>
        <translation>Імпорт ЕPS зображення</translation>
    </message>
    <message>
        <source>Import OpenOffice.org Draw image</source>
        <translation>Імпортувати зображення OpenOffice.org Draw</translation>
    </message>
    <message>
        <source>Scratch space</source>
        <translation>Чорновик</translation>
    </message>
    <message>
        <source>Text flows around the frame</source>
        <translation>Текст огинає рамку</translation>
    </message>
    <message>
        <source>Text flows around bounding box</source>
        <translation>Текст огинає обмежуючу рамку</translation>
    </message>
    <message>
        <source>Text flows around contour line</source>
        <translation>Текст огинає контурну лінію</translation>
    </message>
    <message>
        <source>No text flow</source>
        <translation>Відміна огинання тексту</translation>
    </message>
    <message>
        <source>No bounding box</source>
        <translation>Не використовувати обмежуючу рамку</translation>
    </message>
    <message>
        <source>No contour line</source>
        <translation>Не використовувати контурну лінію</translation>
    </message>
    <message>
        <source>Page %1</source>
        <translation>Сторінка %1</translation>
    </message>
    <message>
        <source>Set image scaling</source>
        <translation>Установити масштабування зображення</translation>
    </message>
    <message>
        <source>Frame size</source>
        <translation>Розмір рамки</translation>
    </message>
    <message>
        <source>Free scaling</source>
        <translation>Вільне масштабування</translation>
    </message>
    <message>
        <source>Keep aspect ratio</source>
        <translation>Зберігати співвідношення сторін</translation>
    </message>
    <message>
        <source>Break aspect ratio</source>
        <translation>Не зберігати співвідношення сторін</translation>
    </message>
    <message>
        <source>Edit contour line</source>
        <translation>Редагувати контурну лінію</translation>
    </message>
    <message>
        <source>Edit shape</source>
        <translation>Редагувати геометричну форму</translation>
    </message>
    <message>
        <source>Reset contour line</source>
        <translation>Повернути контурну лінію в початковий стан</translation>
    </message>
    <message>
        <source>Add page</source>
        <translation>Додати сторінку</translation>
    </message>
    <message>
        <source>Add pages</source>
        <translation>Додати сторінки</translation>
    </message>
    <message>
        <source>Delete page</source>
        <translation>Видалити сторінку</translation>
    </message>
    <message>
        <source>Delete pages</source>
        <translation>Видалити сторінки</translation>
    </message>
    <message>
        <source>Add layer</source>
        <translation>Додати план</translation>
    </message>
    <message>
        <source>Delete layer</source>
        <translation>Видалити план</translation>
    </message>
    <message>
        <source>Rename layer</source>
        <translation>Перейменувати план</translation>
    </message>
    <message>
        <source>Raise layer</source>
        <translation>Підняти план на вищий рівень</translation>
    </message>
    <message>
        <source>Lower layer</source>
        <translation>Опустити план на нижчий рівень</translation>
    </message>
    <message>
        <source>Send to layer</source>
        <translation>Перемістити на план</translation>
    </message>
    <message>
        <source>Enable printing of layer</source>
        <translation>Ввімкнути друк плану</translation>
    </message>
    <message>
        <source>Disable printing of layer</source>
        <translation>Вимкнути друк плану</translation>
    </message>
    <message>
        <source>Change name of the layer</source>
        <translation>Перейменувати план</translation>
    </message>
    <message>
        <source>Get image</source>
        <translation>Вставити зображення</translation>
    </message>
    <message>
        <source>Text on a Path</source>
        <translation>Текст на шляху</translation>
    </message>
    <message>
        <source>Enable Item Printing</source>
        <translation>Ввімкнути друк об&apos;єкта</translation>
    </message>
    <message>
        <source>Disable Item Printing</source>
        <translation>Вимкнути друк об&apos;єкта</translation>
    </message>
    <message>
        <source>Multiple duplicate</source>
        <translation>Множинне дублювання</translation>
    </message>
    <message>
        <source>Change Image Offset</source>
        <translation>Змінити зміщення зображення</translation>
    </message>
    <message>
        <source>Change Image Scale</source>
        <translation>Змінити масштабування зображення</translation>
    </message>
    <message>
        <source>X1: %1, Y1: %2
X2: %4, Y2: %5</source>
        <translation>X1: %1, Y1: %2
X2: %4, Y2: %5</translation>
    </message>
    <message>
        <source>X: %1, Y: %2
X: %4, Y: %5</source>
        <translation>X: %1, Y: %2
X: %4, Y: %5</translation>
    </message>
    <message>
        <source>Apply text style</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Undo: %1</source>
        <comment>f.e. Undo: Move</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Redo: %1</source>
        <comment>f.e. Redo: Move</comment>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>No object frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Reset control point</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Reset control points</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Apply image effects</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Insert frame</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Adjust frame to the image size</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Set start and end arrows</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>UndoPalette</name>
    <message>
        <source>Initial State</source>
        <translation>Початковий стан</translation>
    </message>
    <message>
        <source>Action History</source>
        <translation>Історія подій</translation>
    </message>
    <message>
        <source>Show selected object only</source>
        <translation>Показувати лише вибраний об&apos;єкт</translation>
    </message>
    <message>
        <source>&amp;Undo</source>
        <translation>&amp;Відмінити</translation>
    </message>
    <message>
        <source>&amp;Redo</source>
        <translation>&amp;Повторити</translation>
    </message>
</context>
<context>
    <name>UndoWidget</name>
    <message>
        <source>%1: %2</source>
        <comment>undo target: action (f.e. Text frame: Resize)</comment>
        <translation>%1: %2</translation>
    </message>
</context>
<context>
    <name>UnicodeSearchBase</name>
    <message>
        <source>Unicode Search</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Search:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hex</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Meaning</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>UpgradeChecker</name>
    <message>
        <source>Attempting to get the Scribus version update file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>(No data on your computer will be sent to an external location)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Timed out when attempting to get update file.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Error when attempting to get update file: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>File not found on server</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Could not open version file: %1
Error:%2 at line: %3, row: %4</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>An error occurred while looking for updates for Scribus, please check your internet connection.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>No updates are available for your version of Scribus %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>One or more updates for your version of Scribus (%1) are available:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Please visit www.scribus.net for details.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>This list may contain development versions.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>UsePrinterMarginsDialog</name>
    <message>
        <source>Minimum Margins for Page Size %1</source>
        <translation>Мінімальні поля для розміру сторінки %1</translation>
    </message>
</context>
<context>
    <name>UsePrinterMarginsDialogBase</name>
    <message>
        <source>Use Printer Margins</source>
        <translation>Використовувати поля принтера</translation>
    </message>
    <message>
        <source>Select &amp;Printer:</source>
        <translation>Вибрати &amp;принтер:</translation>
    </message>
    <message>
        <source>Margins</source>
        <translation>Поля</translation>
    </message>
    <message>
        <source>Right:</source>
        <translation>Праве:</translation>
    </message>
    <message>
        <source>&amp;Top:</source>
        <translation>&amp;Верхнє:</translation>
    </message>
    <message>
        <source>&amp;Bottom:</source>
        <translation>&amp;Нижнє:</translation>
    </message>
    <message>
        <source>&amp;Left:</source>
        <translation>&amp;Ліве:</translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation>&amp;Гаразд</translation>
    </message>
    <message>
        <source>Alt+O</source>
        <translation>Alt+Г</translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation>В&amp;ихід</translation>
    </message>
    <message>
        <source>Alt+C</source>
        <translation>Alt+И</translation>
    </message>
</context>
<context>
    <name>ValueDialog</name>
    <message>
        <source>Insert value</source>
        <translation>Введіть значення</translation>
    </message>
    <message>
        <source>Enter a value then press OK.</source>
        <translation>Введіть значення і натисніть Гаразд.</translation>
    </message>
    <message>
        <source>Enter a value then press OK</source>
        <translation>Введіть значення і натисніть Гаразд</translation>
    </message>
    <message>
        <source>Alt+O</source>
        <translation>Alt+O</translation>
    </message>
    <message>
        <source>Send your value to the script</source>
        <translation>Передати ваше значення сценарію</translation>
    </message>
</context>
<context>
    <name>WerkToolB</name>
    <message>
        <source>Tools</source>
        <translation type="obsolete">Стандартні інструменти</translation>
    </message>
    <message>
        <source>Properties...</source>
        <translation type="obsolete">Властивості...</translation>
    </message>
</context>
<context>
    <name>WerkToolBP</name>
    <message>
        <source>Text</source>
        <translation type="obsolete">Текст</translation>
    </message>
    <message>
        <source>Link</source>
        <translation type="obsolete">Ссилка</translation>
    </message>
    <message>
        <source>Button</source>
        <translation type="obsolete">Кнопка</translation>
    </message>
    <message>
        <source>Text Field</source>
        <translation type="obsolete">Текстове поле</translation>
    </message>
    <message>
        <source>Check Box</source>
        <translation type="obsolete">Вибіркове поле</translation>
    </message>
    <message>
        <source>Combo Box</source>
        <translation type="obsolete">Комбінований випадаючий список</translation>
    </message>
    <message>
        <source>List Box</source>
        <translation type="obsolete">Випадаючий список</translation>
    </message>
    <message>
        <source>PDF Tools</source>
        <translation type="obsolete">PDF Інструменти</translation>
    </message>
    <message>
        <source>Insert PDF Fields</source>
        <translation type="obsolete">Вставити PDF поля</translation>
    </message>
    <message>
        <source>Insert PDF Annotations</source>
        <translation type="obsolete">Вставити PDF аннотації</translation>
    </message>
</context>
<context>
    <name>gtFileDialog</name>
    <message>
        <source>Choose the importer to use</source>
        <translation>Вибрати імпортер</translation>
    </message>
    <message>
        <source>Automatic</source>
        <translation>Автоматичний</translation>
    </message>
    <message>
        <source>Import text without any formatting</source>
        <translation>Імпортувати текст без ніякого форматування</translation>
    </message>
    <message>
        <source>Importer:</source>
        <translation>Імпортер:</translation>
    </message>
    <message>
        <source>Encoding:</source>
        <translation>Кодування:</translation>
    </message>
    <message>
        <source>Import Text Only</source>
        <translation>Імпортувати лише текст</translation>
    </message>
    <message>
        <source>Open</source>
        <translation type="unfinished">Відчинити</translation>
    </message>
</context>
<context>
    <name>gtImporterDialog</name>
    <message>
        <source>Choose the importer to use</source>
        <translation>Вибрати імпортер для використання</translation>
    </message>
    <message>
        <source></source>
        <translation></translation>
    </message>
    <message>
        <source>Remember association</source>
        <translation>Пам&quot;ятати ассоціацію</translation>
    </message>
    <message>
        <source>Remember the file extension - importer association and do not ask again to select an importer for files of this type.</source>
        <translation>Запам&apos;ятати ассоціацію між розширенням імені файла та вибраним імпортером і більне не задавати питання про вибір імпортера для цього типу файлів.</translation>
    </message>
</context>
<context>
    <name>nftdialog</name>
    <message>
        <source>New From Template</source>
        <translation>Новий з шаблона</translation>
    </message>
    <message>
        <source>All</source>
        <translation>Всі</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation>Розмір сторінки</translation>
    </message>
    <message>
        <source>Colors</source>
        <translation>Кольори</translation>
    </message>
    <message>
        <source>Description</source>
        <translation>Опис</translation>
    </message>
    <message>
        <source>Usage</source>
        <translation>Використання</translation>
    </message>
    <message>
        <source>Author</source>
        <translation>Автор</translation>
    </message>
    <message>
        <source>Created with</source>
        <translation>Створено</translation>
    </message>
    <message>
        <source>&amp;Remove</source>
        <translation>Ви&amp;далити</translation>
    </message>
    <message>
        <source>&amp;Open</source>
        <translation>&amp;Відчинити</translation>
    </message>
    <message>
        <source>Downloading Templates</source>
        <translation>Зкачати шаблони</translation>
    </message>
    <message>
        <source>Installing Templates</source>
        <translation>Установка шаблонів</translation>
    </message>
    <message>
        <source>Extract the package to the template directory ~/.scribus/templates for the current user or PREFIX/share/scribus/templates for all users in the system.</source>
        <translation>Розпакуйте архів у директорію для шаблонів користувача (~/.scribus/templates) або в PREFIX/share/scribus/templates для доступу всіх користувачів системи.</translation>
    </message>
    <message>
        <source>Preparing a template</source>
        <translation>Приготування шаблона</translation>
    </message>
    <message>
        <source>Removing a template</source>
        <translation>Видалення шаблона</translation>
    </message>
    <message>
        <source>Translating template.xml</source>
        <translation>Переклад template.xml</translation>
    </message>
    <message>
        <source>Document templates can be found at http://www.scribus.net/ in the Downloads section.</source>
        <translation>Шаблони документів можна знайти на  http://www.scribus.net/ у розділі матеріалів для зкачування.</translation>
    </message>
    <message>
        <source>Make sure images and fonts you use can be used freely. If fonts cannot be shared do not collect them when saving as a template.</source>
        <translation>Впевніться, що зображення та шрифти, використані в шаблоні, дозволяється розповсюджувати. Якщо існують обмеження на їх розповсюдження, то не використовуйте їх &quot;збірку&quot; в документ при запису шаблона.</translation>
    </message>
    <message>
        <source>The template creator should also make sure that the Installing Templates section above applies to their templates as well. This means a user should be able to download a template package and be able to extract them to the template directory and start using them.</source>
        <translation>Автор шаблона повинен впевнитися, що користувач зможе звантажити пакет з його шаблоном і інсталювати його, розпакувавши шаблон у відповідну директорію.</translation>
    </message>
    <message>
        <source>Removing a template from the New From Template dialog will only remove the entry from the template.xml, it will not delete the document files. A popup menu with remove is only shown if you have write access to the template.xml file.</source>
        <translation>Видалення шаблона з діалога &quot;Новий документ з шаблона&quot; лише видалить відповідний пункт з template.xml. Файли не буде видалено.  Діалог видалення активується лише при наявності прав редагування файла template.xml.</translation>
    </message>
    <message>
        <source>Copy an existing template.xml to a file called template.lang_COUNTRY.xml (use the same lang code that is present in the qm file for your language), for example template.fi.xml for Finnish language template.xml. The copy must be located in the same directory as the original template.xml so Scribus can load it.</source>
        <translation>Скопіюйте існуючий файл template.xml у файл template.lang_COUNTRY.xml, де COUNTRY - це код країни який відповідає коду використаному в .qm файлі для Вашої мови. Наприклад &quot;fi&quot; для фінської мови. Ця копія має бути розташована у тій же директорії, що й template.xml для того, щоб Scribus міг її завантажити.</translation>
    </message>
    <message>
        <source>Date</source>
        <translation>Дата</translation>
    </message>
</context>
<context>
    <name>patternDialogBase</name>
    <message>
        <source>Patterns</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Load</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Load Set</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Remove</source>
        <translation type="unfinished">Видалити</translation>
    </message>
    <message>
        <source>OK</source>
        <translation type="unfinished">Гаразд</translation>
    </message>
    <message>
        <source>Cancel</source>
        <translation type="unfinished">Вихід</translation>
    </message>
    <message>
        <source>Remove All</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>satdialog</name>
    <message>
        <source>Save as Template</source>
        <translation>Записати як шаблон</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Ім&apos;я</translation>
    </message>
    <message>
        <source>Category</source>
        <translation>Категорія</translation>
    </message>
    <message>
        <source>Page Size</source>
        <translation>Розмір сторінки</translation>
    </message>
    <message>
        <source>Colors</source>
        <translation>Кольори</translation>
    </message>
    <message>
        <source>Description</source>
        <translation>Опис</translation>
    </message>
    <message>
        <source>Usage</source>
        <translation>Використання</translation>
    </message>
    <message>
        <source>Author</source>
        <translation>Автор</translation>
    </message>
    <message>
        <source>Email</source>
        <translation>Адреса електронної пошти</translation>
    </message>
    <message>
        <source>More Details</source>
        <translation>Більш детально</translation>
    </message>
    <message>
        <source>OK</source>
        <translation>Гаразд</translation>
    </message>
    <message>
        <source>Less Details</source>
        <translation>Менш детально</translation>
    </message>
    <message>
        <source>Legal</source>
        <translation>Юридичний</translation>
    </message>
    <message>
        <source>Letter</source>
        <translation>Лист</translation>
    </message>
    <message>
        <source>Tabloid</source>
        <translation>Таблоїд</translation>
    </message>
    <message>
        <source>landscape</source>
        <translation>Горизонтально</translation>
    </message>
    <message>
        <source>portrait</source>
        <translation>Вертикально</translation>
    </message>
    <message>
        <source>custom</source>
        <translation>Установлено користувачем</translation>
    </message>
</context>
<context>
    <name>tfDia</name>
    <message>
        <source>Create filter</source>
        <translation>Створити фільтр</translation>
    </message>
    <message>
        <source>C&amp;lear</source>
        <translation>О&amp;чистити</translation>
    </message>
    <message>
        <source>&amp;Delete</source>
        <translation>&amp;Видалити</translation>
    </message>
    <message>
        <source>Choose a previously saved filter</source>
        <translation>Вибрати попередньо записаний фільтр</translation>
    </message>
    <message>
        <source>Give a name to this filter for saving</source>
        <translation>Дайте ім&quot;я цьому фільтру для його запису</translation>
    </message>
    <message>
        <source>Give a name for saving</source>
        <translation>Дайте ім&quot;я для запису</translation>
    </message>
</context>
<context>
    <name>tfFilter</name>
    <message>
        <source>Disable or enable this filter row</source>
        <translation>Активувати або деактивувати цей рядок фільтрів</translation>
    </message>
    <message>
        <source>Remove this filter row</source>
        <translation>Видалити цей рядок фільтрів</translation>
    </message>
    <message>
        <source>Add a new filter row</source>
        <translation>Додати новий рядок фільтрів</translation>
    </message>
    <message>
        <source>to</source>
        <translation>до</translation>
    </message>
    <message>
        <source>and</source>
        <translation>і</translation>
    </message>
    <message>
        <source>remove match</source>
        <translation>видалити співпадання</translation>
    </message>
    <message>
        <source>do not remove match</source>
        <translation>не видаляти співпадання</translation>
    </message>
    <message>
        <source>words</source>
        <translation>слова</translation>
    </message>
    <message>
        <source>Remove</source>
        <translation>Видалити</translation>
    </message>
    <message>
        <source>Replace</source>
        <translation>Замінити</translation>
    </message>
    <message>
        <source>Apply</source>
        <translation>Застосувати</translation>
    </message>
    <message>
        <source>Value at the left is a regular expression</source>
        <translation>Значення зліва - це регулярний вираз</translation>
    </message>
    <message>
        <source>with</source>
        <translation>з</translation>
    </message>
    <message>
        <source>paragraph style</source>
        <translation>стиль абзаца</translation>
    </message>
    <message>
        <source>all instances of</source>
        <translation>всі приклади</translation>
    </message>
    <message>
        <source>all paragraphs</source>
        <translation>всі абзаци</translation>
    </message>
    <message>
        <source>paragraphs starting with</source>
        <translation>абзаци починаються з</translation>
    </message>
    <message>
        <source>paragraphs with less than</source>
        <translation>абзаци з менш ніж</translation>
    </message>
    <message>
        <source>paragraphs with more than</source>
        <translation>абзаци з більш ніж</translation>
    </message>
</context>
</TS>
