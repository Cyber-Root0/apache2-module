#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>

int bruno_checkislinux(const char *path) {
    if (strstr(path, "linux") != NULL) {
        return 1;
    }
    return 0;
}
char* bruno_render(){
    char *html = ""
    "<!DOCTYPE html>"
    "<html lang='pt-br'>"
    "<head>"
        "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>Mod Apache: Render Linux Imagem by Bruno Alves</title>"
        "<style>body{padding:0;margin:0;text-align:center}"
        "</style>"
    "</head>"
    "<body>"
        "<h1>Linux Image</h1>"
        "<h2>Author: Bruno Alves</h2>"
        "<p>Below is an image of the Linux logo:</p>"
       "<img"
            " src='https://bloximages.newyork1.vip.townnews.com/redandblack.com/content/tncms/assets/v3/editorial/4/59/45940eb2-5403-11e9-a843-db0e4491cc90/5ca13d8453042.image.jpg'"
            " alt='Linux Logo'"
            " width='800'>"
    "</body>"
    "</html>";
    return html;
}
static int brunoalves_showlinux_img(request_rec *r)
{
    if (!r->handler || (strcmp(r->handler, "brunoalves_module") != 0))
    {
        return DECLINED;
    }
    const char *url = r->uri;
    if (bruno_checkislinux(url))
    {
      r->status = HTTP_OK;
      ap_set_content_type(r, "text/html");
      ap_rputs(bruno_render(), r);
      return OK;
    }
    return DECLINED;
}
static void brunoalves_register(apr_pool_t *pool)
{
    ap_hook_handler(brunoalves_showlinux_img, NULL, NULL, APR_HOOK_LAST);
}
module AP_MODULE_DECLARE_DATA brunoalves_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    brunoalves_register /* Register function */
};