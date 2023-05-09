var car = {
    registrationNumber: "GA12345",
    brand: "Toyota",

    displayDetails: function(ownerName) {
        console.log(ownerName + ",this is your car:" + this.registrationNumber + " " + this.brand);
    }
}

car.displayDetails("Viviane1");

var myCarDetails = car.displayDetails;
myCarDetails();


var myCarDetails = car.displayDetails.bind(car, "Viviane2");
myCarDetails();

car.displayDetails.apply(car, ["Viviane3"]);
car.displayDetails.call(car, "Viviane4");

function sumOfNumbers() {
    var total = 0;
    for (var i = 0; i < arguments.length; i++) {
        total += arguments[i];
    }
    return total;
};

var sum = sumOfNumbers(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
console.log(sum);


var sum = sumOfNumbers.call(null, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

var updateZipCode = function() {
    console.log(this);
};

updateZipCode();

updateZipCode.call({zip : "11787"});

"use strict";

var person = {
    name : "John",
    prop: {
        name : "Viviane",
        getName : function() {
            return this.name;
        }
    }
};

var name = person.prop.getName.bind(person);
console.log(name());

var name = person.prop.getName();
console.log(name);
