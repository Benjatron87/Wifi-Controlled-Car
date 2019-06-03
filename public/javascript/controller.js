

$(".button").click(function(){

    let val = $(this).attr("data-id");
    let obj = {
        direction: val
    }

    console.log(val);

    $.post("/direction", obj);
})