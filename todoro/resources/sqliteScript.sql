drop table if exists tproject;
create table tproject(
       id INTEGER PRIMARY KEY AUTOINCREMENT , 
       name TEXT
);

drop table if exists tpomodoro;
create table tpomodoro(
       id INTEGER PRIMARY KEY AUTOINCREMENT , 
       project INTEGER, 
       description TEXT, 
       startTime datetime, 
       endtime DATETIME,
       productivity INTEGER,
       FOREIGN KEY (project) REFERENCES tproject(id)
       );

drop table if exists tbreak;
create table tbreak(
       id INTEGER PRIMARY KEY AUTOINCREMENT , 
       project INTEGER,
       startTime DATETIME, 
       endTime DATETIME,
       mintsOrig INTEGER,
       FOREIGN KEY (project) REFERENCES tproject(id)
       );

insert into tproject VALUES(NULL,'default');