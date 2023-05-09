search = document.querySelector("[data-search]");
container = document.querySelector("[data-user-cards-container]");
template = document.querySelector("[data-user-template]");

let users = [];

search.addEventListener("input", (e) => {
    const value =   e.target.value.toLowerCase();
    users.forEach((user) => {
        const isVisible = user.username.toLowerCase().includes(value) || user.useremail.toLowerCase().includes(value)|| user.website.toLowerCase().includes(value);
        user.elt.classList.toggle("hide", !isVisible);
    });
});

async function searchUsers(){
    const response = await fetch("https://jsonplaceholder.typicode.com/users",{
        method: "GET",
        mode: "cors",
        credentials: "same-origin",
        headers: {
            "Content-Type": "application/json"
        }
    });
    const data = await response.json();
    await new Promise((resolve, reject) => setTimeout(resolve, 1000));
    update(data);
    return data;
}

searchUsers().then(data => alert(data));
alert("bonjour");

async function show() {
    let res = await fetch("https://dummyjson.com/products/1");
    let data = await res.json();
    let img = document.createElement("img");
    img.src = data.images[0];
    document.body.append(img);
    await new Promise((resolve, reject) => setTimeout(resolve, 3000));
    //img.remove();
    return data;
}

//show().then(data => alert(data.title));

// fetch("https://jsonplaceholder.typicode.com/users",{
//    method: "GET",
//    mode: "cors",
//    credentials: "same-origin",
//    headers: {
//       "Content-Type": "application/json"
//     }
//   }
// )
// .then((response)=> response.json())
//   .then(data=> update(data));

function update(data){
    users= data.map(user=> {
        const card= template.content.cloneNode(true).children[0]
        const header= card.querySelector("[data-header]");
        const body= card.querySelector("[data-body]");
        header.textContent= user.name;
        body.innerHTML= user.email + "</br> " + user.website + "</br>" + user.address.city;
        container.appendChild(card);
        return {username: user.name, useremail: user.email,elt: card};
    });
}



