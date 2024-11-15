var shop_menu_innerhtml = document.querySelector(".shop-menu").innerHTML;

for(var i=1;i<=30;i++)
  {
      shop_menu_innerhtml += `
      <div class="shop-menu-items">
        <a href="shop-jali.html"><img class="shop-menu-items-img" src="images/Decorative Jali/Mandir Back/`+i+`.jpg"></a><br>
        <h2>MandirDesign-`+i+`</h2>
      </div>
      `;
  }
  
  for(var i=1;i<=20;i++)  
  {
      shop_menu_innerhtml += `
      <div class="shop-menu-items">
        <a href="shop-jali.html"><img class="shop-menu-items-img" src="images/Decorative Jali/Mandir side/`+i+`.jpg"></a><br>
        <h2>MandirSide-`+i+`</h2>
      </div>
      `;
  }

for(var i=1;i<=280;i++)
{
    shop_menu_innerhtml += `
    <div class="shop-menu-items">
      <a href="shop-jali.html"><img class="shop-menu-items-img" src="images/Decorative Jali/Jali/`+i+`.jpg"></a><br>
      <h2>JaliPartition-`+i+`</h2>
    </div>
    `;
}

document.querySelector(".shop-menu").innerHTML = shop_menu_innerhtml;