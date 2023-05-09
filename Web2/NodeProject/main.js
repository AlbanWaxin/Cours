const myPromise = (nb) => (
    new Promise((resolve, reject) => {
        setTimeout(() => {
            if (nb > 100) reject(`rejected for : ${nb} greater than 100`);
            resolve(`resolved to : ${nb} less than or equal to 100`);
        }, 5000);
    })
);

function doSomeThing(result) {
    console.log(`doSomeThing, ${result}`);
}

function doSomeThingElse() {
    console.log('some code running synchronously');
    console.log('some code running synchronously');
    console.log('some code running synchronously');
}

const nb1 = 10;

const myFunc = (number) => {
    //call MyPromise
    myPromise(number)
        .then((result) => {
            doSomeThing(result)
        })
        .catch((error) => {
            doSomeThing(error)
        })
    
    doSomeThingElse();
}

//myFunc(nb1);

const myAsyncAwaitFunc = async (number) => {
    try {
        const result = await myPromise(number);
        doSomeThing(result);
    } catch (error) {
        doSomeThing(error);
    }
    doSomeThingElse();
}

myAsyncAwaitFunc(nb1);