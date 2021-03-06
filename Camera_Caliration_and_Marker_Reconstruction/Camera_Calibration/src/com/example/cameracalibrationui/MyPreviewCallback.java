package com.example.cameracalibrationui;

import java.util.Date;

import nativeFunctions.NativeLib;

import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;


import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.util.Log;
import android.view.SurfaceHolder;
public class MyPreviewCallback implements PreviewCallback, Runnable{

	SurfaceHolder mHolder;
	int mHeight;
	int mWidth;
	Bitmap mBitmap;
	int [] mRGBA;
	int frameSize;
	long time=0;
	
	byte [] mFrame;
	
	boolean mThreadRun;
	
    private Mat mYuv;
    private Mat mRgba;
    private Mat mRGB;
    private Mat mGraySubmat;
	Date date;
	public MyPreviewCallback()
	{
		date=new Date();
		time=System.currentTimeMillis();
	}
	
	public void setSurfaceHolder(SurfaceHolder holder)
	{
		mHolder=holder;
	}
	public void setupPreviewBitmap(int height, int width)
	{
		mHeight=height;
		mWidth=width;
		mBitmap = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
		mRGBA = new int[mWidth * mHeight];
	}
	public void setFrameSize(int fs)
	{
		frameSize=fs;
	}
	public void setupMat()
	{	
		mYuv = new Mat(mHeight + mHeight / 2, mWidth, CvType.CV_8UC1);
        mGraySubmat = mYuv.submat(0, mHeight, 0, mWidth);
        mRgba = new Mat();
        mRGB =new Mat();    
	}
	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
            synchronized (MyPreviewCallback.this) {
                mFrame = data;
                MyPreviewCallback.this.notify();
            }
		
	}
	@Override
	public void run() {
		 mThreadRun = true;
	        Log.i("PreviweCallback", "Starting processing thread");
	        while (mThreadRun) {
	            Bitmap bmp = null;

	            synchronized (MyPreviewCallback.this) {
	                try {
	                    this.wait();
	                    bmp = processFrame(mFrame);
	                } catch (InterruptedException e) {
	                    e.printStackTrace();
	                }
	            }

	            
	            if (bmp != null) {
	                Canvas canvas = mHolder.lockCanvas();
	                if (canvas != null) {
	                    canvas.drawBitmap(bmp, (canvas.getWidth() - mWidth) / 2, (canvas.getHeight() - mHeight) / 2, null);
	                    mHolder.unlockCanvasAndPost(canvas);
	                }
	            }
	            
	        }
	}
	
	public Bitmap processFrame(byte[] data)
	{
		 Log.e("time:",": "+(System.currentTimeMillis()-time));
		mYuv.put(0, 0, data);
		
        Imgproc.cvtColor(mYuv, mRgba, Imgproc.COLOR_YUV420sp2RGB, 4);
		Imgproc.cvtColor(mRgba, mRGB, Imgproc.COLOR_RGBA2RGB, 3);
		NativeLib.FindRectangle(mRGB.getNativeObjAddr(), mHeight, mWidth, 1);

		Imgproc.cvtColor(mRGB, mRgba, Imgproc.COLOR_RGB2RGBA, 4);
        Bitmap bmp = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
        time=System.currentTimeMillis();
        if (Utils.matToBitmap(mRgba, bmp))
        {
        	return bmp;
        }
        return null; 
		
		
	}

	
}
