package geometrie;

public class GeometricalShape {

	public GeometricalShape(String color,String texture) {
		this.color = color;
		this.texture = texture;
		// TODO Auto-generated constructor stub
	}
	
	protected String color;
	private String texture;
	
	public String getcolor() {
		return this.color;
	}
	public String gettexture() {
		return this.texture;
	}
	
	public void draw(int zone) {
		System.out.println("Drawing the *valeur de zone*th zone of a shape ");
	}
	
	public void draw() {
		System.out.println("Drawing shape");
	}
	
}
