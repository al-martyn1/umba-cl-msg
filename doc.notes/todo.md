
- [X] Обойти рекурсивно все записи, построить список "чистых" типов - clean сериализованное имя типа -> Record типа.
      Список чистых типов возрастает по длине чистого имени.
      Обход делаем по этому списку (по возрастанию длины).

- [X] Если нет суффикса (это важно/или не важно), по needAutoSubst проверяем, не надо ли делать автозамену.
      Если надо - генерим автозамену, авозаменяем, строим заново список чистых типов.
      После каждой сгенерированной автозамены начинаем заново построение списка чистых типов и автозамену.
      Если не было генерации автозамены - прекращаем цикл.
      Многое поменялось, но в итоге стало как надо.

- [X] Автогенерация имени (если без суффикса). В префиксе находим последнюю `:` и используем то, что после.
      Если пусто или isSame(':') - откат поближе к началу.

- [X] При генерации имени автозамены надо выбрасывать все символы, которые недопустимы в идентификаторе.

- [X] Если у типа есть суффикс и есть `::` в суффиксе - то это под замену, генерим имя на базе того, что после `::`.
      Если это тип - а то бывают ещё методы класса.

