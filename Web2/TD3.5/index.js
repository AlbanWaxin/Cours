Person = function (name,age){
    this.name = name;
    this.age = age;
    this.speak = function(){
        console.log("Im " + this.name + ",and I speak english");
        return "Im " + this.name + ",and I speak english"
    }
}
Person.prototype.describe = function(){
    console.log("description");
    return "description";

}
Person.prototype.tester = function (mot){
    console.log("test " + mot);
    return "test " + mot;
}

Student = function(name,age,dpt){
    Person.call(this,name,age);
    this.dpt = dpt
    this.getinfo = function(){
        console.log(this.dpt);
        console.log(this.name);
        console.log(this.age);
    }
}

let support = function(){
    this.constructor = Student;
}
support.prototype = Person.prototype
s= new support();
Student.prototype =s;
Student.prototype.ajouter = function(){
    console.log("ajout");
}

students = [
    {name:"A",grade: 18},
    {name:"B",grade: 15},
    {name:"C",grade: 12}
]



function render(){
    p1 = new Person("alban",21);
    p2 = new Person("mael",20);
    s1 = new Student("test",43,"STI");
    //t = p1.speak();
    //t2 = p1.describe()
    //t3 = p1.tester("regarde");
    //t4 = p2.tester("moi");
    //t5 = s1.describe();
    //s1.ajouter();
    //console.log(p1.speak === p2.speak);
    //console.log(p1.describe === p2.describe);
    //console.log(s1 instanceof Student);
    //console.log(s1 instanceof Person);
    //console.log(s1 instanceof Object);
    //console.log(s1.constructor);
    console.log(s1.getinfo());
    cb = function (a,b) {return a +b["grade"]};
    console.log(students.reduce(cb,0));
    //console.log(Person.prototype);
    //console.log(Student.prototype);
    document.getElementById("app").innerHTML =`
    <p> hello </p>
    <div style="line-wrap=pre">
    </div>
    `;
    
} 

render();