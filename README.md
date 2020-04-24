# Симуляция жизни

## Описание проекта

Результатом нашего проекта будет модель некой экосистемы. В этой экосистеме будут находится «хищники», «травоядные» и «растения». Каждый объект в экосистеме имеет свои особенности.
«Хищники» имеют определенный срок жизни. Чтобы выжить и не умереть от голода, они должны питаться травоядными.
«Травоядные» также имеют определенный срок жизни. Чтобы выжить, они должны питаться растениями. Они могут умереть из-за разных причин. Первая – естественная смерть из-за нехватки еды или воды. Вторая – они могут быть съедены «хищниками».
«Растения» являются источником питания для травоядных.
Все объекты будут находится на карте местности, где могут быть препятствия (овраги, холмы).
У всех них есть общие особенности: видят в каком-то радиусе, имеют направление движения, в качестве параметра имеют скорость(может меняться в зависимости от другого параметра - голода). Если животные сыты и им не угрожает опасность, они могут размножаться, в результате появляется потомство, соединяющее в себе параметры отца и матери. Особи разделяются по полу.

## Разделение обязанностей

### Никита

* Создание модели системы

### Катя

* Создание классов и структур

### Герман

* Создание графики модели
