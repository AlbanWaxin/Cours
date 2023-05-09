const add = function () {
    let counter = 0;
    return function () {
      counter += 1; 
      return counter;
    }
  };
  
  add1= add();
  add2= add();
  
  console.log(add1());
  console.log(add1());
  console.log(add1());
  console.log(add1());
  console.log(add1());
  console.log(add1());
  console.log(add2());
  console.log(add2());

  