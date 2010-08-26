require 'rubygems'
require 'webrick'
require 'tempfile'
require 'json'
require 'erb'

class GraphMstReport < WEBrick::HTTPServlet::AbstractServlet
  def do_POST(request, response)
    status, content_type, body = run_algorithm(request)
    
    response.status = status
    response['Content-Type'] = content_type
    response.body = body
  end

  def run_algorithm(request)
    tmp = Tempfile.new("graph_mst_server")
    tmp.write(request.query["input_file"])
    tmp.flush
    data = JSON.parse(`cd .. && ./graph_mst #{tmp.path}`)
    body = ERB.new(File.open("report.html.erb").read).result(binding)
    return 200, "text/html", body
  end
end

class GraphMstImage < WEBrick::HTTPServlet::AbstractServlet
  def do_GET(request, response)
    status, content_type, body = get_image(request)
    
    response.status = status
    response['Content-Type'] = content_type
    response.body = body
  end

  def get_image(request)
    id = request.path.gsub("/img/", "").gsub(".png", "")
    img = `fdp -Tpng ../tmp/#{id}.dot`
    return 200, "image/png", img
  end
end

if $0 == __FILE__ then
  Dir.chdir(File.dirname(__FILE__))
  server = WEBrick::HTTPServer.new(:Port => 8000)
  server.mount "/",     WEBrick::HTTPServlet::FileHandler, "."
  server.mount "/post", GraphMstReport
  server.mount "/img", GraphMstImage
  trap "INT" do server.shutdown end
  server.start
end
