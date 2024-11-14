var shop_menu_innerhtml = document.querySelector(".shop-menu").innerHTML;

for(var i=1;i<=27;i++)
{
    shop_menu_innerhtml += `
    <div class="shop-menu-items">
      <a href="shop-jali.html"><img class="shop-menu-items-img" src="images/Mandir/`+i+`.jpg"></a><br>
      <h2>Mandir-`+i+`</h2>
    </div>
    `;
}

document.querySelector(".shop-menu").innerHTML = shop_menu_innerhtml;