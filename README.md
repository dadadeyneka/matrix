matrix
======

проект розробки класа матриці

Виконуються такі операції як
віднімання, додавання, множення матриць матриць. 
Знаходимо мінор матриці(для його виділення з матриці, ми його видаляємо), 
який надалі використовується для знаходження детермінанта матриці розмірності більше, ніж 3х3
Виконуються такі операції (прописані окремими функціями) як знаходження детермінанта, транспонування матриці та 
знаходження оберненої матриці за допомогою транспонованого значення мінора матриці та детермінанта заданої матриці 


Нечітко виокремлені вимоги до матриці. Треба сюди записати усі методи класу з поміткою, реалізовані вони в програмі чи ні.
Не вистачає методів для детермінанту, оберненої матриці, транспонування.
Також Ви використовуєте клас Array, який шукається в файлі array.h (має бути в самому проекті),  а його нема. Виділіть також вимоги до класу Array (продивившись його використання), та доповнити даний файл вимогами до цього класу.
Також є проблема з файлами. Часто в файли .h записують прототип класу (обявлення класу з усіма полями і методами), а в файл з таким же іменем, як і h. але .cpp, записують реалізацію, але у cpp-файл пишуть #include "matrix.h" наприклад, тобто підключають локальний файл, в якому обявлення.
Зверніть на це увагу і запишіть потрібні частини проекту у відповідні файли.
Дуже прошу не копіювати нічого з інтернету бездумно, тому що допомогати запустити це я не буду. 
Почніть з того, що розберіться з полями класу "матриця" та додайте методи, яких не вистачає. Вкажіть туди звичайний двовимірний динамічний масив і працюйте з тим, що умієте.
