


- [ ] Обойти рекурсивно все записи, построить список "чистых" типов - clean сериализованное имя типа -> Record типа.
      Список чистых типов возрастает по длине чистого имени.
      Обход делаем по этому списку (по возрастанию длины).

- [ ] Если нет суффикса (это важно), по needAutoSubst проверяем, не надо ли делать автозамену.
      Если надо - генерим автозамену, авозаменяем, строим заново список чистых типов.
      После каждой сгенерированной автозамены начинаем заново.
      Если не было генерации автозамены - прекращаем цикл.
       (после каждой автозамены).



- [ ] Если у типа есть суффикс и есть `::` в суффиксе - то это под замену, генерим имя на базе того, что после `::`