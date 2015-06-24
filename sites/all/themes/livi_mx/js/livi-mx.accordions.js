(function ($) {
  /**
   * Script for the accordions in the generic page 
   */
  Drupal.behaviors.liviMxAccordions = {
    attach: function (context, settings) {
      $('.accordions_block_wrapper', context).once('accordions', function () {

        function Accordion () {
          if ($(this).parent().next(".body").is(":hidden")) {

            if ($(".accordions_block .field-collection-item-field-accordions-block .title h3").parent().next(".body").is(":visible")) {
              $(".accordions_block .field-collection-item-field-accordions-block .title h3").parent().next(".body").slideUp();
              $(".accordions_block").removeClass("active");
              $(this).parent().next(".body").slideDown();
              $(this).parent().parent().parent().addClass("active");

            } else{

              $(this).parent().next(".body").slideDown();
              $(this).parent().parent().parent().addClass("active");
             
            };

          } else{
            $(this).parent().next(".body").slideUp();
            $(this).parent().parent().parent().removeClass("active");

          };
          
        };

        $( ".accordion_block .title h3" ).click(Accordion);
      });
    }
  };
})(jQuery);