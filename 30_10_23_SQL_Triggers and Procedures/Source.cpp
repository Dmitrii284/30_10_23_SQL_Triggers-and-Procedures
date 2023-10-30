/*Triggers and procedures
* 
* �������� � ��������� �������� ������� ������������ SQL. ��� ������������ ��� ������������� ��������, 
����������� ����������� ������ � ���������� ������� ��������.

�������� - ��� ����������� SQL-�������, ������� ����������� ������������� ��� ���������� ������������ �������� � �������,
����� ��� �������, ���������� ��� �������� ������� �� �������.
�������� ��������� �������������� ��������� � ������ � ��������� �������������� ��������, ����� ��� �������� ����������� ��� ���������� ��������.

��������� - ��� ����� ����, ������� ����� ���� ��������� �����������. ��� ��������� ���������� ��������� SQL-������ � ���� ����,
������� ����� ���� ������ �� ������ ���� ���������. ��������� �������� ��������� � ������������� ����, 
� ����� ��������� ��������� ����� ��������� � ������ ����������.

��� ���������� ����� �������������� ��� ��������� ������������, ���������� � ������������������ ����������, ������������ SQL. 
������ ��� ������� �� ������������ �������� ��������� ������ � ������ ������ � SQL, � ����� ������ ������ ����������� ���.


��, � ���� �������� ������� ��������� � SQL. ��� ��������� ��������:

1) AFTER INSERT �������: ���� ������� ����������� ����� �������� ������� ����� ������ � �������.
�� ����� ���� ����������� ��� ���������� �������������� ��������, ����� ��� �������� ����������� ��� ���������� ������ �������.
2) BEFORE UPDATE �������: ���� ������� ����������� ����� ����������� ������ � �������.
�� ����� ��������� ������� ���������� � ���������� ���������, ���� ��� �� ������������� ������������ ���������.
3) INSTEAD OF �������: ���� ������� ������������, ����� ���������� �������������� ����������� ��������� �������� ���������� ��� ��������.
��������, �� ����� ���� ����������� ��� ���������� ������� ��������� ��� ��� ���������� ���������� ����������� ������ ����� ���������.
4) FOR EACH ROW �������: ��� ������ ��� ��������, ������� ����������� ��� ������ ������, ���������� ��������� �������, ���������� ��� ��������.
�� ����� �������������� ��� ���������� �������� �� ������ ������, ����� ��� ���������� �������� ��� ���������� ������� ����������.
5) ON DELETE CASCADE �������: ���� ������� ������������� ������� ��������� ������ �� ������ ������ ��� �������� �������� ������.
�� ������������ ��� ����������� ��������� ����������� � �������������� ��������� ��������� �������.


//////////////////////////
������ 
//////////////////
������� chk_cvalification ������������ ��� �������� ���������� ������ ��� ������� ����� ������� � ������� examinations. 
���� ������� ���������� � ������� ���������� INSERT, �� ������ ��� ����� ��������� ��������� chk_cvalification.
��� ��������� �������������� ������ ����� �� �������� � �������.
............
WITH APPEND
................
���������� WITH APPEND ���������, ��� ����� ������ ������ ���� ��������� � ����� �������, � �� �������������� ������������ ������.
��� ����� ���� �������, ���� �� ������ ��������� ������� ��������� ��� �������� ������ � ������� � ������ ��������� �������.

...........
INSERT
.......
���� ������� ���������� � ������� ���������� INSERT, �� ������ ��� ����� ��������� ��������� chk_cvalification.
��� ��������� �������������� ������ ����� �� �������� � �������.


������ ������������� ����� �������� ����� ��������� ���:

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

� ���� ������� ������� ���������, ��� �������� ���� cvalification ����� ������ ��������� � ��������� �� 1 �� 3.
���� ��� �� ���, �� �������� ������ � ������� �� �����������. ���� ��� � �������, �� ������ ����������� � �������.

������:
@float_val- ��� ��������� ��� ����������

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

������:

� ������ ���� ���� ��������� �������:

1. � ������ "USE hospital1;" ���� ��������, ������ "�" ������ ���� ����� "C". �� ���� ��������� ����� "USE hospital1;".

2. ������ "--@float_val- ��� ��������� ��� ����������" �������� ������������, �� ����� ����������� �� ����� ������ � ����� ������� ��� ������.

3. � ������ "DECLARE @float_val FLOAT = 3" ���������� ���������� @float_val �������� ������.
������ �������� �������� ���������� ��� �� ���������� ������ ���� ��������. ����� ���������� ��� ������ ���: "DECLARE @float_val FLOAT".

4. ������ � ������ "SET @float_val = 6.8" ���������� @float_val ������������� �������� 6.8, ��� �� ������������� ����������� ���������� (3).
���� ����� ��������� �������� 6.8, �� ����� ������� ���������� ���������� � �������� ���������� � ��������� �� �������� ���: "DECLARE @float_val FLOAT = 6.8".

5. � ������� "SET @val = (SELECT @float_val INT = SELECT COUNT(*) FROM inserted )" � "IF (SELECT COUNT(*) FROM insert) > 1" ������������
������������ �������� ����� "INT". ����� ������� ���, ����� ��� ������ ��������� ���:
   "SET @val = (SELECT @float_val = SELECT COUNT(*) FROM inserted )"
   "IF (SELECT COUNT(*) FROM inserted) > 1"

6. � ������ "IF (SELECT COUNT(*) FROM insert) > 1" ������� "insert" ������ ���� "inserted".
�� ���� ��������� ����� "IF (SELECT COUNT(*) FROM inserted) > 1".

������������ ���:

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
   PRINT '������ ������ ������ ����� ������'
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
������
��� ������� [dbo].[donations] ������� ������ �� ������ ���������� ������� ��� ��� ��������� � ������� ��� ������.
������� ����� � ������ ������������.
������ �� ��������� ��� �������� ���� ����� ���� ����������� ���������� ���������.

//////////////

����� ������ ������ ������, ���������� ��������� ��������� ����:

1. ������� ������� �� ������� dbo.donations, ������� ����� ����������� ����� ����������� ����� ������. ��� ����� ����� ������������ ��������� ���:

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

2. ��� ��������� ���������� ����� � ������ ������������ ����� ��������� ��������� ������:

SELECT d.name AS department_name, COUNT(*) AS ward_count
FROM [dbo].[departments] d
JOIN [dbo].[wards] w ON d.id = w.departments_id
GROUP BY d.name

3. ����� ��������� ��������� ��� ��������, ���� ����� ���� ����������� ���������� ���������, ���������� ������� 
������� �� ������� � ���������. ������, � ��������������� �������� ������ ��� ���������� � ������� �������� � ����������.
�������, ��� �������� ���������������� ��������, ����������� ���������� � ��������� ���� ������.

���������� ���������, ��� ��������������� ������� ������ �������� ��� ����������� ���������� ��� ������� ������.
............
IF EXISTS
............
IF EXISTS - ��� �������� �������� � SQL, ������� ��������� ��������� ���� ���� ������ � ��� ������, ���� ��������� �������� ������ ���������.
� ������ ������ �������� ���������, ���������� �� ������ � ������� inserted � ������������ ��������� ���� cvalification. ���� ����� ������ ����������,
�� ����� ��������� ���������� � ������� � ������� �� ����� ���������. ���� �� ����� ������� �� ����������, ������� ����� ��������� ��� �������.


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

