function EnableButtons(div)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("disabled");});
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("unselected");});
}
function DisableButtons(div)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.remove("unselected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("disabled");});
}
function SelectButton(div, index)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("unselected");});
  if(index != -1)div.querySelectorAll("button")[index].classList.remove("unselected");
  if(index != -1)div.querySelectorAll("button")[index].classList.add("selected");
  if(typeof Draw !== 'undefined')Draw();
}
function EnableButton(button)
{
  button.classList.remove("selected");
  button.classList.remove("disabled");
  button.classList.add("unselected");
}
function DisableButton(button)
{
  if (button) 
  {
    button.classList.remove("selected");
    button.classList.remove("unselected");
    button.classList.add("disabled");
  }
}

class Item
{
    constructor(type, name, thumbnailurl, specifications, quantity ,price ,packaging, gst, description)
    {
        this.type = type;
        this.name = name;
        this.thumbnailurl = thumbnailurl;
        this.specifications = specifications;
        this.quantity = quantity;
        this.price = price;
        this.gst = gst;
        this.packaging = packaging;
        this.description = description;
    }
};
class Cart
{
  constructor()
  {
    this.items = [];
  }
  Load()
  {
    var cartitems = JSON.parse(localStorage.getItem('cart'));
    if(cartitems != undefined)
    {
      this.items = cartitems;
      if(this.Count())
      {
        document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
        document.querySelector(".TopRibbonTextCartQuantity").style.display = "flex";
      }
    }
    else
    {
      document.querySelector(".TopRibbonTextCartQuantity").style.display = "none";
    }
  }
  Count()
  {
    return this.items.length;
  }
  Get(index)
  {
    return this.items[index];
  }
  Add(item)
  {
    var found = false;
    for(var i = 0; i < this.items.length; i++)
    {
      if(this.items[i].type == item.type && this.items[i].name == item.name && this.items[i].specifications == item.specifications)
      {
        this.items[i].quantity += item.quantity;
        found = true;
      }
    }
    if(!found)
        this.items.push(item);

    localStorage.setItem('cart', JSON.stringify(this.items));
    document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
    document.querySelector(".TopRibbonTextCartQuantity").style.display = "flex";
  }
  Remove(index)
  {
    this.items.splice(index, 1);
    localStorage.setItem('cart', JSON.stringify(this.items));
    document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
    if(this.Count() == 0)document.querySelector(".TopRibbonTextCartQuantity").style.display = "none";
  }
};
var cart;
if(cart == null)
{
  cart = new Cart();
}
cart.Load();

class User
{
  constructor()
  {
    this.status = undefined;
    this.phone = "";
    this.password = "";
    this.name = "";
    this.orders = [];
  }
  Authenticate()
  {
    const userdata = JSON.parse(localStorage.getItem('user'));
    if (userdata) 
      {
      this.phone = userdata.phone;
      this.password = userdata.password;
      this.name = userdata.name;
      this.email = userdata.email;
      this.address = userdata.address;
    }
 
    if(this.phone != undefined && this.password != undefined)
    {
      const encodedcredentials = btoa(`${this.phone}:${this.password}`);
      const url = `http://192.168.1.5/api/authenticate?credentials=${encodedcredentials}`;    
      fetch(url).then(response => 
      {
        if(response.status == 200)
        {
          response.body.getReader().read().then(({value}) =>
          {
            if(value != undefined)
            {
              if(value[0] == 1)
              {
                document.querySelectorAll(".TopRibbonText")[4].innerHTML = `<span class="material-symbols-outlined" style="font-size:40px;">account_circle</span>`;
                let namearray = new Uint8Array(value.slice(4));
                let namestring = '';
                for (let i = 0; i < namearray.length; i++) 
                {
                  if (namearray[i] === 0) break;
                  namestring += String.fromCharCode(namearray[i]);
                }
                this.name = namestring;
                this.status = true;
              }
              else
              {
                document.querySelectorAll(".TopRibbonText")[4].innerHTML = "Login";
                this.status = false;
              }
            }
          });
        }
      });  
    }
    document.querySelectorAll(".TopRibbonText")[4].innerHTML = "Login";
  }
  LogIn(phone, password)
  {
    this.phone = phone;
    this.password = password;
    this.status = undefined;
    localStorage.setItem('user', JSON.stringify(this));
    this.Authenticate();
  }
  LogOut()
  {
    document.querySelectorAll(".TopRibbonText")[4].innerHTML = "Login";
    localStorage.removeItem('user');
    this.status = false;
    this.phone = "";
    this.password = "";
    this.name = "";
    this.orders = [];
  }
};
var user;
if(user == null)
{
  user = new User();
}
user.Authenticate();