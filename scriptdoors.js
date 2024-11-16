var shop_menu_innerhtml = document.querySelector(".shop-menu").innerHTML;

for(var i=1;i<=46;i++)
{
    shop_menu_innerhtml += `
    <div class="shop-menu-items">
      <a href="shop-doors.html"><img class="shop-menu-items-img" src="images/Doors/`+i+`.jpg"></a><br>
      <h2>Door-`+i+`</h2>
    </div>
    `;
}

document.querySelector(".shop-menu").innerHTML = shop_menu_innerhtml;