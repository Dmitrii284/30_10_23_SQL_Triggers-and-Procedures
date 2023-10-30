/*Triggers and procedures
* 
* Триггеры и процедуры являются важными компонентами SQL. Они используются для автоматизации операций, 
обеспечения целостности данных и выполнения сложных запросов.

Триггеры - это специальные SQL-команды, которые выполняются автоматически при выполнении определенных действий с данными,
таких как вставка, обновление или удаление записей из таблицы.
Триггеры позволяют контролировать изменения в данных и выполнять дополнительные операции, такие как отправка уведомлений или выполнение расчетов.

Процедуры - это блоки кода, которые могут быть выполнены многократно. Они позволяют объединять несколько SQL-команд в один блок,
который может быть вызван из разных мест программы. Процедуры упрощают написание и сопровождение кода, 
а также позволяют создавать более модульные и гибкие приложения.

Обе технологии могут использоваться для улучшения безопасности, надежности и производительности приложений, использующих SQL. 
Однако они требуют от разработчика хорошего понимания работы с базами данных и SQL, а также умения писать эффективный код.


Да, я могу привести примеры триггеров в SQL. Вот несколько примеров:

1) AFTER INSERT триггер: Этот триггер выполняется после успешной вставки новой записи в таблицу.
Он может быть использован для выполнения дополнительных операций, таких как отправка уведомления или обновление другой таблицы.
2) BEFORE UPDATE триггер: Этот триггер запускается перед обновлением записи в таблице.
Он может проверять условия обновления и откатывать изменения, если они не соответствуют определенным критериям.
3) INSTEAD OF триггер: Этот триггер используется, когда необходимо переопределить стандартное поведение операции обновления или удаления.
Например, он может быть использован для сохранения истории изменений или для выполнения резервного копирования данных перед удалением.
4) FOR EACH ROW триггер: Это особый тип триггера, который выполняется для каждой строки, затронутой операцией вставки, обновления или удаления.
Он может использоваться для выполнения операций на уровне строки, таких как обновление счетчика или применение условий фильтрации.
5) ON DELETE CASCADE триггер: Этот триггер автоматически удаляет связанные записи из других таблиц при удалении основной записи.
Он используется для обеспечения ссылочной целостности и предотвращения появления “висячих” записей.


//////////////////////////
ТРИГЕР 
//////////////////
Триггер chk_cvalification предназначен для проверки валидности данных при вставке новых записей в таблицу examinations. 
Если вставка происходит с помощью инструкции INSERT, то вместо нее будет выполнена процедура chk_cvalification.
Это позволяет контролировать данные перед их вставкой в таблицу.
............
WITH APPEND
................
Инструкция WITH APPEND указывает, что новые данные должны быть добавлены в конец таблицы, а не перезаписывать существующие записи.
Это может быть полезно, если вы хотите сохранить историю изменений или добавить данные в таблицу в режиме реального времени.

...........
INSERT
.......
Если вставка происходит с помощью инструкции INSERT, то вместо нее будет выполнена процедура chk_cvalification.
Это позволяет контролировать данные перед их вставкой в таблицу.


Пример использования этого триггера может выглядеть так:

CREATE TRIGGER chk_cvalification ON hospital1.dbo.examinations
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;

    IF EXISTS (SELECT * FROM inserted WHERE cvalification NOT IN (1, 2, 3))
    BEGIN
        THROW 51000, 'Invalid cvalification value', 1;
    END

    INSERT INTO examinations (cvalification)
    SELECT i.cvalification
    FROM inserted i;
END;
GO

В этом примере триггер проверяет, что значение поля cvalification новой записи находится в диапазоне от 1 до 3.
Если это не так, то выдается ошибка и вставка не выполняется. Если все в порядке, то запись добавляется в таблицу.

Пример:
@float_val- Так объявляют имя переменной

USE hospital1;
GO

CREATE TRIGGER [hospital1].[dbo].[chk_cvalification] ON [dbo].[examinations]

INSTEAD OF INSERT
AS
BEGIN
DECLARE @float_val FLOAT = 3
SET @float_val = 6.8
IF @float_val > 0.5
    BEGIN
     SET @float_val = @float_val +1.8
    END

END

Пример:

В данном коде есть несколько проблем:

1. В строке "USE hospital1;" есть опечатка, вместо "ч" должна быть буква "C". То есть правильно будет "USE hospital1;".

2. Строка "--@float_val- Так объявляют имя переменной" является комментарием, но такой комментарий не имеет смысла и нужно удалить эту строку.

3. В строке "DECLARE @float_val FLOAT = 3" объявление переменной @float_val содержит ошибку.
Нельзя задавать значение переменной при ее объявлении внутри тела триггера. Нужно переписать эту строку так: "DECLARE @float_val FLOAT".

4. Дальше в строке "SET @float_val = 6.8" переменной @float_val присваивается значение 6.8, что не соответствует предыдущему объявлению (3).
Если нужно присвоить значение 6.8, то нужно удалить предыдущее объявление и объявить переменную и присвоить ей значение так: "DECLARE @float_val FLOAT = 6.8".

5. В строках "SET @val = (SELECT @float_val INT = SELECT COUNT(*) FROM inserted )" и "IF (SELECT COUNT(*) FROM insert) > 1" используется
неправильное ключевое слово "INT". Нужно удалить его, чтобы эти строки выглядели так:
   "SET @val = (SELECT @float_val = SELECT COUNT(*) FROM inserted )"
   "IF (SELECT COUNT(*) FROM inserted) > 1"

6. В строке "IF (SELECT COUNT(*) FROM insert) > 1" таблица "insert" должна быть "inserted".
То есть правильно будет "IF (SELECT COUNT(*) FROM inserted) > 1".

Исправленный код:

USE hospital1;
GO

CREATE TRIGGER [hospital1].[dbo].[chk_cvalification] ON [dbo].[examinations]

INSTEAD OF INSERT
AS
BEGIN
DECLARE @float_val FLOAT = 6.8
IF @float_val > 0.5
 BEGIN
  SET @float_val = @float_val +1.8
 END
 DECLARE @val INT
 SET @val = (SELECT @float_val = SELECT COUNT(*) FROM inserted)
 IF (SELECT COUNT(*) FROM inserted) > 1
  BEGIN
   PRINT 'Нельзя пихать больше одной записи'
   ROLLBACK TRANSACTION
  END
 ELSE
  BEGIN
   INSERT INTO examinations(
     [begin_time]
     , [end_time]
     , [procedure_id]
     , [doctor_id]
     , [ward_id])

   (SELECT * FROM inserted);
  END

END


\\\\\\\\\\\\\
Задача
Для табдици [dbo].[donations] создать тригер на запрет добавления донатов для тех отделений у которых нет палаты.
сколько палат в каждом департаменте.
запрет на изменение дат отпусков если новые даты затрагивают назначение процедуры.

//////////////

Чтобы решить данную задачу, необходимо выполнить следующие шаги:

1. Создать триггер на таблице dbo.donations, который будет выполняться перед добавлением новой записи. Для этого можно использовать следующий код:

CREATE TRIGGER trg_prevent_donation_without_ward
ON [dbo].[donations]
INSTEAD OF INSERT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted i
               INNER JOIN [dbo].[departments] d ON i.department_id = d.id
               LEFT JOIN [dbo].[wards] w ON d.id = w.departments_id
               WHERE w.id IS NULL)
    BEGIN
        RAISERROR('Cannot add donation for departments without ward.', 16, 1)
        ROLLBACK
    END
    ELSE
    BEGIN
        INSERT INTO [dbo].[donations] (amount, date, department_id, sponsor_id)
        SELECT amount, date, department_id, sponsor_id FROM inserted
    END
END

2. Для получения количества палат в каждом департаменте можно выполнить следующий запрос:

SELECT d.name AS department_name, COUNT(*) AS ward_count
FROM [dbo].[departments] d
JOIN [dbo].[wards] w ON d.id = w.departments_id
GROUP BY d.name

3. Чтобы запретить изменение дат отпусков, если новые даты затрагивают назначение процедуры, необходимо создать 
триггер на таблице с отпусками. Однако, в предоставленных скриптах таблиц нет информации о таблице отпусков и процедурах.
Поэтому, для создания соответствующего триггера, понадобится информация о структуре этих таблиц.

Необходимо убедиться, что предоставленные скрипты таблиц содержат всю необходимую информацию для решения задачи.
............
IF EXISTS
............
IF EXISTS - это условный оператор в SQL, который позволяет выполнить блок кода только в том случае, если указанная проверка вернет результат.
В данном случае проверка проверяет, существует ли запись в таблице inserted с некорректным значением поля cvalification. Если такая запись существует,
то будет выброшено исключение с ошибкой и вставка не будет выполнена. Если же таких записей не существует, вставка будет выполнена без проблем.


USE [hospital1]
GO

/****** Object:  Table [dbo].[vacations]    Script Date: 30.10.2023 21:25:02 ******/
/*SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE[dbo].[vacations](
    [id][int] IDENTITY(1, 1) NOT NULL,
    [begin_date][date] NOT NULL,
    [end_date][date] NOT NULL,
    [doctor_id][int] NOT NULL,
    PRIMARY KEY CLUSTERED
    (
        [id] ASC
    )WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON[PRIMARY]
    ) ON[PRIMARY]
    GO

    ALTER TABLE[dbo].[vacations]  WITH CHECK ADD  CONSTRAINT[vacations_fk0] FOREIGN KEY([doctor_id])
    REFERENCES[dbo].[doctors]([id])
    GO

    ALTER TABLE[dbo].[vacations] CHECK CONSTRAINT[vacations_fk0]
    GO
    */

/*USE [hospital1]
GO

/****** Object:  Table [dbo].[examinations]    Script Date: 30.10.2023 21:24:42 ******/
/*SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE[dbo].[examinations](
    [id][int] IDENTITY(1, 1) NOT NULL,
    [begin_time][datetime] NOT NULL,
    [end_time][datetime] NOT NULL,
    [procedure_id][int] NOT NULL,
    [doctor_id][int] NOT NULL,
    [ward_id][int] NOT NULL,
    PRIMARY KEY CLUSTERED
    (
        [id] ASC
    )WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON[PRIMARY]
    ) ON[PRIMARY]
    GO

    ALTER TABLE[dbo].[examinations]  WITH CHECK ADD  CONSTRAINT[examinations_fk0] FOREIGN KEY([procedure_id])
    REFERENCES[dbo].[procedures]([id])
    GO

    ALTER TABLE[dbo].[examinations] CHECK CONSTRAINT[examinations_fk0]
    GO

    ALTER TABLE[dbo].[examinations]  WITH CHECK ADD  CONSTRAINT[examinations_fk1] FOREIGN KEY([doctor_id])
    REFERENCES[dbo].[doctors]([id])
    GO

    ALTER TABLE[dbo].[examinations] CHECK CONSTRAINT[examinations_fk1]
    GO

    ALTER TABLE[dbo].[examinations]  WITH CHECK ADD  CONSTRAINT[examinations_fk2] FOREIGN KEY([ward_id])
    REFERENCES[dbo].[wards]([id])
    GO

    ALTER TABLE[dbo].[examinations] CHECK CONSTRAINT[examinations_fk2]
    GO


    */

